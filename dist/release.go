// Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
//
// This file is part of oiseau (https://github.com/tiagovla/oiseau)
//
// SPDX-License-Identifier: GPL-3.0-or-later

package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
	"time"
)

var (
	ThreePartVersionRegexp  *regexp.Regexp = regexp.MustCompile(`^\d+\.\d+\.\d+$`)
	CMakeVersionRegexp      *regexp.Regexp = regexp.MustCompile(`(project\s*\([^)]*?VERSION\s+)(\d+\.\d+\.\d+)([^)]*?\))`)
	PyProjectVersionRegexp  *regexp.Regexp = regexp.MustCompile(`(?m)^(version\s*=\s*")(\d+\.\d+\.\d+)(".*)`)
	PythonInitVersionRegexp *regexp.Regexp = regexp.MustCompile(`(?m)^(__version__\s*=\s*")(\d+\.\d+\.\d+)(".*)`)
)

// VersionNumber represents a semantic version with Major, Minor, and Patch components.
type VersionNumber struct {
	Major int
	Minor int
	Patch int
}

// String returns the string representation of the VersionNumber (e.g., "1.2.3").
func (v VersionNumber) String() string {
	return fmt.Sprintf("%d.%d.%d", v.Major, v.Minor, v.Patch)
}

// CompareTo compares this VersionNumber (v) with another VersionNumber (other).
// It returns:
//
//	 1 if v is newer than other
//	 0 if v is the same as other
//	-1 if v is older than other
func (v VersionNumber) CompareTo(other VersionNumber) int {
	if v.Major > other.Major {
		return 1
	}
	if v.Major < other.Major {
		return -1
	}
	if v.Minor > other.Minor {
		return 1
	}
	if v.Minor < other.Minor {
		return -1
	}
	if v.Patch > other.Patch {
		return 1
	}
	if v.Patch < other.Patch {
		return -1
	}
	return 0
}

// ParseVersionString converts a "X.Y.Z" string into a VersionNumber struct.
func ParseVersionString(versionStr string) (VersionNumber, error) {
	if !ThreePartVersionRegexp.MatchString(versionStr) {
		return VersionNumber{}, fmt.Errorf("version string '%s' does not match X.Y.Z format", versionStr)
	}
	partsStr := strings.Split(versionStr, ".")
	if len(partsStr) != 3 {
		return VersionNumber{}, fmt.Errorf("internal error: version string '%s' split into %d parts, expected 3", versionStr, len(partsStr))
	}
	major, err := strconv.Atoi(partsStr[0])
	if err != nil {
		return VersionNumber{}, fmt.Errorf("invalid major version part '%s': %w", partsStr[0], err)
	}
	minor, err := strconv.Atoi(partsStr[1])
	if err != nil {
		return VersionNumber{}, fmt.Errorf("invalid minor version part '%s': %w", partsStr[1], err)
	}
	patch, err := strconv.Atoi(partsStr[2])
	if err != nil {
		return VersionNumber{}, fmt.Errorf("invalid patch version part '%s': %w", partsStr[2], err)
	}
	return VersionNumber{Major: major, Minor: minor, Patch: patch}, nil
}

// VersionFileInfo defines the structure of the data read from/written to the "version" file.
type VersionFileInfo struct {
	Version     VersionNumber
	ReleaseDate time.Time
}

// ReadVersionFileData parses the content of a version file.
// It expects the version number (X.Y.Z) on the first line and the date (YYYY-MM-DD) on the second.
func ReadVersionFileData(data []byte, filePath string) (VersionFileInfo, error) {
	lines := strings.Split(strings.TrimSpace(string(data)), "\n")
	if len(lines) < 2 {
		return VersionFileInfo{}, fmt.Errorf("version file '%s' content is malformed, expected at least 2 lines (version, date)", filePath)
	}
	versionStr := strings.TrimSpace(lines[0])
	parsedVersion, err := ParseVersionString(versionStr)
	if err != nil {
		return VersionFileInfo{}, fmt.Errorf("error parsing version '%s' from '%s': %w", versionStr, filePath, err)
	}
	releaseDateStr := strings.TrimSpace(lines[1])
	releaseDate, err := time.ParseInLocation("2006-01-02", releaseDateStr, time.Local)
	if err != nil {
		return VersionFileInfo{}, fmt.Errorf("failed to parse release date '%s' from '%s': %w", releaseDateStr, filePath, err)
	}
	return VersionFileInfo{
		Version:     parsedVersion,
		ReleaseDate: releaseDate,
	}, nil
}

// ReadCurrentVersionInfo reads and parses the "version" file.
// It returns the parsed VersionFileInfo, a boolean indicating if the file existed, and an error if any occurred.
func ReadCurrentVersionInfo(filePath string) (info VersionFileInfo, existed bool, err error) {
	data, err := os.ReadFile(filePath)
	if err != nil {
		if os.IsNotExist(err) {
			return VersionFileInfo{}, false, nil
		}
		return VersionFileInfo{}, false, fmt.Errorf("failed to read version file '%s': %w", filePath, err)
	}
	parsedInfo, parseErr := ReadVersionFileData(data, filePath)
	if parseErr != nil {
		return VersionFileInfo{}, true, parseErr
	}
	return parsedInfo, true, nil
}

// WriteVersionFile writes the provided version information to the specified file.
// The file will contain the version number (X.Y.Z) on the first line and the release date
// (formatted as YYYY-MM-DD) on the second line.
// If the file doesn't exist, it will be created. If it exists, it will be overwritten.
func WriteVersionFile(filePath string, versionInfo VersionFileInfo) error {
	versionText := fmt.Sprintf("%s\n%s\n", versionInfo.Version.String(), versionInfo.ReleaseDate.Format("2006-01-02"))
	if err := os.WriteFile(filePath, []byte(versionText), 0644); err != nil {
		return fmt.Errorf("failed to write to '%s': %w", filePath, err)
	}
	fmt.Printf("Updated '%s': version %s, date %s\n", filePath, versionInfo.Version, versionInfo.ReleaseDate.Format("2006-01-02"))
	return nil
}

// updateFileWithRegex is a generic helper to update a file content using a regex.
// It handles file reading, regex matching, replacement, and writing.
// If the file does not exist or the pattern is not found, it logs a message and returns nil (skips).
func updateFileWithRegex(filePath string, newVersion VersionNumber, versionRegex *regexp.Regexp, replacementPattern string, fileType string) error {
	data, err := os.ReadFile(filePath)
	if err != nil {
		if os.IsNotExist(err) {
			log.Printf("%s file '%s' not found, skipping update.", fileType, filePath)
			return nil
		}
		return fmt.Errorf("failed to read %s file '%s': %w", fileType, filePath, err)
	}
	content := string(data)

	matches := versionRegex.FindStringSubmatch(content)
	if matches == nil {
		log.Printf("Version pattern not found in %s file '%s', skipping update.", fileType, filePath)
		return nil
	}

	oldVersionStr := matches[2] // Group 2 is consistently the version number in our regexes
	newVersionStr := newVersion.String()

	if oldVersionStr == newVersionStr {
		log.Printf("%s file '%s' already contains version %s. No update needed.", fileType, filePath, newVersionStr)
		return nil
	}

	newContent := versionRegex.ReplaceAllString(content, replacementPattern)

	fileInfo, err := os.Stat(filePath)
	if err != nil {
		return fmt.Errorf("failed to get file info for '%s' before writing: %w", filePath, err)
	}
	originalPerms := fileInfo.Mode().Perm()

	if err := os.WriteFile(filePath, []byte(newContent), originalPerms); err != nil {
		return fmt.Errorf("failed to write updated content to %s file '%s': %w", fileType, filePath, err)
	}

	log.Printf("Updated version in %s file '%s' from %s to %s", fileType, filePath, oldVersionStr, newVersionStr)
	return nil
}

// UpdateCMakeVersion updates the version in a CMakeLists.txt file.
func UpdateCMakeVersion(cmakeFilePath string, newVersion VersionNumber) error {
	replacementPattern := "${1}" + newVersion.String() + "${3}"
	return updateFileWithRegex(cmakeFilePath, newVersion, CMakeVersionRegexp, replacementPattern, "CMake")
}

// UpdatePyProjectTomlVersion updates the version in a pyproject.toml file.
func UpdatePyProjectTomlVersion(tomlFilePath string, newVersion VersionNumber) error {
	replacementPattern := "${1}" + newVersion.String() + "${3}"
	return updateFileWithRegex(tomlFilePath, newVersion, PyProjectVersionRegexp, replacementPattern, "pyproject.toml")
}

// UpdatePythonInitVersion updates the version in a Python __init__.py file.
func UpdatePythonInitVersion(initFilePath string, newVersion VersionNumber) error {
	replacementPattern := "${1}" + newVersion.String() + "${3}"
	return updateFileWithRegex(initFilePath, newVersion, PythonInitVersionRegexp, replacementPattern, "Python __init__.py")
}

// parseAndValidateInputs handles command-line flags and initial validation.
// It returns the source path, the parsed new version, and an error if any occurs.
func parseAndValidateInputs() (sourcePath string, parsedVersion VersionNumber, err error) {
	var newVersionString string
	flag.StringVar(&sourcePath, "sourcePath", ".", "Base path to the project's source directory. Version files like 'version', 'CMakeLists.txt', 'python/pyproject.toml', and 'python/oiseau/__init__.py' will be sought relative to this path.")
	flag.StringVar(&newVersionString, "new_version", "", "The new version number (e.g., 1.2.3) to write.")
	flag.Parse()

	if newVersionString == "" {
		programName := filepath.Base(os.Args[0])
		return "", VersionNumber{}, fmt.Errorf("the -new_version flag is required.\nUsage: %s -new_version <version_string> [-sourcePath <path>]", programName)
	}

	parsedVersion, err = ParseVersionString(newVersionString)
	if err != nil {
		return "", VersionNumber{}, fmt.Errorf("invalid new version format: %w", err)
	}
	return sourcePath, parsedVersion, nil
}

// updateAllVersionFiles coordinates the reading, validation, and writing of all version files.
func updateAllVersionFiles(sourcePath string, newVersion VersionNumber) error {
	actualVersionFilePath := filepath.Join(sourcePath, "version")
	actualCMakeFilePath := filepath.Join(sourcePath, "CMakeLists.txt")
	actualPyProjectTomlPath := filepath.Join(sourcePath, "python", "pyproject.toml")
	actualPythonInitPath := filepath.Join(sourcePath, "python", "oiseau", "__init__.py")

	currentVersionInfo, fileExisted, err := ReadCurrentVersionInfo(actualVersionFilePath)
	if err != nil {
		return fmt.Errorf("processing current version file '%s': %w", actualVersionFilePath, err)
	}

	if fileExisted {
		log.Printf("Current version in '%s': %s (Release Date: %s)",
			actualVersionFilePath,
			currentVersionInfo.Version.String(),
			currentVersionInfo.ReleaseDate.Format("2006-01-02"))

		comparisonResult := newVersion.CompareTo(currentVersionInfo.Version)
		if comparisonResult <= 0 {
			return fmt.Errorf("new version '%s' is not strictly newer than current version '%s' found in '%s'. (Comparison result: %d)",
				newVersion.String(), currentVersionInfo.Version.String(), actualVersionFilePath, comparisonResult)
		}
		log.Printf("New version '%s' is newer than current version '%s'. Proceeding.", newVersion.String(), currentVersionInfo.Version.String())
	} else {
		log.Printf("Version file '%s' does not exist. Proceeding to create it with version '%s'.", actualVersionFilePath, newVersion.String())
	}

	releaseDate := time.Now().Truncate(24 * time.Hour)
	newVersionInfoToWrite := VersionFileInfo{
		Version:     newVersion,
		ReleaseDate: releaseDate,
	}

	if err := WriteVersionFile(actualVersionFilePath, newVersionInfoToWrite); err != nil {
		return fmt.Errorf("updating version file '%s': %w", actualVersionFilePath, err)
	}

	if err := UpdateCMakeVersion(actualCMakeFilePath, newVersion); err != nil {
		// updateFileWithRegex handles logging for "not found" or "pattern not found" by returning nil.
		// An error here means a more serious issue (e.g., read/write permission error).
		return fmt.Errorf("updating CMake file '%s': %w", actualCMakeFilePath, err)
	}

	if err := UpdatePyProjectTomlVersion(actualPyProjectTomlPath, newVersion); err != nil {
		return fmt.Errorf("updating pyproject.toml file '%s': %w", actualPyProjectTomlPath, err)
	}

	if err := UpdatePythonInitVersion(actualPythonInitPath, newVersion); err != nil {
		return fmt.Errorf("updating Python __init__.py file '%s': %w", actualPythonInitPath, err)
	}

	return nil
}

// main orchestrates the version update process.
func main() {
	sourcePath, newParsedVersion, err := parseAndValidateInputs()
	if err != nil {
		log.Fatalf("Input error: %v", err)
	}

	err = updateAllVersionFiles(sourcePath, newParsedVersion)
	if err != nil {
		log.Fatalf("Failed to update version information: %v", err)
	}

	log.Println("Version update process completed successfully.")
}
