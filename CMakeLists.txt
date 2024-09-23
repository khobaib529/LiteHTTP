if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

cmake_minimum_required(VERSION 3.10)

project(LiteHTTP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create the library
add_library(litehttp STATIC
    src/HTTP.cpp
    src/Request.cpp
    src/Response.cpp
)

# Specify the include directories for the library
target_include_directories(litehttp PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
