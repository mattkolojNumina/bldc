# VESC Firmware Development Commands

## Build Commands

### Install Development Environment
```bash
# Install ARM toolchain
make arm_sdk_install

# Install Qt development tools
make qt_install
```

### Firmware Building
```bash
# Show available board targets
make

# Build firmware for specific board (example: 100_250)
make 100_250

# Build firmware for default target
make fw

# Build firmware for custom hardware configuration
make fw_custom HW_SRC=path/to/hw_source.c HW_HEADER=path/to/hw_header.h

# Build all firmware variants
make all_fw

# Package firmware for distribution
make all_fw_package
```

### Cleaning
```bash
# Clean specific board build
make 100_250_clean

# Clean custom build
make fw_custom_clean
```

### Flashing Firmware
```bash
# Flash via SWD/JTAG debugger (requires STLink or similar)
make 100_250_flash

# Flash custom firmware
make fw_custom_flash
```

## Testing Commands

### Unit Tests
```bash
# Build all unit tests
make all_ut

# Run all unit tests with XML output to files
make all_ut_xml

# Run all unit tests with console output
make all_ut_run
```

### Build Validation
```bash
# Build all hardware variants to check for issues
# (Run from build_all directory)
cd build_all && ./rebuild_all
```

## Development Tools

### IDE Setup
```bash
# Open Qt Creator IDE
tools/Qt/Tools/QtCreator/bin/qtcreator

# Open VESC project file
# File: Project/Qt Creator/vesc.pro
```

### Hardware Programming Setup (Linux)
```bash
# Install udev rules for STLink (run once)
wget vedder.se/Temp/49-stlinkv2.rules
sudo mv 49-stlinkv2.rules /etc/udev/rules.d/
sudo udevadm trigger
```

## System Commands (Linux)

### Essential System Tools
```bash
# File operations
ls -la              # List files with details
find . -name "*.c"  # Find C source files
grep -r "pattern"   # Search for patterns in files

# Git operations
git status          # Check repository status
git log --oneline   # View commit history
git tag -a [version] [commit] -m "VESC Firmware Version [version]"
git push --tags     # Push tags for releases

# System monitoring
htop               # Process monitor
df -h              # Disk usage
free -h            # Memory usage
```

### Prerequisites Installation (Ubuntu/Debian)
```bash
sudo apt install git build-essential libgl-dev libxcb-xinerama0 wget git-gui
```

### Prerequisites Installation (macOS)
```bash
brew install stlink
brew install openocd
```

## Verbose Output
Add `V=1` to any make command for verbose build output:
```bash
make 100_250 V=1
```