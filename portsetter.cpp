#include <vector>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <locale>




// Need to read usage from file.
// E.g. portsetter.cpp.usage_en.txt
// read by line.
enum MSG_STRING_INDX {
  LISTEN_PORT,
  INVALID_PORT,
  VALUE_OUT_RANGE,
  INVALID_PARAMS,
};


std::vector<std::string> readlines(std::string infile) {
  std::vector<std::string> msgs;
  std::ifstream strm(infile, std::ios::in);
  if (strm.good()) {
    for (std::string temp; !strm.eof(); ) {
      std::getline(strm, temp);
      msgs.push_back(temp);
    }
    strm.close();
  } else {
    std::cout << "Failed to open messages infile: " << infile << std::endl;
  }
  return msgs;
}

std::string readfile(std::string infile) {
  std::ifstream strm(infile, std::ios::in | std::ios::ate);
  if (strm.good()) {
    auto size = strm.tellg();
    std::string stdoutres(size, '\0');
    strm.seekg(0);
    strm.read(&stdoutres[0], size);
    strm.close();
    return stdoutres;
  } else {
    std::cout << "Failed to open usage infile: " << infile << std::endl;
  }
  return "";
}

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
    if (lc == "*" || lc == "") {
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

std::vector<std::string> get_msgs(std::string lang) {
  return readlines("locale/" + lang + "/messages.txt");
}

void usage(std::string lang) {
  std::string msg = readfile("locale/" + lang + "/usage.txt");
  std::cout << msg << std::endl;
}

void printerror(std::vector<std::string> msgs, int msgindx) {
  std::cout << "Error: " << msgs[msgindx] << std::endl;
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
  return std::stoi(portstr);
}

int main(int argc, char** args) {
  std::string lang = get_lang();
  auto msgs = get_msgs(lang);
  if (argc == 1) {
    printerror(msgs, MSG_STRING_INDX::INVALID_PARAMS);
    usage(lang);
    return EXIT_FAILURE;
  } else {
    int i;
    for (i = 1; i < argc; i++) {
      std::string current_arg = args[i];

      if (current_arg == "-h" || current_arg == "--help") {
        usage(lang);
        return EXIT_SUCCESS;
      }

      if (current_arg == "-p" || current_arg == "--port") {
        if (i + 1 < argc) {
          try {
            auto port_index = i + 1;
            std::string portstr = args[port_index];
            auto port = getport(port_index, argc, args, portstr);
            if (port > 0 && port <= 65000) {
              std::cout << msgs[(int)MSG_STRING_INDX::LISTEN_PORT] << port << std::endl;
              break;
            }
          } catch (std::invalid_argument) {
            printerror(msgs, MSG_STRING_INDX::INVALID_PORT);
            usage(lang);
            return EXIT_FAILURE;
          } catch (std::out_of_range) {
            printerror(msgs, MSG_STRING_INDX::VALUE_OUT_RANGE);
            usage(lang);
            return EXIT_FAILURE;
          }
        }
      }

      printerror(msgs, MSG_STRING_INDX::INVALID_PARAMS);
      usage(lang);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
