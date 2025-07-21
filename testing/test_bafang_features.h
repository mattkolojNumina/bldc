/*
	Copyright 2024 VESC Enhanced Features Test Suite
	
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

#ifndef TEST_BAFANG_FEATURES_H_
#define TEST_BAFANG_FEATURES_H_

#include "stdbool.h"
#include "stdint.h"

// Test result structure
typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    char last_error[256];
} test_results_t;

// Test function declarations

// Initialize test suite
void test_bafang_features_init(void);

// Individual test functions
bool test_adaptive_params_init(void);
bool test_adaptive_params_temperature_response(void);
bool test_telemetry_init(void);
bool test_telemetry_data_collection(void);
bool test_field_optimization_init(void);
bool test_field_optimization_updates(void);
bool test_system_integration(void);
bool test_error_handling_safety(void);
bool test_enhanced_hfi_init(void);
bool test_enhanced_hfi_signal_quality(void);
bool test_enhanced_hfi_voltage_adaptation(void);

// Hardware-specific test functions for Flipsky 75200 Pro V2.0
bool test_hardware_compatibility_flipsky_75200_pro_v2(void);
bool test_hardware_phase_filter_absence(void);
bool test_hardware_current_sensing_low_side(void);
bool test_hardware_thermal_management_single_sensor(void);
bool test_hardware_mosfet_protection_limits(void);
bool test_hardware_switching_frequency_constraints(void);
bool test_hardware_20s_lipo_compatibility(void);
bool test_hardware_diagnostic_system(void);
bool test_hardware_safety_mechanisms(void);
bool test_enhanced_hfi_temperature_compensation(void);
bool test_enhanced_mtpa_init(void);
bool test_enhanced_mtpa_temperature_compensation(void);
bool test_enhanced_mtpa_nonlinear_optimization(void);
bool test_enhanced_mtpa_efficiency_calculation(void);
bool test_enhanced_field_weakening_init(void);
bool test_enhanced_field_weakening_two_stage(void);
bool test_enhanced_field_weakening_mtpv(void);
bool test_enhanced_field_weakening_efficiency(void);

// Comprehensive integration test
bool test_comprehensive_system_integration(void);

// Run all tests
void test_bafang_features_run_all(void);

// Get test results
test_results_t test_bafang_features_get_results(void);

#endif /* TEST_BAFANG_FEATURES_H_ */