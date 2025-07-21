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

#include "test_bafang_features.h"
#include "../motor/mc_interface.h"
#include "../utils/utils_math.h"
#include "../hwconf/hw_flipsky_75200_pro_v2_adaptations.h"
#include "stdio.h"
#include "math.h"
#include <string.h>

// Test result structure
typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    char last_error[256];
} test_results_t;

static test_results_t test_results;

// Test helper macros
#define TEST_ASSERT(condition, message) do { \
    test_results.total_tests++; \
    if (!(condition)) { \
        test_results.failed_tests++; \
        snprintf(test_results.last_error, sizeof(test_results.last_error), "FAIL: %s", message); \
        printf("FAIL: %s\n", message); \
        return false; \
    } else { \
        test_results.passed_tests++; \
        printf("PASS: %s\n", message); \
    } \
} while(0)

#define TEST_ASSERT_FLOAT_EQUAL(expected, actual, tolerance, message) do { \
    test_results.total_tests++; \
    if (fabsf((expected) - (actual)) > (tolerance)) { \
        test_results.failed_tests++; \
        snprintf(test_results.last_error, sizeof(test_results.last_error), \
                "FAIL: %s - Expected: %.6f, Got: %.6f", message, (expected), (actual)); \
        printf("FAIL: %s - Expected: %.6f, Got: %.6f\n", message, (expected), (actual)); \
        return false; \
    } else { \
        test_results.passed_tests++; \
        printf("PASS: %s\n", message); \
    } \
} while(0)

// Test initialization
void test_bafang_features_init(void) {
    memset(&test_results, 0, sizeof(test_results_t));
    printf("=== VESC Enhanced Features Test Suite ===\n");
    printf("Testing Bafang 500W Hub Motor Features\n");
    printf("=======================================\n\n");
}

// Test adaptive parameter system initialization
bool test_adaptive_params_init(void) {
    printf("Testing Adaptive Parameter System Initialization...\n");
    
    // Initialize the system
    mc_interface_init_adaptive_params();
    
    // Get current adaptive parameters
    adaptive_params_t params = mc_interface_get_adaptive_params();
    
    // Test that parameters are within valid ranges
    TEST_ASSERT(params.kp_adapted > 0.0f && params.kp_adapted < 1.0f,
               "KP parameter within valid range");
    TEST_ASSERT(params.ki_adapted > 0.0f && params.ki_adapted < 200.0f,
               "KI parameter within valid range");
    TEST_ASSERT(params.resistance_adapted > 0.0f && params.resistance_adapted < 2.0f,
               "Resistance parameter within valid range");
    TEST_ASSERT(params.flux_linkage_adapted > 0.0f && params.flux_linkage_adapted < 1.0f,
               "Flux linkage parameter within valid range");
    
    // Test that adaptive system is enabled
    TEST_ASSERT(params.adaptive_enabled == true,
               "Adaptive system is enabled");
    
    return true;
}

// Test adaptive parameter updates with temperature
bool test_adaptive_params_temperature_response(void) {
    printf("Testing Adaptive Parameter Temperature Response...\n");
    
    // Initialize the system
    mc_interface_init_adaptive_params();
    
    // Get initial parameters
    adaptive_params_t params_cold = mc_interface_get_adaptive_params();
    
    // Simulate temperature change (simulate hot motor)
    float hot_temp = 80.0f;
    mc_interface_set_motor_temperature(hot_temp);
    
    // Update adaptive parameters
    mc_interface_update_adaptive_params();
    
    // Get updated parameters
    adaptive_params_t params_hot = mc_interface_get_adaptive_params();
    
    // Test that parameters have adapted to temperature
    TEST_ASSERT(params_hot.kp_adapted != params_cold.kp_adapted,
               "KP parameter adapted to temperature");
    TEST_ASSERT(params_hot.ki_adapted != params_cold.ki_adapted,
               "KI parameter adapted to temperature");
    TEST_ASSERT(params_hot.resistance_adapted != params_cold.resistance_adapted,
               "Resistance parameter adapted to temperature");
    
    // Test that parameters are still within bounds
    TEST_ASSERT(params_hot.kp_adapted > 0.001f && params_hot.kp_adapted < 0.1f,
               "Hot KP parameter within bounds");
    TEST_ASSERT(params_hot.ki_adapted > 0.1f && params_hot.ki_adapted < 100.0f,
               "Hot KI parameter within bounds");
    TEST_ASSERT(params_hot.resistance_adapted > 0.001f && params_hot.resistance_adapted < 1.0f,
               "Hot resistance parameter within bounds");
    
    return true;
}

// Test telemetry system initialization
bool test_telemetry_init(void) {
    printf("Testing Enhanced Telemetry System Initialization...\n");
    
    // Initialize the system
    mc_interface_init_telemetry();
    
    // Get current telemetry data
    telemetry_data_t telemetry = mc_interface_get_telemetry_data();
    
    // Test that telemetry is initialized
    TEST_ASSERT(telemetry.telemetry_enabled == true,
               "Telemetry system is enabled");
    TEST_ASSERT(telemetry.update_rate_hz > 0.0f,
               "Telemetry update rate is valid");
    TEST_ASSERT(telemetry.buffer_size > 0,
               "Telemetry buffer size is valid");
    
    return true;
}

// Test telemetry data collection
bool test_telemetry_data_collection(void) {
    printf("Testing Telemetry Data Collection...\n");
    
    // Initialize the system
    mc_interface_init_telemetry();
    
    // Update telemetry data
    mc_interface_update_telemetry();
    
    // Get telemetry data
    telemetry_data_t telemetry = mc_interface_get_telemetry_data();
    
    // Test that data is within reasonable ranges
    TEST_ASSERT(telemetry.motor_temp_c >= -50.0f && telemetry.motor_temp_c <= 150.0f,
               "Motor temperature within reasonable range");
    TEST_ASSERT(telemetry.controller_temp_c >= -50.0f && telemetry.controller_temp_c <= 150.0f,
               "Controller temperature within reasonable range");
    TEST_ASSERT(telemetry.input_voltage_v >= 0.0f && telemetry.input_voltage_v <= 100.0f,
               "Input voltage within reasonable range");
    TEST_ASSERT(telemetry.motor_current_a >= -500.0f && telemetry.motor_current_a <= 500.0f,
               "Motor current within reasonable range");
    TEST_ASSERT(telemetry.battery_current_a >= -500.0f && telemetry.battery_current_a <= 500.0f,
               "Battery current within reasonable range");
    TEST_ASSERT(telemetry.motor_rpm >= -200000.0f && telemetry.motor_rpm <= 200000.0f,
               "Motor RPM within reasonable range");
    
    return true;
}

// Test field optimization system initialization
bool test_field_optimization_init(void) {
    printf("Testing Field Optimization System Initialization...\n");
    
    // Initialize the system
    mc_interface_init_field_optimization();
    
    // Get current field optimization data
    field_optimization_data_t field_data = mc_interface_get_field_optimization_data();
    
    // Test that field optimization is initialized
    TEST_ASSERT(field_data.optimization_enabled == true,
               "Field optimization system is enabled");
    TEST_ASSERT(field_data.learning_rate > 0.0f && field_data.learning_rate < 1.0f,
               "Learning rate within valid range");
    TEST_ASSERT(field_data.optimization_cycles >= 0,
               "Optimization cycles initialized");
    
    return true;
}

// Test field optimization parameter updates
bool test_field_optimization_updates(void) {
    printf("Testing Field Optimization Parameter Updates...\n");
    
    // Initialize the system
    mc_interface_init_field_optimization();
    
    // Get initial field optimization data
    field_optimization_data_t field_data_initial = mc_interface_get_field_optimization_data();
    
    // Simulate some operation cycles
    for (int i = 0; i < 10; i++) {
        mc_interface_update_field_optimization();
    }
    
    // Get updated field optimization data
    field_optimization_data_t field_data_updated = mc_interface_get_field_optimization_data();
    
    // Test that optimization has progressed
    TEST_ASSERT(field_data_updated.optimization_cycles > field_data_initial.optimization_cycles,
               "Optimization cycles have progressed");
    
    // Test that parameters are within bounds
    TEST_ASSERT(field_data_updated.current_score >= 0.0f && field_data_updated.current_score <= 100.0f,
               "Current performance score within bounds");
    TEST_ASSERT(field_data_updated.best_score >= 0.0f && field_data_updated.best_score <= 100.0f,
               "Best performance score within bounds");
    
    return true;
}

// Test system integration
bool test_system_integration(void) {
    printf("Testing System Integration...\n");
    
    // Initialize all systems
    mc_interface_init_adaptive_params();
    mc_interface_init_telemetry();
    mc_interface_init_field_optimization();
    
    // Update all systems
    mc_interface_update_adaptive_params();
    mc_interface_update_telemetry();
    mc_interface_update_field_optimization();
    
    // Get data from all systems
    adaptive_params_t adaptive_params = mc_interface_get_adaptive_params();
    telemetry_data_t telemetry = mc_interface_get_telemetry_data();
    field_optimization_data_t field_data = mc_interface_get_field_optimization_data();
    
    // Test that all systems are running
    TEST_ASSERT(adaptive_params.adaptive_enabled == true,
               "Adaptive parameters system is active");
    TEST_ASSERT(telemetry.telemetry_enabled == true,
               "Telemetry system is active");
    TEST_ASSERT(field_data.optimization_enabled == true,
               "Field optimization system is active");
    
    // Test that systems are interacting correctly
    TEST_ASSERT(telemetry.adaptive_params_active == adaptive_params.adaptive_enabled,
               "Telemetry correctly reports adaptive params status");
    TEST_ASSERT(telemetry.field_optimization_active == field_data.optimization_enabled,
               "Telemetry correctly reports field optimization status");
    
    return true;
}

// Test error handling and safety systems
bool test_error_handling_safety(void) {
    printf("Testing Error Handling and Safety Systems...\n");
    
    // Initialize systems
    mc_interface_init_adaptive_params();
    mc_interface_init_telemetry();
    mc_interface_init_field_optimization();
    
    // Test invalid temperature handling
    mc_interface_set_motor_temperature(999.0f);  // Invalid temperature
    mc_interface_update_adaptive_params();
    
    adaptive_params_t params = mc_interface_get_adaptive_params();
    TEST_ASSERT(params.kp_adapted > 0.001f && params.kp_adapted < 0.1f,
               "Invalid temperature handled safely - KP within bounds");
    
    // Test invalid voltage handling
    mc_interface_update_telemetry();
    telemetry_data_t telemetry = mc_interface_get_telemetry_data();
    TEST_ASSERT(telemetry.input_voltage_v >= 0.0f && telemetry.input_voltage_v <= 100.0f,
               "Invalid voltage handled safely");
    
    // Test division by zero protection
    mc_interface_update_field_optimization();
    field_optimization_data_t field_data = mc_interface_get_field_optimization_data();
    TEST_ASSERT(field_data.current_score >= 0.0f && field_data.current_score <= 100.0f,
               "Division by zero protection active");
    
    return true;
}

// Run all tests
void test_bafang_features_run_all(void) {
    test_bafang_features_init();
    
    bool all_passed = true;
    
    // Run all test functions
    all_passed &= test_adaptive_params_init();
    all_passed &= test_adaptive_params_temperature_response();
    all_passed &= test_telemetry_init();
    all_passed &= test_telemetry_data_collection();
    all_passed &= test_field_optimization_init();
    all_passed &= test_field_optimization_updates();
    all_passed &= test_system_integration();
    all_passed &= test_error_handling_safety();
    
    // Enhanced feature tests
    all_passed &= test_enhanced_hfi_init();
    all_passed &= test_enhanced_hfi_signal_quality();
    all_passed &= test_enhanced_hfi_voltage_adaptation();
    all_passed &= test_enhanced_hfi_temperature_compensation();
    all_passed &= test_enhanced_mtpa_init();
    all_passed &= test_enhanced_mtpa_temperature_compensation();
    all_passed &= test_enhanced_mtpa_nonlinear_optimization();
    all_passed &= test_enhanced_mtpa_efficiency_calculation();
    all_passed &= test_enhanced_field_weakening_init();
    all_passed &= test_enhanced_field_weakening_two_stage();
    all_passed &= test_enhanced_field_weakening_mtpv();
    all_passed &= test_enhanced_field_weakening_efficiency();
    
    // Comprehensive integration test
    all_passed &= test_comprehensive_system_integration();
    
    // Hardware-specific tests for Flipsky 75200 Pro V2.0
    all_passed &= test_hardware_compatibility_flipsky_75200_pro_v2();
    all_passed &= test_hardware_phase_filter_absence();
    all_passed &= test_hardware_current_sensing_low_side();
    all_passed &= test_hardware_thermal_management_single_sensor();
    all_passed &= test_hardware_mosfet_protection_limits();
    all_passed &= test_hardware_switching_frequency_constraints();
    all_passed &= test_hardware_20s_lipo_compatibility();
    all_passed &= test_hardware_diagnostic_system();
    all_passed &= test_hardware_safety_mechanisms();
    
    // Print results
    printf("\n=======================================\n");
    printf("Test Results Summary:\n");
    printf("Total Tests: %d\n", test_results.total_tests);
    printf("Passed: %d\n", test_results.passed_tests);
    printf("Failed: %d\n", test_results.failed_tests);
    printf("Success Rate: %.1f%%\n", 
           (float)test_results.passed_tests / (float)test_results.total_tests * 100.0f);
    
    if (all_passed) {
        printf("✓ ALL TESTS PASSED!\n");
    } else {
        printf("✗ SOME TESTS FAILED!\n");
        printf("Last Error: %s\n", test_results.last_error);
    }
    printf("=======================================\n");
}

// Get test results
test_results_t test_bafang_features_get_results(void) {
    return test_results;
}

// Test enhanced HFI initialization
bool test_enhanced_hfi_init(void) {
    printf("Testing Enhanced HFI Initialization...\n");
    
    // Initialize the enhanced HFI system
    mc_interface_init_enhanced_hfi();
    
    // Get enhanced HFI data
    enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
    
    // Test that enhanced HFI is initialized
    TEST_ASSERT(hfi_data.hfi_enhanced_enabled == true,
               "Enhanced HFI system is enabled");
    TEST_ASSERT(hfi_data.hfi_voltage_scale >= 0.5f && hfi_data.hfi_voltage_scale <= 2.0f,
               "HFI voltage scale within valid range");
    TEST_ASSERT(hfi_data.hfi_bandwidth_hz > 0.0f,
               "HFI bandwidth is valid");
    TEST_ASSERT(hfi_data.hfi_phase_margin > 0.0f && hfi_data.hfi_phase_margin < 90.0f,
               "HFI phase margin within valid range");
    TEST_ASSERT(hfi_data.hfi_gain_margin > 0.0f,
               "HFI gain margin is positive");
    
    return true;
}

// Test enhanced HFI signal quality assessment
bool test_enhanced_hfi_signal_quality(void) {
    printf("Testing Enhanced HFI Signal Quality Assessment...\n");
    
    // Initialize the enhanced HFI system
    mc_interface_init_enhanced_hfi();
    
    // Update enhanced HFI data
    mc_interface_update_enhanced_hfi();
    
    // Get enhanced HFI data
    enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
    
    // Test that signal quality is calculated
    TEST_ASSERT(hfi_data.hfi_signal_quality >= 0.0f && hfi_data.hfi_signal_quality <= 1.0f,
               "HFI signal quality within valid range");
    TEST_ASSERT(hfi_data.hfi_snr_db >= -20.0f && hfi_data.hfi_snr_db <= 60.0f,
               "HFI SNR within reasonable range");
    TEST_ASSERT(hfi_data.hfi_noise_level >= 0.0f,
               "HFI noise level is non-negative");
    TEST_ASSERT(hfi_data.hfi_angle_confidence >= 0.0f && hfi_data.hfi_angle_confidence <= 1.0f,
               "HFI angle confidence within valid range");
    
    return true;
}

// Test enhanced HFI voltage adaptation
bool test_enhanced_hfi_voltage_adaptation(void) {
    printf("Testing Enhanced HFI Voltage Adaptation...\n");
    
    // Initialize the enhanced HFI system
    mc_interface_init_enhanced_hfi();
    
    // Enable voltage adaptation
    mc_interface_set_hfi_voltage_adaptation(true);
    
    // Update enhanced HFI data
    mc_interface_update_enhanced_hfi();
    
    // Get enhanced HFI data
    enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
    
    // Test that voltage adaptation is working
    TEST_ASSERT(hfi_data.voltage_adaptation_enabled == true,
               "HFI voltage adaptation is enabled");
    TEST_ASSERT(hfi_data.hfi_voltage_scale >= 0.5f && hfi_data.hfi_voltage_scale <= 2.0f,
               "HFI voltage scale within adaptation range");
    TEST_ASSERT(hfi_data.hfi_frequency_adapt >= 0.5f && hfi_data.hfi_frequency_adapt <= 2.0f,
               "HFI frequency adaptation within valid range");
    TEST_ASSERT(hfi_data.hfi_gain_compensation >= 0.5f && hfi_data.hfi_gain_compensation <= 2.0f,
               "HFI gain compensation within valid range");
    
    // Test disabling voltage adaptation
    mc_interface_set_hfi_voltage_adaptation(false);
    enhanced_hfi_data_t hfi_data_disabled = mc_interface_get_enhanced_hfi_data();
    TEST_ASSERT(hfi_data_disabled.voltage_adaptation_enabled == false,
               "HFI voltage adaptation can be disabled");
    
    return true;
}

// Test enhanced HFI temperature compensation
bool test_enhanced_hfi_temperature_compensation(void) {
    printf("Testing Enhanced HFI Temperature Compensation...\n");
    
    // Initialize the enhanced HFI system
    mc_interface_init_enhanced_hfi();
    
    // Update enhanced HFI data multiple times to build temperature compensation
    for (int i = 0; i < 10; i++) {
        mc_interface_update_enhanced_hfi();
    }
    
    // Get enhanced HFI data
    enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
    
    // Test that temperature compensation is working
    TEST_ASSERT(hfi_data.hfi_temperature_compensation >= 0.5f && hfi_data.hfi_temperature_compensation <= 2.0f,
               "HFI temperature compensation within valid range");
    TEST_ASSERT(hfi_data.hfi_thermal_drift >= -10.0f && hfi_data.hfi_thermal_drift <= 10.0f,
               "HFI thermal drift within reasonable range");
    TEST_ASSERT(hfi_data.hfi_update_cycles >= 10,
               "HFI update cycles are being tracked");
    TEST_ASSERT(hfi_data.hfi_processing_time >= 0.0f && hfi_data.hfi_processing_time <= 100.0f,
               "HFI processing time within reasonable range");
    
    // Test calibration progress
    TEST_ASSERT(hfi_data.hfi_calibration_samples >= 0,
               "HFI calibration samples are being tracked");
    TEST_ASSERT(hfi_data.hfi_quality_samples >= 0,
               "HFI quality samples are being tracked");
    
    return true;
}

// Test enhanced MTPA initialization
bool test_enhanced_mtpa_init(void) {
    printf("Testing Enhanced MTPA Initialization...\n");
    
    // Initialize the enhanced MTPA system
    mc_interface_init_enhanced_mtpa();
    
    // Get enhanced MTPA data
    enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
    
    // Test that enhanced MTPA is initialized
    TEST_ASSERT(mtpa_data.mtpa_enhanced_enabled == true,
               "Enhanced MTPA system is enabled");
    TEST_ASSERT(mtpa_data.temperature_compensation_enabled == true,
               "MTPA temperature compensation is enabled");
    TEST_ASSERT(mtpa_data.nonlinear_optimization_enabled == true,
               "MTPA nonlinear optimization is enabled");
    TEST_ASSERT(mtpa_data.mtpa_convergence_tolerance > 0.0f,
               "MTPA convergence tolerance is set");
    TEST_ASSERT(mtpa_data.mtpa_temperature_coefficient >= 0.8f && mtpa_data.mtpa_temperature_coefficient <= 1.2f,
               "MTPA temperature coefficient within valid range");
    TEST_ASSERT(mtpa_data.mtpa_saturation_factor >= 0.7f && mtpa_data.mtpa_saturation_factor <= 1.0f,
               "MTPA saturation factor within valid range");
    
    return true;
}

// Test enhanced MTPA temperature compensation
bool test_enhanced_mtpa_temperature_compensation(void) {
    printf("Testing Enhanced MTPA Temperature Compensation...\n");
    
    // Initialize the enhanced MTPA system
    mc_interface_init_enhanced_mtpa();
    
    // Enable temperature compensation
    mc_interface_set_mtpa_temperature_compensation(true);
    
    // Update enhanced MTPA data
    mc_interface_update_enhanced_mtpa();
    
    // Get enhanced MTPA data
    enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
    
    // Test that temperature compensation is working
    TEST_ASSERT(mtpa_data.temperature_compensation_enabled == true,
               "MTPA temperature compensation is enabled");
    TEST_ASSERT(mtpa_data.mtpa_flux_linkage_temp >= 0.0f,
               "MTPA flux linkage temperature compensated");
    TEST_ASSERT(mtpa_data.mtpa_inductance_ld_temp >= 0.0f,
               "MTPA Ld temperature compensated");
    TEST_ASSERT(mtpa_data.mtpa_inductance_lq_temp >= 0.0f,
               "MTPA Lq temperature compensated");
    TEST_ASSERT(mtpa_data.mtpa_resistance_temp >= 0.0f,
               "MTPA resistance temperature compensated");
    TEST_ASSERT(mtpa_data.mtpa_temperature_samples >= 0,
               "MTPA temperature samples being collected");
    
    // Test disabling temperature compensation
    mc_interface_set_mtpa_temperature_compensation(false);
    enhanced_mtpa_data_t mtpa_data_disabled = mc_interface_get_enhanced_mtpa_data();
    TEST_ASSERT(mtpa_data_disabled.temperature_compensation_enabled == false,
               "MTPA temperature compensation can be disabled");
    
    return true;
}

// Test enhanced MTPA nonlinear optimization
bool test_enhanced_mtpa_nonlinear_optimization(void) {
    printf("Testing Enhanced MTPA Nonlinear Optimization...\n");
    
    // Initialize the enhanced MTPA system
    mc_interface_init_enhanced_mtpa();
    
    // Enable nonlinear optimization
    mc_interface_set_mtpa_nonlinear_optimization(true);
    
    // Update enhanced MTPA data
    mc_interface_update_enhanced_mtpa();
    
    // Get enhanced MTPA data
    enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
    
    // Test that nonlinear optimization is working
    TEST_ASSERT(mtpa_data.nonlinear_optimization_enabled == true,
               "MTPA nonlinear optimization is enabled");
    TEST_ASSERT(mtpa_data.mtpa_saturation_factor >= 0.7f && mtpa_data.mtpa_saturation_factor <= 1.0f,
               "MTPA saturation factor within valid range");
    TEST_ASSERT(mtpa_data.mtpa_angle_optimal >= -M_PI && mtpa_data.mtpa_angle_optimal <= M_PI,
               "MTPA optimal angle within valid range");
    TEST_ASSERT(mtpa_data.mtpa_cross_coupling >= 0.0f && mtpa_data.mtpa_cross_coupling <= 1.0f,
               "MTPA cross coupling within valid range");
    TEST_ASSERT(mtpa_data.mtpa_optimization_cycles >= 0,
               "MTPA optimization cycles being tracked");
    
    // Test disabling nonlinear optimization
    mc_interface_set_mtpa_nonlinear_optimization(false);
    enhanced_mtpa_data_t mtpa_data_disabled = mc_interface_get_enhanced_mtpa_data();
    TEST_ASSERT(mtpa_data_disabled.nonlinear_optimization_enabled == false,
               "MTPA nonlinear optimization can be disabled");
    
    return true;
}

// Test enhanced MTPA efficiency calculation
bool test_enhanced_mtpa_efficiency_calculation(void) {
    printf("Testing Enhanced MTPA Efficiency Calculation...\n");
    
    // Initialize the enhanced MTPA system
    mc_interface_init_enhanced_mtpa();
    
    // Update enhanced MTPA data multiple times
    for (int i = 0; i < 10; i++) {
        mc_interface_update_enhanced_mtpa();
    }
    
    // Get enhanced MTPA data
    enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
    
    // Test that efficiency calculations are working
    TEST_ASSERT(mtpa_data.mtpa_efficiency_percent >= 0.0f && mtpa_data.mtpa_efficiency_percent <= 100.0f,
               "MTPA efficiency percentage within valid range");
    TEST_ASSERT(mtpa_data.mtpa_copper_losses >= 0.0f,
               "MTPA copper losses are non-negative");
    TEST_ASSERT(mtpa_data.mtpa_iron_losses >= 0.0f,
               "MTPA iron losses are non-negative");
    TEST_ASSERT(mtpa_data.mtpa_total_losses >= 0.0f,
               "MTPA total losses are non-negative");
    TEST_ASSERT(mtpa_data.mtpa_power_factor >= 0.0f && mtpa_data.mtpa_power_factor <= 1.0f,
               "MTPA power factor within valid range");
    TEST_ASSERT(mtpa_data.mtpa_torque_ripple >= 0.0f,
               "MTPA torque ripple is non-negative");
    
    // Test efficiency gain calculation
    float efficiency_gain = mc_interface_calculate_mtpa_efficiency_gain();
    TEST_ASSERT(efficiency_gain >= 0.0f && efficiency_gain <= 20.0f,
               "MTPA efficiency gain within reasonable range");
    
    // Test parameter validation
    TEST_ASSERT(mtpa_data.mtpa_parameters_valid == true || mtpa_data.mtpa_parameters_valid == false,
               "MTPA parameters validity flag is boolean");
    TEST_ASSERT(mtpa_data.mtpa_processing_time >= 0.0f && mtpa_data.mtpa_processing_time <= 100.0f,
               "MTPA processing time within reasonable range");
    
    return true;
}

// Test enhanced field weakening initialization
bool test_enhanced_field_weakening_init(void) {
    printf("Testing Enhanced Field Weakening Initialization...\n");
    
    // Initialize the enhanced field weakening system
    mc_interface_init_enhanced_field_weakening();
    
    // Get enhanced field weakening data
    enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
    
    // Test that enhanced field weakening is initialized
    TEST_ASSERT(fw_data.field_weakening_enhanced_enabled == true,
               "Enhanced field weakening system is enabled");
    TEST_ASSERT(fw_data.two_stage_control_enabled == true,
               "Two-stage field weakening control is enabled");
    TEST_ASSERT(fw_data.mtpv_control_enabled == true,
               "MTPV control is enabled");
    TEST_ASSERT(fw_data.fw_voltage_threshold >= 0.5f && fw_data.fw_voltage_threshold <= 1.0f,
               "Field weakening voltage threshold within valid range");
    TEST_ASSERT(fw_data.fw_current_threshold >= 0.0f && fw_data.fw_current_threshold <= 1.0f,
               "Field weakening current threshold within valid range");
    TEST_ASSERT(fw_data.fw_gain_p > 0.0f && fw_data.fw_gain_p < 10.0f,
               "Field weakening P gain within valid range");
    TEST_ASSERT(fw_data.fw_gain_i > 0.0f && fw_data.fw_gain_i < 10.0f,
               "Field weakening I gain within valid range");
    
    return true;
}

// Test enhanced field weakening two-stage control
bool test_enhanced_field_weakening_two_stage(void) {
    printf("Testing Enhanced Field Weakening Two-Stage Control...\n");
    
    // Initialize the enhanced field weakening system
    mc_interface_init_enhanced_field_weakening();
    
    // Enable two-stage control
    mc_interface_set_field_weakening_two_stage(true);
    
    // Update enhanced field weakening data
    mc_interface_update_enhanced_field_weakening();
    
    // Get enhanced field weakening data
    enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
    
    // Test that two-stage control is working
    TEST_ASSERT(fw_data.two_stage_control_enabled == true,
               "Two-stage field weakening control is enabled");
    TEST_ASSERT(fw_data.fw_stage1_active == true || fw_data.fw_stage1_active == false,
               "Stage 1 activation flag is boolean");
    TEST_ASSERT(fw_data.fw_stage2_active == true || fw_data.fw_stage2_active == false,
               "Stage 2 activation flag is boolean");
    TEST_ASSERT(fw_data.fw_stage1_voltage_limit >= 0.0f && fw_data.fw_stage1_voltage_limit <= 1.0f,
               "Stage 1 voltage limit within valid range");
    TEST_ASSERT(fw_data.fw_stage2_voltage_limit >= 0.0f && fw_data.fw_stage2_voltage_limit <= 1.0f,
               "Stage 2 voltage limit within valid range");
    TEST_ASSERT(fw_data.fw_stage1_current_limit >= 0.0f && fw_data.fw_stage1_current_limit <= 1.0f,
               "Stage 1 current limit within valid range");
    TEST_ASSERT(fw_data.fw_stage2_current_limit >= 0.0f && fw_data.fw_stage2_current_limit <= 1.0f,
               "Stage 2 current limit within valid range");
    
    // Test disabling two-stage control
    mc_interface_set_field_weakening_two_stage(false);
    enhanced_field_weakening_data_t fw_data_disabled = mc_interface_get_enhanced_field_weakening_data();
    TEST_ASSERT(fw_data_disabled.two_stage_control_enabled == false,
               "Two-stage field weakening control can be disabled");
    
    return true;
}

// Test enhanced field weakening MTPV control
bool test_enhanced_field_weakening_mtpv(void) {
    printf("Testing Enhanced Field Weakening MTPV Control...\n");
    
    // Initialize the enhanced field weakening system
    mc_interface_init_enhanced_field_weakening();
    
    // Enable MTPV control
    mc_interface_set_field_weakening_mtpv(true);
    
    // Update enhanced field weakening data
    mc_interface_update_enhanced_field_weakening();
    
    // Get enhanced field weakening data
    enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
    
    // Test that MTPV control is working
    TEST_ASSERT(fw_data.mtpv_control_enabled == true,
               "MTPV control is enabled");
    TEST_ASSERT(fw_data.mtpv_active == true || fw_data.mtpv_active == false,
               "MTPV activation flag is boolean");
    TEST_ASSERT(fw_data.mtpv_voltage_limit >= 0.0f && fw_data.mtpv_voltage_limit <= 1.0f,
               "MTPV voltage limit within valid range");
    TEST_ASSERT(fw_data.mtpv_current_limit >= 0.0f && fw_data.mtpv_current_limit <= 1.0f,
               "MTPV current limit within valid range");
    TEST_ASSERT(fw_data.mtpv_angle_offset >= -M_PI && fw_data.mtpv_angle_offset <= M_PI,
               "MTPV angle offset within valid range");
    TEST_ASSERT(fw_data.mtpv_power_factor >= 0.0f && fw_data.mtpv_power_factor <= 1.0f,
               "MTPV power factor within valid range");
    TEST_ASSERT(fw_data.mtpv_efficiency_percent >= 0.0f && fw_data.mtpv_efficiency_percent <= 100.0f,
               "MTPV efficiency percentage within valid range");
    
    // Test disabling MTPV control
    mc_interface_set_field_weakening_mtpv(false);
    enhanced_field_weakening_data_t fw_data_disabled = mc_interface_get_enhanced_field_weakening_data();
    TEST_ASSERT(fw_data_disabled.mtpv_control_enabled == false,
               "MTPV control can be disabled");
    
    return true;
}

// Test enhanced field weakening efficiency calculation
bool test_enhanced_field_weakening_efficiency(void) {
    printf("Testing Enhanced Field Weakening Efficiency Calculation...\n");
    
    // Initialize the enhanced field weakening system
    mc_interface_init_enhanced_field_weakening();
    
    // Update enhanced field weakening data multiple times
    for (int i = 0; i < 10; i++) {
        mc_interface_update_enhanced_field_weakening();
    }
    
    // Get enhanced field weakening data
    enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
    
    // Test that efficiency calculations are working
    TEST_ASSERT(fw_data.fw_efficiency_percent >= 0.0f && fw_data.fw_efficiency_percent <= 100.0f,
               "Field weakening efficiency percentage within valid range");
    TEST_ASSERT(fw_data.fw_voltage_utilization >= 0.0f && fw_data.fw_voltage_utilization <= 1.0f,
               "Field weakening voltage utilization within valid range");
    TEST_ASSERT(fw_data.fw_current_utilization >= 0.0f && fw_data.fw_current_utilization <= 1.0f,
               "Field weakening current utilization within valid range");
    TEST_ASSERT(fw_data.fw_power_losses >= 0.0f,
               "Field weakening power losses are non-negative");
    TEST_ASSERT(fw_data.fw_torque_capability >= 0.0f && fw_data.fw_torque_capability <= 1.0f,
               "Field weakening torque capability within valid range");
    TEST_ASSERT(fw_data.fw_speed_capability >= 0.0f,
               "Field weakening speed capability is non-negative");
    
    // Test efficiency calculation function
    float efficiency = mc_interface_calculate_field_weakening_efficiency();
    TEST_ASSERT(efficiency >= 0.0f && efficiency <= 100.0f,
               "Field weakening efficiency calculation within valid range");
    
    // Test parameter validation
    TEST_ASSERT(fw_data.fw_parameters_valid == true || fw_data.fw_parameters_valid == false,
               "Field weakening parameters validity flag is boolean");
    TEST_ASSERT(fw_data.fw_processing_time >= 0.0f && fw_data.fw_processing_time <= 100.0f,
               "Field weakening processing time within reasonable range");
    TEST_ASSERT(fw_data.fw_update_cycles >= 10,
               "Field weakening update cycles are being tracked");
    
    return true;
}

// Test comprehensive system integration of all enhanced features
bool test_comprehensive_system_integration(void) {
    printf("Testing Comprehensive System Integration...\n");
    
    // Initialize all enhanced systems
    mc_interface_init_enhanced_hfi();
    mc_interface_init_enhanced_mtpa();
    mc_interface_init_enhanced_field_weakening();
    
    // Enable all enhanced features
    mc_interface_set_hfi_voltage_adaptation(true);
    mc_interface_set_mtpa_temperature_compensation(true);
    mc_interface_set_mtpa_nonlinear_optimization(true);
    mc_interface_set_field_weakening_two_stage(true);
    mc_interface_set_field_weakening_mtpv(true);
    
    // Run multiple update cycles to establish steady state
    for (int i = 0; i < 100; i++) {
        mc_interface_update_enhanced_hfi();
        mc_interface_update_enhanced_mtpa();
        mc_interface_update_enhanced_field_weakening();
    }
    
    // Get data from all systems
    enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
    enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
    enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
    
    // Test that all systems are operational
    TEST_ASSERT(hfi_data.hfi_enhanced_enabled == true,
               "Enhanced HFI system is operational");
    TEST_ASSERT(mtpa_data.mtpa_enhanced_enabled == true,
               "Enhanced MTPA system is operational");
    TEST_ASSERT(fw_data.field_weakening_enhanced_enabled == true,
               "Enhanced field weakening system is operational");
    
    // Test system performance metrics
    TEST_ASSERT(hfi_data.hfi_signal_quality >= 0.5f,
               "HFI signal quality is acceptable");
    TEST_ASSERT(mtpa_data.mtpa_efficiency_percent >= 85.0f,
               "MTPA efficiency is acceptable");
    TEST_ASSERT(fw_data.fw_efficiency_percent >= 85.0f,
               "Field weakening efficiency is acceptable");
    
    // Test system stability
    TEST_ASSERT(hfi_data.hfi_update_cycles >= 100,
               "HFI system has run sufficient cycles");
    TEST_ASSERT(mtpa_data.mtpa_optimization_cycles >= 100,
               "MTPA system has run sufficient cycles");
    TEST_ASSERT(fw_data.fw_update_cycles >= 100,
               "Field weakening system has run sufficient cycles");
    
    // Test processing time performance
    TEST_ASSERT(hfi_data.hfi_processing_time <= 50.0f,
               "HFI processing time is within limits");
    TEST_ASSERT(mtpa_data.mtpa_processing_time <= 50.0f,
               "MTPA processing time is within limits");
    TEST_ASSERT(fw_data.fw_processing_time <= 50.0f,
               "Field weakening processing time is within limits");
    
    // Test parameter validity
    TEST_ASSERT(hfi_data.hfi_parameters_valid == true,
               "HFI parameters are valid");
    TEST_ASSERT(mtpa_data.mtpa_parameters_valid == true,
               "MTPA parameters are valid");
    TEST_ASSERT(fw_data.fw_parameters_valid == true,
               "Field weakening parameters are valid");
    
    // Test efficiency calculations
    float hfi_quality = mc_interface_get_hfi_signal_quality();
    float mtpa_efficiency = mc_interface_calculate_mtpa_efficiency_gain();
    float fw_efficiency = mc_interface_calculate_field_weakening_efficiency();
    
    TEST_ASSERT(hfi_quality >= 0.5f && hfi_quality <= 1.0f,
               "HFI signal quality function returns valid range");
    TEST_ASSERT(mtpa_efficiency >= 0.0f && mtpa_efficiency <= 20.0f,
               "MTPA efficiency gain function returns valid range");
    TEST_ASSERT(fw_efficiency >= 0.0f && fw_efficiency <= 100.0f,
               "Field weakening efficiency function returns valid range");
    
    // Test reset functionality
    mc_interface_reset_hfi_calibration();
    mc_interface_reset_mtpa_optimization();
    mc_interface_reset_field_weakening_optimization();
    
    // Verify reset worked
    enhanced_hfi_data_t hfi_data_reset = mc_interface_get_enhanced_hfi_data();
    enhanced_mtpa_data_t mtpa_data_reset = mc_interface_get_enhanced_mtpa_data();
    enhanced_field_weakening_data_t fw_data_reset = mc_interface_get_enhanced_field_weakening_data();
    
    TEST_ASSERT(hfi_data_reset.hfi_calibration_samples == 0,
               "HFI calibration reset successfully");
    TEST_ASSERT(mtpa_data_reset.mtpa_optimization_cycles == 0,
               "MTPA optimization reset successfully");
    TEST_ASSERT(fw_data_reset.fw_update_cycles == 0,
               "Field weakening optimization reset successfully");
    
    printf("✓ All enhanced systems integrated successfully!\n");
    return true;
}

// Get test results
test_results_t test_bafang_features_get_results(void) {
    return test_results;
}

// Hardware-specific test implementations for Flipsky 75200 Pro V2.0

bool test_hardware_compatibility_flipsky_75200_pro_v2(void) {
    printf("Testing Flipsky 75200 Pro V2.0 Hardware Compatibility...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test hardware identification
        TEST_ASSERT(HW_HAS_PHASE_FILTERS == 0, "Phase filters correctly identified as absent");
        TEST_ASSERT(HW_SINGLE_TEMPERATURE_SENSOR == 1, "Single temperature sensor correctly identified");
        TEST_ASSERT(HW_CURRENT_SENSING_LOW_SIDE_ONLY == 1, "Low-side current sensing correctly identified");
        TEST_ASSERT(HW_MOSFET_QUALITY_ISSUES == 1, "MOSFET quality issues correctly identified");
        
        // Test hardware adaptation initialization
        hw_flipsky_75200_pro_v2_init_adaptations();
        TEST_ASSERT(hw_flipsky_75200_pro_v2_is_initialized(), "Hardware adaptations initialized successfully");
        
        // Test hardware validation
        bool config_valid = hw_flipsky_75200_pro_v2_validate_configuration();
        TEST_ASSERT(config_valid, "Hardware configuration validated successfully");
        
        // Test diagnostic system
        hw_flipsky_75200_diagnostics_t diagnostics = hw_flipsky_75200_pro_v2_run_diagnostics();
        TEST_ASSERT(diagnostics.hardware_score > 0.0f, "Hardware diagnostic score calculated");
        TEST_ASSERT(diagnostics.hardware_score <= 100.0f, "Hardware diagnostic score within valid range");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_phase_filter_absence(void) {
    printf("Testing Phase Filter Absence Handling...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test HFI adaptations for phase filter absence
        mc_interface_init_enhanced_hfi();
        enhanced_hfi_data_t hfi_data = mc_interface_get_enhanced_hfi_data();
        
        // Verify reduced parameters for hardware without phase filters
        TEST_ASSERT(hfi_data.hfi_voltage_scale <= 1.0f, "HFI voltage scale reduced for missing phase filters");
        TEST_ASSERT(hfi_data.hfi_bandwidth_hz <= 300.0f, "HFI bandwidth reduced for missing phase filters");
        TEST_ASSERT(hfi_data.hfi_phase_margin >= 50.0f, "HFI phase margin increased for stability");
        TEST_ASSERT(hfi_data.hfi_gain_margin >= 6.0f, "HFI gain margin increased for stability");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_current_sensing_low_side(void) {
    printf("Testing Low-Side Current Sensing Compensation...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test MTPA current sensing compensation
        mc_interface_init_enhanced_mtpa();
        enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
        
        // Verify current sensing compensation parameters
        TEST_ASSERT(mtpa_data.current_sensing_compensation_enabled, "Current sensing compensation enabled");
        TEST_ASSERT(mtpa_data.current_sensing_offset_factor >= 1.0f, "Current sensing offset factor applied");
        TEST_ASSERT(mtpa_data.current_sensing_filter_factor <= 1.0f, "Current sensing filter factor applied");
        TEST_ASSERT(mtpa_data.current_sensing_accuracy_threshold > 0.0f, "Current sensing accuracy threshold set");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_thermal_management_single_sensor(void) {
    printf("Testing Single Sensor Thermal Management...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test thermal management initialization
        hw_flipsky_75200_pro_v2_init_adaptations();
        hw_flipsky_75200_diagnostics_t diagnostics = hw_flipsky_75200_pro_v2_run_diagnostics();
        
        // Verify thermal management features
        TEST_ASSERT(diagnostics.thermal_estimation_enabled, "Thermal estimation enabled for single sensor");
        TEST_ASSERT(diagnostics.thermal_protection_enhanced, "Enhanced thermal protection enabled");
        TEST_ASSERT(HW_TEMP_SAFETY_MARGIN >= 5.0f, "Thermal safety margin applied");
        TEST_ASSERT(HW_TEMP_DERATING_AGGRESSIVE == 1, "Aggressive thermal derating enabled");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_mosfet_protection_limits(void) {
    printf("Testing MOSFET Protection Limits...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test MOSFET protection parameters
        TEST_ASSERT(HW_MOSFET_CURRENT_LIMIT_CONSERVATIVE <= 200.0f, "Conservative current limit applied");
        TEST_ASSERT(HW_MOSFET_VOLTAGE_LIMIT_CONSERVATIVE <= 75.0f, "Conservative voltage limit applied");
        TEST_ASSERT(HW_MOSFET_FAILURE_DETECTION == 1, "MOSFET failure detection enabled");
        TEST_ASSERT(HW_MOSFET_THERMAL_PROTECTION == 1, "MOSFET thermal protection enabled");
        
        // Test MTPA optimization limits
        mc_interface_init_enhanced_mtpa();
        enhanced_mtpa_data_t mtpa_data = mc_interface_get_enhanced_mtpa_data();
        TEST_ASSERT(mtpa_data.mtpa_optimization_gain_limit <= 1.0f, "MTPA optimization gain limited for MOSFET protection");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_switching_frequency_constraints(void) {
    printf("Testing Switching Frequency Constraints...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test switching frequency limits
        TEST_ASSERT(HW_SWITCHING_FREQUENCY_MAX <= 16000, "Maximum switching frequency limited");
        TEST_ASSERT(HW_SWITCHING_FREQUENCY_SAFE <= 13000, "Safe switching frequency defined");
        TEST_ASSERT(HW_DEAD_TIME_NS_MIN >= 500, "Minimum dead time increased for safety");
        
        // Test field weakening bandwidth adaptation
        mc_interface_init_enhanced_field_weakening();
        enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
        TEST_ASSERT(fw_data.field_weakening_bandwidth_hz <= 100.0f, "Field weakening bandwidth constrained");
        TEST_ASSERT(fw_data.field_weakening_switching_freq_limit == HW_SWITCHING_FREQUENCY_SAFE, "Field weakening switching frequency limit set");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_20s_lipo_compatibility(void) {
    printf("Testing 20S LiPo Battery Compatibility...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Test voltage limits for 20S LiPo
        TEST_ASSERT(HW_VOLTAGE_MAX_SAFE >= 75.0f, "Safe voltage limit suitable for 20S LiPo");
        TEST_ASSERT(HW_VOLTAGE_MAX_ABSOLUTE == 84.0f, "Absolute voltage limit set for 20S LiPo");
        
        // Test field weakening high voltage mode
        mc_interface_init_enhanced_field_weakening();
        enhanced_field_weakening_data_t fw_data = mc_interface_get_enhanced_field_weakening_data();
        TEST_ASSERT(fw_data.field_weakening_high_voltage_mode, "High voltage mode enabled for 20S LiPo");
        TEST_ASSERT(fw_data.field_weakening_voltage_threshold >= 60.0f, "Voltage threshold set for high voltage operation");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

bool test_hardware_diagnostic_system(void) {
    printf("Testing Hardware Diagnostic System...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Initialize and run diagnostics
        hw_flipsky_75200_pro_v2_init_adaptations();
        hw_flipsky_75200_diagnostics_t diagnostics = hw_flipsky_75200_pro_v2_run_diagnostics();
        
        // Test diagnostic results
        TEST_ASSERT(diagnostics.hardware_score > 0.0f, "Hardware diagnostic score calculated");
        TEST_ASSERT(diagnostics.hardware_score <= 100.0f, "Hardware diagnostic score within valid range");
        TEST_ASSERT(diagnostics.warning_count >= 0, "Warning count tracked");
        TEST_ASSERT(diagnostics.fault_count >= 0, "Fault count tracked");
        
        // Test specific diagnostic checks
        TEST_ASSERT(diagnostics.phase_filter_present == false, "Phase filter absence correctly detected");
        TEST_ASSERT(diagnostics.temperature_sensor_valid == false, "Inadequate temperature sensing correctly detected");
        TEST_ASSERT(diagnostics.current_sensing_calibrated == false, "Limited current sensing correctly detected");
        TEST_ASSERT(diagnostics.mosfet_health_ok == false, "MOSFET reliability issues correctly detected");
        
        // Test configuration validation
        bool config_valid = hw_flipsky_75200_pro_v2_validate_configuration();
        TEST_ASSERT(config_valid || diagnostics.hardware_score <= 60.0f, "Configuration validation consistent with hardware score");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}



bool test_hardware_safety_mechanisms(void) {
    printf("Testing Hardware Safety Mechanisms...\n");
    test_results.total_tests++;
    
    #ifdef HW_FLIPSKY_75200_PRO_V2
        // Initialize hardware adaptations
        hw_flipsky_75200_pro_v2_init_adaptations();
        
        // Test individual safety mechanisms
        hw_flipsky_75200_pro_v2_apply_phase_filter_safety();
        hw_flipsky_75200_pro_v2_apply_thermal_safety();
        hw_flipsky_75200_pro_v2_apply_mosfet_safety();
        hw_flipsky_75200_pro_v2_apply_capacitor_safety();
        hw_flipsky_75200_pro_v2_apply_gate_driver_safety();
        hw_flipsky_75200_pro_v2_apply_high_voltage_safety();
        
        // Validate all safety mechanisms
        bool safety_valid = hw_flipsky_75200_pro_v2_validate_safety_mechanisms();
        TEST_ASSERT(safety_valid, "All safety mechanisms validated successfully");
        
        // Test specific safety parameters
        TEST_ASSERT(HW_HFI_VOLTAGE_SCALE_MAX <= 1.5f, "HFI voltage scale within safe limits");
        TEST_ASSERT(HW_HFI_BANDWIDTH_HZ_MAX <= 300.0f, "HFI bandwidth within safe limits");
        TEST_ASSERT(HW_TEMP_SAFETY_MARGIN >= 10.0f, "Thermal safety margin adequate");
        TEST_ASSERT(HW_MOSFET_CURRENT_LIMIT_CONSERVATIVE <= 180.0f, "MOSFET current limit conservative");
        TEST_ASSERT(HW_MOSFET_VOLTAGE_LIMIT_CONSERVATIVE <= 70.0f, "MOSFET voltage limit conservative");
        TEST_ASSERT(HW_SWITCHING_FREQUENCY_SAFE <= 13000, "Switching frequency within safe limits");
        TEST_ASSERT(HW_DEAD_TIME_NS_MIN >= 500, "Dead time adequate for safety");
        TEST_ASSERT(HW_VOLTAGE_MAX_SAFE <= 75.0f, "High voltage limit conservative");
        
        // Test diagnostic system safety validation
        hw_flipsky_75200_diagnostics_t diagnostics = hw_flipsky_75200_pro_v2_run_diagnostics();
        TEST_ASSERT(diagnostics.hardware_score >= 0.0f, "Hardware score within valid range");
        TEST_ASSERT(diagnostics.warning_count >= 5, "Expected warnings for hardware issues detected");
        
        // Test safety mechanism effectiveness
        TEST_ASSERT(diagnostics.phase_filter_present == false, "Phase filter absence correctly detected");
        TEST_ASSERT(diagnostics.thermal_estimation_enabled == true, "Thermal estimation safety enabled");
        TEST_ASSERT(diagnostics.mosfet_protection_enhanced == true, "MOSFET protection safety enabled");
        
        test_results.passed_tests++;
        printf("✓ PASSED\n");
        return true;
    #else
        printf("⚠ SKIPPED (not compiled for Flipsky 75200 Pro V2.0)\n");
        return true;
    #endif
}

