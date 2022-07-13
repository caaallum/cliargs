cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME args)

project(${PROJECT_NAME})

#####################################
# Export commands for ide use
#####################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCE
    src/params.cc
    )

file(GLOB INCLUDE
    include/cli-params.h
    include/cli-params/params.h)

#####################################
# Create library
#####################################
add_library(${PROJECT_NAME} ${SOURCES} ${INCLUDE})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

target_include_directories(${PROJECT_NAME} PRIVATE include)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

#####################################
# Install files
#####################################
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)