cmake_minimum_required(VERSION 3.10)
project(UnixSocketExample C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add executable for server
add_executable(server Server.c)

# Add executable for client
add_executable(client Client.c)
