// Copyright (C) 2025 Tiago V. L. Amorim (@tiagovla)
//
// This file is part of oiseau (https://github.com/tiagovla/oiseau)
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "oiseau/utils/logging.hpp"

#include <vector>

namespace oiseau::logging {

void set_verbosity(Verbosity level) { loguru::g_stderr_verbosity = level; }

void init(int argc, char** argv) {
  set_verbosity(Verbosity::INFO);  // Default to INFO
  std::vector<char*> argvv(argv, argv + argc);
  argvv.push_back(nullptr);
  loguru::init(argc, argvv.data());
}
}  // namespace oiseau::logging
