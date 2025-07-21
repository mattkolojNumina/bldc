/*
	Copyright 2025 VESC Enhanced Features - Hardware Adaptations
	
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

#ifndef HW_FLIPSKY_75200_PRO_V2_ADAPTATIONS_H_
#define HW_FLIPSKY_75200_PRO_V2_ADAPTATIONS_H_

#include "conf_general.h"
#include "hw.h"

/*
 * Hardware-specific adaptations for Flipsky 75200 Pro V2.0
 * 
 * CRITICAL HARDWARE CONSTRAINTS:
 * - NO HARDWARE PHASE FILTERS (most units lack them despite claims)
 * - Single temperature sensor (inadequate coverage)
 * - Low-side current sensing only
 * - MOSFET quality/reliability issues
 * - Gate driver limitations (EG3112)
 * - Capacitor mounting issues
 * - Quality control problems
 */

// Hardware identification
#define HW_FLIPSKY_75200_PRO_V2
#define HW_HAS_PHASE_FILTERS				0		// CRITICAL: Most units lack phase filters
#define HW_SINGLE_TEMPERATURE_SENSOR		1		// Only one temp sensor
#define HW_LOW_SIDE_CURRENT_SENSING_ONLY	1		// Current sensing limitation
#define HW_MOSFET_QUALITY_ISSUES			1		// Known MOSFET reliability problems

// Enhanced HFI adaptations for hardware without phase filters
#define HW_HFI_VOLTAGE_SCALE_MAX			1.5f	// Reduced from 2.0f (no phase filters)
#define HW_HFI_VOLTAGE_SCALE_MIN			0.3f	// Reduced from 0.5f (safety margin)
#define HW_HFI_BANDWIDTH_HZ_MAX				300.0f	// Reduced from 500.0f (no phase filters)
#define HW_HFI_BANDWIDTH_HZ_MIN				50.0f	// Minimum for stability
#define HW_HFI_INJECTION_AMPLITUDE_MAX		0.8f	// Reduced injection amplitude
#define HW_HFI_NOISE_FLOOR_COMPENSATION		1.5f	// Higher noise floor without filters
#define HW_HFI_SOFTWARE_FILTER_ENABLED		1		// Enable software filtering
#define HW_HFI_CONSERVATIVE_MODE			1		// Conservative mode for hardware without filters

// Switching frequency adaptations for gate driver limitations
#define HW_SWITCHING_FREQUENCY_MAX			16000	// Reduced from 20kHz (gate driver limit)
#define HW_SWITCHING_FREQUENCY_MIN			10000	// Minimum for hub motor efficiency
#define HW_SWITCHING_FREQUENCY_SAFE			13000	// Safe frequency for EG3112 gate driver
#define HW_DEAD_TIME_NS_MIN					500		// Increased dead time for safety
#define HW_GATE_DRIVER_CURRENT_LIMIT		1.0f	// Gate driver current limitation

// Temperature monitoring adaptations for single sensor
#define HW_TEMP_SENSOR_COUNT				1		// Only one temperature sensor
#define HW_TEMP_SENSOR_LOCATION_CORNER		1		// Sensor in corner (not optimal)
#define HW_TEMP_ESTIMATION_REQUIRED			1		// Need temperature estimation
#define HW_TEMP_SAFETY_MARGIN				10.0f	// Extra safety margin due to poor sensor placement
#define HW_TEMP_DERATING_AGGRESSIVE			1		// Aggressive derating for single sensor

// Current sensing adaptations for low-side shunt only
#define HW_CURRENT_SENSING_LOW_SIDE_ONLY	1		// No high-side current sensing
#define HW_CURRENT_SENSING_LIMITED_ACCURACY	1		// Reduced accuracy during certain PWM states
#define HW_CURRENT_OFFSET_COMPENSATION		1		// Enhanced offset compensation required
#define HW_CURRENT_MEASUREMENT_WINDOW_us	50		// Minimum measurement window for accuracy

// MOSFET and power stage adaptations
#define HW_MOSFET_FAILURE_DETECTION			1		// Enable enhanced failure detection
#define HW_MOSFET_THERMAL_PROTECTION		1		// Enhanced thermal protection
#define HW_MOSFET_GATE_RESISTOR_ISSUES		1		// Known gate resistor issues
#define HW_MOSFET_VOLTAGE_LIMIT_CONSERVATIVE 70.0f	// Conservative voltage limit
#define HW_MOSFET_CURRENT_LIMIT_CONSERVATIVE 180.0f	// Conservative current limit

// Capacitor reliability adaptations
#define HW_CAPACITOR_RELIABILITY_ISSUES		1		// Known capacitor mounting issues
#define HW_CAPACITOR_MONITORING_ENABLED		1		// Enhanced capacitor monitoring
#define HW_RIPPLE_CURRENT_LIMIT_FACTOR		0.8f	// Reduced ripple current limit

// Enhanced safety features for hardware issues
#define HW_ENHANCED_SAFETY_MONITORING		1		// Enable enhanced safety
#define HW_FAULT_DETECTION_AGGRESSIVE		1		// Aggressive fault detection
#define HW_SELF_TEST_ENHANCED				1		// Enhanced self-test procedures
#define HW_DIAGNOSTIC_VERBOSE				1		// Verbose diagnostic reporting

// Hardware-specific parameter limits
#define HW_CURRENT_MAX_SAFE					150.0f	// Conservative current limit
#define HW_VOLTAGE_MAX_SAFE					75.0f	// Conservative voltage limit (20S LiPo adjusted)
#define HW_POWER_MAX_SAFE					8000.0f	// Conservative power limit
#define HW_EFFICIENCY_TARGET_ADJUSTED		80.0f	// Adjusted efficiency target
#define HW_VOLTAGE_MAX_ABSOLUTE				84.0f	// 20S LiPo absolute maximum (4.2V * 20)

// Hardware-specific optimization parameters
#define HW_MTPA_TEMPERATURE_COMPENSATION_FACTOR	1.2f	// Increased compensation
#define HW_FIELD_WEAKENING_VOLTAGE_MARGIN		0.90f	// Reduced voltage margin (was 0.95f)
#define HW_FIELD_WEAKENING_BANDWIDTH_HZ			80.0f	// Reduced bandwidth (was 100.0f)

// Hardware-specific test parameters
#define HW_TEST_VOLTAGE_INJECTION_SAFE		0.5f	// Safe injection voltage for tests
#define HW_TEST_CURRENT_LIMIT_SAFE			100.0f	// Safe current limit for tests
#define HW_TEST_TEMPERATURE_LIMIT_SAFE		70.0f	// Safe temperature limit for tests

// Hardware compatibility macros
#define HW_REQUIRES_PHASE_FILTER_DISABLE()	do { \
	/* Critical: Disable phase filter in VESC Tool to prevent damage */ \
	/* This must be done in software configuration */ \
} while(0)

#define HW_REQUIRES_CONSERVATIVE_SETTINGS()	do { \
	/* Apply conservative settings for hardware limitations */ \
} while(0)

#define HW_ENHANCED_FAULT_DETECTION()		do { \
	/* Enhanced fault detection for known hardware issues */ \
} while(0)

// Hardware-specific initialization sequence
void hw_flipsky_75200_pro_v2_init_adaptations(void);
void hw_flipsky_75200_pro_v2_apply_safety_limits(void);
void hw_flipsky_75200_pro_v2_configure_enhanced_features(void);
bool hw_flipsky_75200_pro_v2_validate_configuration(void);
void hw_flipsky_75200_pro_v2_handle_known_issues(void);

// Hardware-specific diagnostic functions
typedef struct {
	bool phase_filter_present;
	bool temperature_sensor_valid;
	bool current_sensing_calibrated;
	bool mosfet_health_ok;
	bool capacitor_health_ok;
	bool gate_driver_ok;
	bool thermal_estimation_enabled;
	bool thermal_protection_enhanced;
	bool mosfet_protection_enhanced;
	float hardware_score;
	uint32_t fault_count;
	uint32_t warning_count;
} hw_flipsky_75200_diagnostics_t;

hw_flipsky_75200_diagnostics_t hw_flipsky_75200_pro_v2_run_diagnostics(void);
void hw_flipsky_75200_pro_v2_print_hardware_warnings(void);
void hw_flipsky_75200_pro_v2_update_diagnostics(void);

// Safety mechanism functions for known failure modes
void hw_flipsky_75200_pro_v2_apply_phase_filter_safety(void);
void hw_flipsky_75200_pro_v2_apply_thermal_safety(void);
void hw_flipsky_75200_pro_v2_apply_mosfet_safety(void);
void hw_flipsky_75200_pro_v2_apply_capacitor_safety(void);
void hw_flipsky_75200_pro_v2_apply_gate_driver_safety(void);
void hw_flipsky_75200_pro_v2_apply_high_voltage_safety(void);
bool hw_flipsky_75200_pro_v2_validate_safety_mechanisms(void);

#endif /* HW_FLIPSKY_75200_PRO_V2_ADAPTATIONS_H_ */