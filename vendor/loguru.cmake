# Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
#
# This file is part of oiseau (https://github.com/tiagovla/oiseau)
#
# SPDX-License-Identifier: GPL-3.0-or-later

FetchContent_Declare(
    loguru
    GIT_REPOSITORY https://github.com/emilk/loguru
    GIT_TAG ${LOGURU_VERSION}
    GIT_SHALLOW 0
    GIT_PROGRESS 1
)

if(NOT loguru_POPULATED)
    cmake_policy(SET CMP0169 OLD)
    FetchContent_Populate(loguru)
    add_library(loguru STATIC ${loguru_SOURCE_DIR}/loguru.cpp)
    target_include_directories(loguru PUBLIC ${loguru_SOURCE_DIR})
    target_compile_definitions(loguru PUBLIC LOGURU_WITH_STREAMS)
    target_compile_options(loguru PRIVATE -fPIC)
endif()
