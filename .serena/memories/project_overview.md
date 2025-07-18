# VESC Firmware Project Overview

## Project Purpose
VESC (Vedder Electronic Speed Controller) firmware is an open-source motor controller firmware for DC/BLDC/FOC (Field Oriented Control) motors. This is the official firmware repository for the VESC project, which is widely used in electric vehicles, robotics, and various motor control applications.

## Key Features
- Supports multiple motor control algorithms (BLDC, FOC)
- Battery Management System (BMS) integration  
- Advanced sensor support (encoders, IMU)
- Multiple communication interfaces (USB, CAN, UART)
- Configurable via VESC Tool GUI application
- Support for many hardware variants and boards
- LispBM scripting language integration for custom logic

## Project Website
- Main project: https://vesc-project.com/
- Repository: https://github.com/vedderb/bldc
- License: GNU GPL v3.0

## Current Version
- Major: 6
- Minor: 06  
- Test Version: 4

## Target Platforms
- STM32F4 microcontrollers
- Various VESC hardware boards (100_250, 100_500, etc.)
- Custom hardware configurations supported