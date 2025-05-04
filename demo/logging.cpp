#include <oiseau/utils/logging.hpp>

int main(int argc, char** argv) {
  oiseau::logging::init(argc, argv);
  LOG_F(ERROR, "Hello from oiseau!");
}
