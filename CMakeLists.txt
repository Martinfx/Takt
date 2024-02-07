cmake_minimum_required(VERSION 3.5)

project(language LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address -fno-omit-frame-pointer)
    link_libraries("-fsanitize=address")
endif()

add_executable(language main.cpp
    ast.hpp environment.hpp interpreter.hpp main.cpp  parser.hpp token.hpp values.hpp)

include(GNUInstallDirs)
install(TARGETS language
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
