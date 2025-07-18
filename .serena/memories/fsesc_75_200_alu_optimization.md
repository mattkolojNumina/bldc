# FSESC_75_200_ALU Controller Optimization for Bafang Hub Motor

## Controller Specifications
- **Model**: Flipsky FSESC 75_200 ALU VESC controller
- **Voltage Range**: 14–84V (4S–20S Li-ion, safe operation to 75V)
- **Continuous Current**: 200A at 50V, 150A at 75V
- **Peak Current**: 300A burst capability
- **Maximum Power**: Up to 15kW theoretical (75V × 200A)
- **Thermal Management**: Aluminum PCB for improved heat dissipation

## Hardware Configuration Changes

### Base Platform Integration
- **File**: `hwconf/hw_bafang_500w_hub.h`
- **Change**: Now inherits from `flipsky/hw_fsesc_75_200_alu.h` instead of generic config
- **Benefit**: Proper pin mappings, ADC configuration, and hardware limits

### Current Limit Optimization
```c
// Previous (generic):           // Updated (FSESC-specific):
HW_LIM_CURRENT: -300, 300       HW_LIM_CURRENT: -100, 100
HW_LIM_CURRENT_IN: -280, 280    HW_LIM_CURRENT_IN: -70, 70  
HW_LIM_CURRENT_ABS: 0, 450      HW_LIM_CURRENT_ABS: 0, 150
```

### Motor Configuration Alignment
```c
// Motor current limits (conservative for hub motor thermal safety):
MCCONF_L_CURRENT_MAX: 100A      // Phase current
MCCONF_L_CURRENT_MIN: -60A      // Brake current  
MCCONF_L_IN_CURRENT_MAX: 70A    // Battery current (1000W @ 48V ≈ 21A base)
MCCONF_L_IN_CURRENT_MIN: -40A   // Regen current
MCCONF_L_MAX_ABS_CURRENT: 120A  // Absolute limit (within FSESC safe range)
```

### Power Limits
```c
MCCONF_L_WATT_MAX: 3000W        // Increased from 1000W (FSESC headroom)
MCCONF_L_WATT_MIN: -1500W       // Conservative regen limit
```

### Switching Frequency Optimization
```c
MCCONF_FOC_F_ZV: 20000Hz        // Research-optimized frequency
HW_DEAD_TIME_NSEC: 400ns        // Optimized for hub motor efficiency
```

## Safety Considerations

### Thermal Management
- **Controller**: FSESC aluminum PCB provides good heat dissipation
- **Motor**: Bafang hub motors have limited cooling, thermal protection at 100°C
- **Conservative Limits**: 70A battery current vs 200A controller capability
- **Recommendation**: Monitor temperatures during initial testing

### Current Scaling
- **Phase Current**: 100A (50% of FSESC peak capability)
- **Battery Current**: 70A (35% of FSESC continuous rating)
- **Safety Margin**: 2-3x headroom for burst operation and thermal protection

### Power Distribution
- **Nominal**: 48V × 70A = 3360W available
- **Bafang Rated**: 500W continuous, 1000W peak (motor thermal limited)
- **Controller Headroom**: 15kW capable vs 3kW configured

## Performance Expectations

### Improved Capabilities
- **Higher Current**: 70A vs previous 35A battery limit
- **Better Cooling**: Aluminum PCB vs standard FR4
- **Optimized Control**: 20kHz switching for efficiency
- **Proper Hardware**: Correct ADC channels and pin mappings

### Thermal Characteristics
- **FSESC**: Rated for 200A continuous with adequate cooling
- **Bafang Hub**: Limited by motor thermal mass, not controller
- **System Bottleneck**: Motor thermal limits, not controller limits

## Validation Requirements
1. **Motor Detection**: Verify L/R parameters with FSESC hardware
2. **Current Monitoring**: Validate current sensing accuracy
3. **Thermal Testing**: Monitor controller and motor temperatures
4. **Power Testing**: Gradual increase to validate 70A operation
5. **Efficiency Measurement**: Confirm 20kHz optimization benefits