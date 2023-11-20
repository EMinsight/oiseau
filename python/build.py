import os
import subprocess
import sys

from setuptools.command.build_ext import build_ext
from setuptools import Extension


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=""):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))

        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        debug = int(os.environ.get("DEBUG", 0)) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"

        cmake_generator = os.environ.get("CMAKE_GENERATOR", "")

        cmake_args = [
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={extdir}",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            f"-DCMAKE_BUILD_TYPE={cfg}",
        ]
        build_args = []
        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]

        if not cmake_generator or cmake_generator == "Ninja":
            try:
                import ninja  # noqa: F401

                ninja_executable_path = os.path.join(ninja.BIN_DIR, "ninja")
                cmake_args += [
                    "-GNinja",
                    f"-DCMAKE_MAKE_PROGRAM:FILEPATH={ninja_executable_path}",
                ]
            except ImportError:
                pass

        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            if hasattr(self, "parallel") and self.parallel:
                build_args += [f"-j{self.parallel}"]
        build_args += [f"-j{12}"]

        build_temp = os.path.join(self.build_temp, ext.name)
        if not os.path.exists(build_temp):
            os.makedirs(build_temp)
        print("HAHA" * 50)
        print(["cmake", ext.sourcedir] + cmake_args)
        subprocess.check_call(["cmake", ext.sourcedir] + cmake_args, cwd=build_temp)
        subprocess.check_call(["cmake", "--build", "."] + build_args, cwd=build_temp)


def build(setup_kwargs):
    print("AHSDFHIASDHIFA")
    os.environ["CFLAGS"] = "-O3"
    setup_kwargs.update(
        {
            "version": "0.1.0",
            "author": "tiagovla",
            "author_email": "tiagovla@gmail.com",
            "description": "DG Framework",
            "long_description": "",
            "packages": ["oiseau", "oiseau.wrappers"],
            "package_data": {"oiseau.cpp": ["*.h"]},
            "ext_modules": [CMakeExtension("oiseau.cpp")],
            "cmdclass": {"build_ext": CMakeBuild},
            "zip_safe": False,
            "setup_requires": ["pybind11"],
        }
    )
