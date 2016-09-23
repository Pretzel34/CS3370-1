#include <cstddef>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

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

int runTest(std::string command, std::string stdlog, std::string expstdres, int expretcode) {
  auto retcode = system(command.c_str());
  std::string stdres = readfile(stdlog);
  int passed = 0;
  stdres.replace(stdres.end() - 1, stdres.end(), '\n', '\0');

  std::cout << "\nCommand: '" << command << "'" << std::endl;
  if (expstdres == "usage" && retcode == expretcode) {
    std::cout << "Test Passed!" << std::endl;
    passed = 1;
  } else if (stdres.compare(expstdres) && retcode == expretcode) {
    std::cout << "Test Passed!" << std::endl;
    passed = 1;
  } else {
    std::cout << "Test Failed!" << std::endl;
  }
  std::cout << "\tReturned code: " << std::endl;
  std::cout << "\t\t'" << retcode << "'" << std::endl;
  std::cout << "\tExpected code: " << std::endl;
  std::cout << "\t\t'" << expretcode << "'" << std::endl;
  std::cout << "\tReturned Stdout: " << std::endl;
  std::cout << "\t\t'" << stdres << "'" << std::endl;
  std::cout << "\tExpected Stdout: " << std::endl;
  std::cout << "\t\t'" << expstdres << "'" << std::endl;
  return passed;
}

int main(int argc, char** args) {
  int summary = 0;
  int num_tests = 14;
  // The 256 code is equivalent to 1.
  // C++ and C multiply the return code by 256.

  // General Tests
  summary += runTest("./portsetter -p 50 > stdout.txt", "stdout.txt", "Listening on port: 50", 0);
  summary += runTest("./portsetter -h > stdout.txt", "stdout.txt", "usage", 0);
  summary += runTest("./portsetter > stdout.txt", "stdout.txt", "usage", 0);
  summary += runTest("./portsetter -p a > stdout.txt", "stdout.txt", "usage", 256);
  summary += runTest("./portsetter --port a > stdout.txt", "stdout.txt", "usage", 256);
  summary += runTest("./portsetter a > stdout.txt", "stdout.txt", "usage", 256);
  summary += runTest("./portsetter -h -p 50 > stdout.txt", "stdout.txt", "usage", 0);
  summary += runTest("./portsetter -p 571 -h > stdout.txt", "stdout.txt", "Listening on port: 571", 0);
  summary += runTest("./portsetter -p 999999 > stdout.txt", "stdout.txt", "usage", 256);
  summary += runTest("./portsetter -p -10 > stdout.txt", "stdout.txt", "usage", 256);

  // Env Tests
  summary += runTest("env MY_PORT=70 ./portsetter -p -e MY_PORT > stdout.txt", "stdout.txt", "Listening on port: 70", 0);
  summary += runTest("env PORT=50 ./portsetter -p -e > stdout.txt", "stdout.txt", "Listening on port: 50", 0);
  summary += runTest("env PORT=150 ./portsetter -p -e > stdout.txt", "stdout.txt", "Listening on port: 150", 0);

  // Spanish Tests
  summary += runTest("env LANG=es_ES.UTF-8 PORT=75 ./portsetter -p -e > stdout.txt", "stdout.txt", "Escucha en el puerto: 75", 0);
  summary += runTest("env LANG=es_ES.UTF-8 PORT=75 ./portsetter > stdout.txt", "stdout.txt", "usage", 256);

  std::cout << "\nSummary: " << summary << " / " << num_tests << " Tests passed!" << std::endl;
}
