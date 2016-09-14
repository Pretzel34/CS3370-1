cmake_minimum_required (VERSION 2.6)
project (Portsetter)
add_executable (Portsetter portsetter.cpp)
set_property (TARGET Portsetter PROPERTY CXX_STANDARD 14)
set_property (TARGET Portsetter PROPERTY OUTPUT_NAME portsetter)

add_executable (Tests tests.cpp)
set_property (TARGET Tests PROPERTY CXX_STANDARD 14)
set_property (TARGET Tests PROPERTY OUTPUT_NAME tests)
