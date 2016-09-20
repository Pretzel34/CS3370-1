#include <vector>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <locale>




// Need to read usage from file.
// E.g. portsetter.cpp.usage_en.txt
// read by line.
enum USAGE_STRING_INDX {
  USAGE_MSG,
  FLAG_HEADER_MSG,
  P_FLAG_MSG,
  E_FLAG_MSG,
  H_FLAG_MSG,
};

std::string get_lang() {
  //Language reqs.
  // 1. LANGUAGE
  // 2. LANG
  // 3. LC_ALL
  // 4. LC
  // 5. Default to en.
  //
  // Read from lang file into msg array.
  std::string lang;
  try {
    std::string lc = std::locale("").name();
    if (lc == "*") {
      std::cout << "Locale not set defaulting to english." << std::endl;
      lang = "en";
    } else {
      lang = lc.substr(0, 2);
    }
  } catch (std::runtime_error) {
    std::cout << "Environment Locale is invalid defaulting to english." << std::endl;
    lang = "en";
  }

  return lang;
}

std::vector<std::string> get_error_msgs(std::string lang) {
}

std::string readfile(std::string infile) {
  if (std::ifstream strm{infile, std::ios::in | std::ios::ate}) {
    auto size = strm.tellg();
    std::string stdoutres(size, '\0');
    strm.seekg(0);
    strm.read(&stdoutres[0], size);
    strm.close();
    return stdoutres;
  } else {
    std::cout << "Failed to open infile: " << infile << std::endl;
  }
  return "";
}

void usage(std::string lang) {
  std::string msg = readfile("locale/" + lang + "/usage.txt");
  std::cout << msg << std::endl;
}

int getport(int argsindx, int argc, char** args, std::string portstr) {
  if (portstr == "-e" || portstr == "--env") {
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
  std::string lang = get_lang();
  if (argc == 1) {
    usage(lang);
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
            usage(lang);
            return EXIT_FAILURE;
          } catch (std::out_of_range) {
            usage(lang);
            return EXIT_FAILURE;
          }
        }
      }

      usage(lang);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
