// Motor configuration for Bafang 1000W Hub Motor (doubled from 500W base)
// Based on Luna M600 but optimized for hub motor operation

#ifndef MCCONF_BAFANG_500W_HUB_H_
#define MCCONF_BAFANG_500W_HUB_H_

// PWM Mode
#define MCCONF_PWM_MODE 1

// Commutation Mode  
#define MCCONF_COMM_MODE 0

// Motor Type - FOC for best performance
#define MCCONF_DEFAULT_MOTOR_TYPE 2

// Sensor Mode - Hall sensors
#define MCCONF_SENSOR_MODE 0

// Motor Current Max - Optimized for FSESC_75_200_ALU with Bafang hub motor
#define MCCONF_L_CURRENT_MAX 100

// Motor Current Max Brake - Conservative for hub motor
#define MCCONF_L_CURRENT_MIN -60

// Battery Current Max - Aligned with FSESC_75_200_ALU and 1000W @ 48V 
#define MCCONF_L_IN_CURRENT_MAX 70

// Battery Current Max Regen - Conservative for battery safety
#define MCCONF_L_IN_CURRENT_MIN -40

// Absolute Maximum Current - Conservative for FSESC_75_200_ALU
#define MCCONF_L_MAX_ABS_CURRENT 120

// Max ERPM Reverse - Hub motors can handle higher speeds
#define MCCONF_L_RPM_MIN -80000

// Max ERPM - Hub motors can handle higher speeds  
#define MCCONF_L_RPM_MAX 80000

// ERPM Limit Start
#define MCCONF_L_RPM_START 0.8

// Max ERPM Full Brake
#define MCCONF_L_CURR_MAX_RPM_FBRAKE 500

// Max ERPM Full Brake Current Control
#define MCCONF_L_CURR_MAX_RPM_FBRAKE_CC 2000

// Minimum Input Voltage - 36V battery systems
#define MCCONF_L_MIN_VOLTAGE 30

// Maximum Input Voltage - 72V battery systems
#define MCCONF_L_MAX_VOLTAGE 85

// Battery Voltage Cutoff Start - 48V system (adjust for your battery)
#define MCCONF_L_BATTERY_CUT_START 42

// Battery Voltage Cutoff End
#define MCCONF_L_BATTERY_CUT_END 40

// Slow ABS Current Limit
#define MCCONF_L_SLOW_ABS_OVERCURRENT 0

// MOSFET Temp Cutoff Start
#define MCCONF_L_LIM_TEMP_FET_START 80

// MOSFET Temp Cutoff End
#define MCCONF_L_LIM_TEMP_FET_END 90

// Motor Temp Cutoff Start
#define MCCONF_L_LIM_TEMP_MOTOR_START 80

// Motor Temp Cutoff End - Hub motors can run hotter
#define MCCONF_L_LIM_TEMP_MOTOR_END 100

// Acceleration Temperature Decrease
#define MCCONF_L_LIM_TEMP_ACCEL_DEC 0

// Enhanced thermal management for hub motors
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_START 60     // Start derating at 60°C
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_END 85       // Significant derating at 85°C
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_AGGRESSIVE_START 90  // Aggressive derating at 90°C
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_AGGRESSIVE_END 105   // Emergency derating at 105°C
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_POWER_SCALE 0.7      // Power scaling factor
#define MCCONF_L_LIM_TEMP_MOTOR_HUB_ADAPTIVE_ENABLE 1    // Enable adaptive management

// Minimum Duty Cycle
#define MCCONF_L_MIN_DUTY 0.005

// Maximum Duty Cycle
#define MCCONF_L_MAX_DUTY 0.95

// Maximum Wattage - Conservative for FSESC_75_200_ALU thermal limits
#define MCCONF_L_WATT_MAX 3000

// Maximum Braking Wattage - Conservative for thermal management
#define MCCONF_L_WATT_MIN -1500

// Max Current Scale
#define MCCONF_L_CURRENT_MAX_SCALE 1

// Min Current Scale
#define MCCONF_L_CURRENT_MIN_SCALE 1

// Duty Cycle Current Limit Start
#define MCCONF_L_DUTY_START 1

// Minimum ERPM
#define MCCONF_SL_MIN_RPM 150

// Minimum ERPM Integrator
#define MCCONF_SL_MIN_ERPM_CYCLE_INT_LIMIT 1100

// Max Brake Current at Direction Change
#define MCCONF_SL_MAX_FB_CURR_DIR_CHANGE 15

// Cycle Integrator Limit
#define MCCONF_SL_CYCLE_INT_LIMIT 62

// Phase Advance at BR ERPM
#define MCCONF_SL_PHASE_ADVANCE_AT_BR 0.8

// BR ERPM
#define MCCONF_SL_CYCLE_INT_BR 80000

// BEMF Coupling
#define MCCONF_SL_BEMF_COUPLING_K 600

// Hall Table - Standard Bafang sequence
#define MCCONF_HALL_TAB_0 -1
#define MCCONF_HALL_TAB_1 1
#define MCCONF_HALL_TAB_2 3
#define MCCONF_HALL_TAB_3 2
#define MCCONF_HALL_TAB_4 5
#define MCCONF_HALL_TAB_5 6
#define MCCONF_HALL_TAB_6 4
#define MCCONF_HALL_TAB_7 -1

// Sensorless ERPM Hybrid
#define MCCONF_HALL_ERPM 2000

// FOC Current Controllers - Optimized for hub motor stability (research-based)
#define MCCONF_FOC_CURRENT_KP 0.04
#define MCCONF_FOC_CURRENT_KI 0.4

// Zero Vector Frequency - Optimal 20kHz for hub motor efficiency
#define MCCONF_FOC_F_ZV 20000

// Dead Time Compensation - Hub motors typically need less
#define MCCONF_FOC_DT_US 0.20

// Encoder Settings
#define MCCONF_FOC_ENCODER_INVERTED 0
#define MCCONF_FOC_ENCODER_OFFSET 0.0
#define MCCONF_FOC_ENCODER_RATIO 1

// Sensor Mode - Hall sensors
#define MCCONF_FOC_SENSOR_MODE 1

// Speed Tracker - More aggressive for hub motor
#define MCCONF_FOC_PLL_KP 2500
#define MCCONF_FOC_PLL_KI 40000

// Motor Parameters - Research-based Bafang 500W specifications
#define MCCONF_FOC_MOTOR_L 0.000275        // Motor inductance (275 μH from research)
#define MCCONF_FOC_MOTOR_LD_LQ_DIFF 0      // No saliency assumed
#define MCCONF_FOC_MOTOR_R 0.139           // Motor resistance (139 mΩ from research)
#define MCCONF_FOC_MOTOR_FLUX_LINKAGE 0.017 // Flux linkage (calculated for 20 poles)

// Observer Gain - Reduced for hub motor stability (research-based)
#define MCCONF_FOC_OBSERVER_GAIN 6.0e+06
#define MCCONF_FOC_OBSERVER_GAIN_SLOW 0.50
#define MCCONF_FOC_OBSERVER_OFFSET -1

// Duty Downramp
#define MCCONF_FOC_DUTY_DOWNRAMP_KP 10
#define MCCONF_FOC_DUTY_DOWNRAMP_KI 200

// Start Current Decrease
#define MCCONF_FOC_START_CURR_DEC 1
#define MCCONF_FOC_START_CURR_DEC_RPM 2500

// Openloop Settings - Optimized for low-speed efficiency
#define MCCONF_FOC_OPENLOOP_RPM 50
#define MCCONF_FOC_OPENLOOP_RPM_LOW 0
#define MCCONF_FOC_D_GAIN_SCALE_START 1
#define MCCONF_FOC_D_GAIN_SCALE_MAX_MOD 0.2

// Openloop Parameters
#define MCCONF_FOC_SL_OPENLOOP_HYST 0.1
#define MCCONF_FOC_SL_OPENLOOP_T_LOCK 0
#define MCCONF_FOC_SL_OPENLOOP_T_RAMP 0.1
#define MCCONF_FOC_SL_OPENLOOP_TIME 0.05
#define MCCONF_FOC_SL_OPENLOOP_BOOST_Q 0
#define MCCONF_FOC_SL_OPENLOOP_MAX_Q -1

// FOC Hall Table
#define MCCONF_FOC_HALL_TAB_0 255
#define MCCONF_FOC_HALL_TAB_1 255
#define MCCONF_FOC_HALL_TAB_2 255
#define MCCONF_FOC_HALL_TAB_3 255
#define MCCONF_FOC_HALL_TAB_4 255
#define MCCONF_FOC_HALL_TAB_5 255
#define MCCONF_FOC_HALL_TAB_6 255
#define MCCONF_FOC_HALL_TAB_7 255

// Hall Interpolation ERPM
#define MCCONF_FOC_HALL_INTERP_ERPM 500

// Sensorless ERPM - Reduced for better low-speed operation
#define MCCONF_FOC_SL_ERPM 250

// Sample in V0 and V7
#define MCCONF_FOC_SAMPLE_V0_V7 0

// High Current Sampling Mode
#define MCCONF_FOC_SAMPLE_HIGH_CURRENT 0

// Saturation Compensation
#define MCCONF_FOC_SAT_COMP_MODE 0
#define MCCONF_FOC_SAT_COMP 0

// Temperature Compensation
#define MCCONF_FOC_TEMP_COMP 0
#define MCCONF_FOC_TEMP_COMP_BASE_TEMP 25

// Current Filter
#define MCCONF_FOC_CURRENT_FILTER_CONST 0.1

// Current Controller Decoupling
#define MCCONF_FOC_CC_DECOUPLING 0

// Observer Type
#define MCCONF_FOC_OBSERVER_TYPE 0

// HFI Settings (not typically used with hall sensors)
#define MCCONF_FOC_HFI_VOLTAGE_START 20
#define MCCONF_FOC_HFI_VOLTAGE_RUN 4
#define MCCONF_FOC_HFI_VOLTAGE_MAX 10
#define MCCONF_FOC_HFI_GAIN 0.3
#define MCCONF_FOC_HFI_HYST 0
#define MCCONF_FOC_SL_ERPM_HFI 2000
#define MCCONF_FOC_HFI_START_SAMPLES 65
#define MCCONF_FOC_HFI_OBS_OVR_SEC 0.001
#define MCCONF_FOC_HFI_SAMPLES 1

// Offset Calibration
#define MCCONF_FOC_OFFSETS_CAL_ON_BOOT 1
#define MCCONF_FOC_OFFSETS_CURRENT_0 2048.0
#define MCCONF_FOC_OFFSETS_CURRENT_1 2048.0
#define MCCONF_FOC_OFFSETS_CURRENT_2 2048.0
#define MCCONF_FOC_OFFSETS_VOLTAGE_0 0.0
#define MCCONF_FOC_OFFSETS_VOLTAGE_1 0.0
#define MCCONF_FOC_OFFSETS_VOLTAGE_2 0.0
#define MCCONF_FOC_OFFSETS_VOLTAGE_UNDRIVEN_0 0
#define MCCONF_FOC_OFFSETS_VOLTAGE_UNDRIVEN_1 0
#define MCCONF_FOC_OFFSETS_VOLTAGE_UNDRIVEN_2 0

// Phase Filters
#define MCCONF_FOC_PHASE_FILTER_ENABLE 1
#define MCCONF_FOC_PHASE_FILTER_DISABLE_FAULT 1
#define MCCONF_FOC_PHASE_FILTER_MAX_ERPM 3000

// MTPA Algorithm
#define MCCONF_FOC_MTPA_MODE 0

// Field Weakening - Research-optimized for hub motors
#define MCCONF_FOC_FW_CURRENT_MAX 30
#define MCCONF_FOC_FW_DUTY_START 0.60
#define MCCONF_FOC_FW_RAMP_TIME 0.3
#define MCCONF_FOC_FW_Q_CURRENT_FACTOR 0.02

// Speed Source
#define MCCONF_FOC_SPEED_SOURCE 0

// PID Controllers
#define MCCONF_S_PID_KP 0.004
#define MCCONF_S_PID_KI 0.004
#define MCCONF_S_PID_KD 0.0001
#define MCCONF_S_PID_KD_FILTER 0.2
#define MCCONF_S_PID_MIN_RPM 150
#define MCCONF_S_PID_ALLOW_BRAKING 1
#define MCCONF_S_PID_RAMP_ERPMS_S 2000

// Position PID
#define MCCONF_P_PID_KP 0.03
#define MCCONF_P_PID_KI 0
#define MCCONF_P_PID_KD 0.0004
#define MCCONF_P_PID_KD_PROC 0.00035
#define MCCONF_P_PID_KD_FILTER 0.2
#define MCCONF_P_PID_ANG_DIV 1
#define MCCONF_P_PID_GAIN_DEC_ANGLE 0
#define MCCONF_P_PID_OFFSET 0

// Startup boost
#define MCCONF_CC_STARTUP_BOOST_DUTY 0.01
#define MCCONF_CC_MIN_CURRENT 0.05
#define MCCONF_CC_GAIN 0.0046
#define MCCONF_CC_RAMP_STEP 0.04

// Fault and Timing
#define MCCONF_M_FAULT_STOP_TIME 500
#define MCCONF_M_RAMP_STEP 0.02
#define MCCONF_M_CURRENT_BACKOFF_GAIN 0.5

// Motor Properties - Bafang Hub Motor (research-verified)
#define MCCONF_SI_MOTOR_POLES 20             // 20 magnetic poles (10 pole pairs) from research
#define MCCONF_SI_GEAR_RATIO 1.0             // Direct drive hub motor
#define MCCONF_SI_WHEEL_DIAMETER 0.700       // 700mm (28") typical e-bike wheel
#define MCCONF_SI_BATTERY_TYPE 0             // Li-ion
#define MCCONF_SI_BATTERY_CELLS 13           // 48V battery (13S)
#define MCCONF_SI_BATTERY_AH 15.0            // 15Ah typical capacity
#define MCCONF_SI_MOTOR_NL_CURRENT 1.4       // No-load current (research spec)

// Other settings
#define MCCONF_M_INVERT_DIRECTION 0
#define MCCONF_M_SENSOR_PORT_MODE 7
#define MCCONF_M_MOTOR_TEMP_SENS_TYPE 1
#define MCCONF_M_BATT_FILTER_CONST 70

// Adaptive Parameter System Configuration
#define MCCONF_FOC_ADAPTIVE_ENABLE 1                     // Enable adaptive parameters
#define MCCONF_FOC_ADAPTIVE_KP_TEMP_COEFF 0.8            // Kp temperature coefficient (0.8% per °C)
#define MCCONF_FOC_ADAPTIVE_KI_TEMP_COEFF 0.6            // Ki temperature coefficient (0.6% per °C)
#define MCCONF_FOC_ADAPTIVE_RESISTANCE_TEMP_COEFF 0.393  // Resistance temperature coefficient (0.393% per °C for copper)
#define MCCONF_FOC_ADAPTIVE_FLUX_TEMP_COEFF 0.1          // Flux linkage temperature coefficient (0.1% per °C)
#define MCCONF_FOC_ADAPTIVE_TEMP_REFERENCE 25.0          // Reference temperature (25°C)
#define MCCONF_FOC_ADAPTIVE_PARAM_LPF_TAU 2.0            // Low-pass filter time constant (2 seconds)

// Enhanced Telemetry System Configuration
#define MCCONF_TELEMETRY_ENABLE 1                        // Enable telemetry
#define MCCONF_TELEMETRY_RATE_HZ 10                      // Telemetry update rate (10 Hz)
#define MCCONF_TELEMETRY_CAN_ID 0x101                    // CAN ID for telemetry

// Field Optimization System Configuration
#define MCCONF_FIELD_OPTIMIZATION_ENABLE 1               // Enable field optimization
#define MCCONF_FIELD_OPTIMIZATION_SAMPLES 50             // Number of samples for optimization
#define MCCONF_FIELD_OPTIMIZATION_LEARNING_RATE 0.01     // Learning rate for optimization
#define MCCONF_FIELD_OPTIMIZATION_UPDATE_RATE_HZ 1       // Optimization update rate (1 Hz)

#endif /* MCCONF_BAFANG_500W_HUB_H_ */