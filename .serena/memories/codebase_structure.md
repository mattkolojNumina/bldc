# VESC Firmware Codebase Structure

## Root Directory Files
- **main.c/main.h**: Main application entry point and initialization
- **Makefile**: Primary build configuration
- **conf_general.h/c**: General firmware configuration and constants
- **conf_custom.h/c**: Custom configuration overrides
- **terminal.h/c**: Terminal command interface implementation  
- **timeout.h/c**: Timeout and safety management
- **events.h/c**: Event handling system
- **bms.h/c**: Battery Management System integration
- **datatypes.h**: Core data structure definitions
- **flash_helper.h/c**: Flash memory operations
- **isr_vector_table.h**: Interrupt service routine definitions
- **irq_handlers.c**: Interrupt handler implementations

## Core Directories

### `/motor/` - Motor Control Core
- **mc_interface.h/c**: Main motor control interface
- **mcpwm.h/c**: Motor PWM control (BLDC)
- **mcpwm_foc.h/c**: Field Oriented Control implementation
- **foc_math.h/c**: FOC mathematical operations
- **virtual_motor.h/c**: Virtual motor simulation
- **mcconf_default.h**: Default motor configuration

### `/applications/` - Application Layer
- **app.h/c**: Application framework and management
- **app_adc.c**: ADC-based control application
- **app_ppm.c**: PPM (RC) control application  
- **app_nunchuk.c**: Wii Nunchuk control interface
- **app_pas.c**: Pedal Assist System
- **app_uartcomm.c**: UART communication application
- **app_custom.c**: Custom application template
- **appconf_default.h**: Default application configuration

### `/hwconf/` - Hardware Configurations
- **hw.h/c**: Hardware abstraction interface
- **board.h/c**: Board-specific implementations
- Various subdirectories for different manufacturers:
  - `vesc/`, `trampa/`, `flipsky/`, `makerx/`, etc.
- Driver implementations: `drv8301.c`, `drv8305.c`, etc.

### `/comm/` - Communication Protocols
- USB, CAN, UART communication implementations
- Protocol handling and packet management

### `/encoder/` - Position Sensors
- Various encoder implementations and interfaces
- Sensor data processing and calibration

### `/imu/` - Inertial Measurement Unit
- IMU sensor integration and data processing
- Orientation and motion sensing

### `/driver/` - Low-level Drivers
- Hardware driver implementations
- Peripheral interface code

### `/util/` - Utility Functions
- Mathematical utilities
- System utilities and helper functions

### `/tests/` - Unit Tests
- **utils_math/**: Math function unit tests
- **angles/**: Angle calculation tests
- **packet_recovery/**: Communication packet tests
- **float_serialization/**: Data serialization tests
- **overvoltage_fault/**: Safety system tests

### `/make/` - Build System
- **fw.mk**: Firmware build rules
- **tools.mk**: Tool installation and management
- **unittest.mk**: Unit testing framework
- Platform-specific makefiles: `linux.mk`, `macos.mk`, `windows.mk`

### `/ChibiOS_3.0.5/` - Real-time OS
- ChibiOS/RT operating system source code
- HAL (Hardware Abstraction Layer) implementations

### `/lispBM/` - Scripting Engine
- LispBM embedded Lisp interpreter
- Custom extensions for VESC functionality

### `/blackmagic/` - Debug Tools
- Black Magic Probe debugger integration

### `/qmlui/` - User Interface
- QML-based user interface components

## Configuration Files
- **chconf.h**: ChibiOS configuration
- **halconf.h**: Hardware Abstraction Layer configuration  
- **mcuconf.h**: Microcontroller unit configuration
- **stm32f4xx_conf.h**: STM32F4 peripheral configuration

## Build Output
- **build/**: Compiled firmware binaries (gitignored)
- **downloads/**: Downloaded toolchain components
- **tools/**: Development tools and Qt installation