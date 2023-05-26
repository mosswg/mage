cmake_minimum_required(VERSION 3.13)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(MAGE CXX C ASM)

pico_sdk_init()

add_subdirectory(firmware)
# add_subdirectory(configurator)
