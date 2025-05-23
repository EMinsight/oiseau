#!/bin/bash
# Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
#
# This file is part of oiseau (https://github.com/tiagovla/oiseau)
#
# SPDX-License-Identifier: GPL-3.0-or-later


set -e
set -o pipefail
set -u

cd "$(dirname "${0}")/.."

list_repository_files() {
  if command -v git &>/dev/null && git rev-parse --is-inside-work-tree &>/dev/null; then
    git ls-files --cached --exclude-standard -- "${@}"
    return 0
  fi

  if command -v sl &>/dev/null; then
    if sl files "${@}" 2>/dev/null; then
      return 0
    fi
  fi

  printf "ERROR: Unable to list repository files. Neither 'git ls-files' nor 'sl files' succeeded.\n" >&2
  return 1
}

filter_out_lines() {
  local pattern_to_exclude="${1}"
  grep -E -v -- "${pattern_to_exclude}" || true
}

mapfile -t files_to_analyze < <(
  list_repository_files "${@}" \
    | filter_out_lines '^vendor/.*/' \
    | filter_out_lines -- '-generated'
)

if [ "${#files_to_analyze[@]}" -eq 0 ]; then
  printf "No relevant files found to analyze after filtering.\n" >&2
  exit 0
fi

cloc --no-autogen "${files_to_analyze[@]}"
