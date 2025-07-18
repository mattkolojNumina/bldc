# VESC Firmware Tech Stack

## Programming Language
- **C99**: Primary language for firmware development
- **C++11**: Used for unit tests (Google Test framework)

## Build System
- **GNU Make**: Primary build system
- **GNU ARM Toolchain**: gcc-arm-none-eabi cross-compiler
- **Custom Makefile system**: Multi-platform support (Linux, macOS, Windows)

## Operating System / RTOS
- **ChibiOS 3.0.5**: Real-time operating system for STM32 microcontrollers
- **HAL (Hardware Abstraction Layer)**: STM32F4xx specific

## Key Libraries and Frameworks
- **STM32F4xx**: Target microcontroller platform
- **Google Test**: Unit testing framework (tests written in C++)
- **LispBM**: Embedded Lisp interpreter for scripting

## Hardware Support
- **STM32F4 series**: Primary target microcontrollers
- **Multiple VESC board variants**: Hardware configurations in hwconf/ directory
- **Motor drivers**: DRV8301, DRV8305, DRV8320s, DRV8323s, DRV8316, SI8900

## Development Tools
- **Qt Creator**: Recommended IDE (project files in Project/Qt Creator/)
- **OpenOCD**: For flashing via SWD/JTAG debuggers
- **STLink**: Hardware debugger support
- **Travis CI**: Continuous integration (legacy)

## Communication Protocols
- **USB**: Communication with VESC Tool
- **CAN**: Multi-VESC communication
- **UART**: Serial communication
- **SPI/I2C**: Sensor interfaces