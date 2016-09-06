#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>

void usage() {
  std::cout << "Usage:" << std::endl;
}

int main(int argc, char** args) {
  //int k = 1;
  //for (k; k < argc; ++k) {
  //  std::cout << args[k] << std::endl;
  //}
  // Start at argc[1] because we don't care about the name of the program.
  int i = 1;
  for (i; i < argc; i++) {
    auto current_arg = args[i];

    if (std::strcmp(current_arg, "-p") || std::strcmp(current_arg, "--port")) {
      if (i + 1 < argc) {
        auto port_index = i + 1;
        auto port = (int)(*args[port_index]);
        if (0 < port <= 65000) {
          std::cout << "Listening on port " << port << std::endl;
          break;
        }
      }
      usage();
      return EXIT_FAILURE;
    } else if (std::strcmp(current_arg, "-h") || std::strcmp(current_arg, "--help")) {
      usage();
      return EXIT_FAILURE;
    } else {
      usage();
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
