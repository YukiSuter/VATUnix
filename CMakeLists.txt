cmake_minimum_required(VERSION 3.16)
project(VATUnix VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config to find GTKMM 4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Add include directories
include_directories(${GTKMM_INCLUDE_DIRS} include)
link_directories(${GTKMM_LIBRARY_DIRS})

# Add the executable
add_executable(VATUnix
    src/main.cpp
        src/VATUnix.cpp
        src/home_window.cpp
        include/about_page.h
        src/about_page.cpp
        include/software_page.h
        src/software_page.cpp
        src/file_utils.cpp
        include/file_utils.h
        include/fts_page.h
        src/fts_page.cpp
        include/json.hpp
)

# Link against GTKMM
target_link_libraries(VATUnix ${GTKMM_LIBRARIES})
target_compile_options(VATUnix PRIVATE ${GTKMM_CFLAGS_OTHER})

