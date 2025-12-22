cmake_minimum_required(VERSION 3.16)
project(MyApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Generate compile_commands.json for better IDE support and linting
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find clang-tidy if available
find_program(CLANG_TIDY_EXE
    NAMES "clang-tidy"
    PATHS "/opt/homebrew/opt/llvm/bin" "/usr/local/opt/llvm/bin"
    NO_DEFAULT_PATH
)
if(NOT CLANG_TIDY_EXE)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
endif()

add_executable(app
  main.cpp
)

target_include_directories(app PRIVATE include)

# Enable clang-tidy if found
if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(app PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy"
    )
else()
    message(WARNING "clang-tidy not found")
endif()

# Add custom linting target
if(CLANG_TIDY_EXE)
    add_custom_target(lint
        COMMAND ${CLANG_TIDY_EXE}
        --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        --header-filter=.*
        --format-style=file
        ${CMAKE_SOURCE_DIR}/main.cpp
        --
        -std=c++17
        -I${CMAKE_SOURCE_DIR}/include
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-tidy..."
    )
endif()
