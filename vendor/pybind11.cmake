# Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
#
# This file is part of oiseau (https://github.com/tiagovla/oiseau)
#
# SPDX-License-Identifier: GPL-3.0-or-later

set(PYBIND11_FINDPYTHON "NEW")

FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG ${PYBIND11_VERSION}
    GIT_SHALLOW 0
    GIT_PROGRESS 1
)

FetchContent_MakeAvailable(pybind11)
