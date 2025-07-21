/*
	Copyright 2016 - 2024 Benjamin Vedder	benjamin@vedder.se
	Copyright 2024 Custom configuration for Bafang 500W Hub Motor

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The VESC firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef HW_BAFANG_500W_HUB_H_
#define HW_BAFANG_500W_HUB_H_

#define HW_NAME					"BAFANG_1000W_HUB"
#define FW_NAME					"BAFANG_1000W_HUB_2024"

// Include motor and app configurations
#include "mcconf_bafang_500w_hub.h"
#include "appconf_bafang_500w_hub.h"

// Override specific settings for Bafang hub motor optimization
// Note: This file should be used with FSESC_75_200_ALU as build target
// The make system will link this with the appropriate FSESC base configuration

// Motor configuration overrides for optimized Bafang operation
#define MCCONF_FOC_F_ZV					20000.0    // Research-optimized 20kHz switching frequency
#define MCCONF_L_MAX_ABS_CURRENT		150.0      // Optimized absolute current for hub motor

// Dead time optimization for hub motor efficiency  
#define HW_DEAD_TIME_NSEC		400.0          // Optimized dead time for hub motor

// Current limits for Bafang hub motor with FSESC_75_200_ALU
// FSESC_75_200_ALU capability: 200A continuous at 50V, 150A at 75V, 300A peak
// Bafang optimization: Conservative limits for thermal safety and longevity
#define HW_LIM_CURRENT			-120.0, 120.0  // Phase current (120A for optimized 1000W operation)
#define HW_LIM_CURRENT_IN		-80.0, 80.0    // Battery current (80A for optimized 1000W @ 48V) 
#define HW_LIM_CURRENT_ABS		0.0, 180.0     // Absolute current (optimized within FSESC safe limits)

#endif /* HW_BAFANG_500W_HUB_H_ */