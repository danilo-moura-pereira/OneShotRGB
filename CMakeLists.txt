# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Semaforo C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1
add_executable(Semaforo
    Semaforo.c
)

pico_set_program_name(Semaforo "Semaforo")
pico_set_program_version(Semaforo "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_usb(Semaforo 1)
pico_enable_stdio_uart(Semaforo 0)


# Add the standard library to the build
target_link_libraries(Semaforo
    pico_stdlib
    hardware_pio
    hardware_clocks
	hardware_adc
)

# Add the standard include files to the build
target_include_directories(Semaforo PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(Semaforo)