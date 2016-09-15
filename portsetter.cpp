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
};

//std::vector<std::string*> en = {"Usage: portsetter [flag] [port]", "\tFlags:", "\t\t-p, --port [n]\t where 0 < n <= 65000", "\t\t-h, --help\t Prints this usage screen."}
//std::vector<std::string*> usage_msg = en;

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

int main(int argc, char** args) {
  if (argc == 1) {
    usage();
  } else {
    int i = 1;
    for (i; i < argc; i++) {
      std::string current_arg = args[i];

      if (current_arg == "-p" || current_arg == "--port") {
        if (i + 1 < argc) {
          auto port_index = i + 1;
          try {
            auto portcstr = args[port_index];
            int port = std::stoi(portcstr);
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
        usage();
        return EXIT_FAILURE;
      } else if (current_arg == "-h" || current_arg == "--help") {
        usage();
        return EXIT_SUCCESS;
      } else {
        usage();
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
