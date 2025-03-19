cmake_minimum_required(VERSION 3.16)
SET(CMAKE_TOOLCHAIN_FILE "/Users/jiyong/Lib/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(qxx01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

message ("OpenCV_ROOT = " ${OpenCV_ROOT})
link_directories(${OpenCV_INCLUDE_DIRS})

INCLUDE_DIRECTORIES ( ${OpenCV_INCLUDE_DIRS} )
add_executable(qxx01 main.cpp)

include(GNUInstallDirs)
install(TARGETS qxx01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
target_link_libraries(cqxx01 ${OpenCV_LIBS})
