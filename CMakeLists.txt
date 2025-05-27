cmake_minimum_required(VERSION 3.16)
project(Gtk4CppApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use pkg-config to find GTKMM 4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)

# Add include directories
include_directories(${GTKMM_INCLUDE_DIRS} include)
link_directories(${GTKMM_LIBRARY_DIRS})

# Add the executable
add_executable(gtk4_cpp_app
    src/main.cpp
        src/VATUnix.cpp
        src/home_window.cpp
        include/about_page.h
        src/about_page.cpp
        include/software_page.h
        src/software_page.cpp
)

# Link against GTKMM
target_link_libraries(gtk4_cpp_app ${GTKMM_LIBRARIES})
target_compile_options(gtk4_cpp_app PRIVATE ${GTKMM_CFLAGS_OTHER})

