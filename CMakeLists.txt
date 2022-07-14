cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME args)

project(${PROJECT_NAME})

#####################################
# Export commands for ide use
#####################################
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCE
    src/params.c
    src/arg.c
    )

file(GLOB INCLUDE
    include/cli-params.h
    include/cli-params/params.h)

include_directories(include)

#####################################
# Create library
#####################################
add_library(${PROJECT_NAME} ${SOURCE} ${INCLUDE})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)

#####################################
# Install files
#####################################
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
