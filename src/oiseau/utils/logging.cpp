#include "oiseau/utils/logging.hpp"
#include <vector>

void oiseau::logging::init(int argc, char** argv) {
  loguru::g_stderr_verbosity = loguru::Verbosity_WARNING;
  std::vector<char*> argvv(argv, argv + argc);
  argvv.push_back(nullptr);
  loguru::init(argc, argvv.data());
}
