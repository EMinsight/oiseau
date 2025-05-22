// Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
//
// This file is part of oiseau (https://github.com/tiagovla/oiseau)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <loguru.hpp>

namespace oiseau::logging {

enum Verbosity {
  OFF = loguru::Verbosity_OFF,
  FATAL = loguru::Verbosity_FATAL,
  ERROR = loguru::Verbosity_ERROR,
  WARNING = loguru::Verbosity_WARNING,
  INFO = loguru::Verbosity_INFO,
  DEBUG = loguru::Verbosity_1,  // Loguru's custom higher-verbosity
};

void set_verbosity(Verbosity level);
void init(int argc, char** argv);

}  // namespace oiseau::logging
