#include <vector>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>


// Need to read usage from file.
// E.g. portsetter.cpp.usage_en.txt
// read by line.
enum class USAGE_STRING_INDX {
  USAGE_MSG,
  FLAG_HEADER_MSG,
  P_FLAG_MSG,
  H_FLAG_MSG,
  E_FLAG_MSG,
};

void usage() {
  std::cout << "Usage: portsetter [flag] [port]" << std::endl;
  std::cout << "\tFlags:" << std::endl;
  std::cout << "\t\t-p, --port [n]\t where 0 < n <= 65000" << std::endl;
  std::cout << "\t\t-h, --help\t Prints this usage screen." << std::endl;
}

//Language reqs.
// 1. LANGUAGE
// 2. LANG
// 3. LC_ALL
// 4. LC
// 5. Default to en.
//
// Read from lang file into msg array.


int getport(int argsindx, int argc, char** args, std::string portstr) {
  if (portstr == "-e") {
    auto envstr = "PORT";
    if (argsindx + 1 < argc) {
      auto env_var_indx = argsindx + 1;
      envstr = args[env_var_indx];
    }
    portstr = std::getenv(envstr);
    return std::stoi(portstr);
  }
  return 0;
}

int main(int argc, char** args) {
  if (argc == 1) {
    usage();
  } else {
    int i = 1;
    for (i; i < argc; i++) {
      std::string current_arg = args[i];

      if (current_arg == "-p" || current_arg == "--port") {
        if (i + 1 < argc) {
          try {
            auto port_index = i + 1;
            std::string portstr = args[port_index];
            auto port = getport(port_index, argc, args, portstr);
            if (port > 0 && port <= 65000) {
              std::cout << "Listening on port " << port << std::endl;
              break;
            }
          } catch (std::invalid_argument) {
            usage();
            return EXIT_FAILURE;
          } catch (std::out_of_range) {
            usage();
            return EXIT_FAILURE;
          }
        }
      }

      usage();
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
