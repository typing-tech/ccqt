cmake_minimum_required(VERSION 3.14)
project(ccqt CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wfloat-conversion -Wsign-conversion -Wshadow")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets UiTools SerialPort)
qt_standard_project_setup()

add_executable(ccqt
   src/senderthread.cpp
   src/raw_terminal.cpp
   src/mainwindow.cpp
   src/main.cpp
	 )
target_link_libraries(ccqt Qt6::Widgets Qt6::UiTools Qt6::SerialPort)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Copy root/build/compile_commands.json to root/
if (EXISTS "${CMAKE_BINARY_DIR}/compile_commands.json")
   FILE(COPY ${CMAKE_BINARY_DIR}/compile_commands.json DESTINATION ${CMAKE_HOME_DIRECTORY})
endif()
