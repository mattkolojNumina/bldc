# FSESC_75_200_ALU Deployment Guide for Bafang Hub Motor

## Firmware Files Available
- **Binary**: `build/fsesc_75_200_alu/fsesc_75_200_alu.bin` (524 KB) - For VESC_TOOL
- **Intel Hex**: `build/fsesc_75_200_alu/fsesc_75_200_alu.hex` (1.3 MB) - For programmers
- **ELF**: `build/fsesc_75_200_alu/fsesc_75_200_alu.elf` (4.6 MB) - For debugging

## Flashing Procedure

### Method 1: VESC_TOOL (Recommended)
1. **Connect**: USB cable to FSESC_75_200_ALU
2. **Open VESC_TOOL**: Latest version with FSESC support
3. **Flash Custom Firmware**:
   - Firmware → Flash Custom Firmware
   - Select `fsesc_75_200_alu.bin`
   - Flash and wait for completion
4. **Verify**: Check firmware version shows custom build

### Method 2: ST-Link/SWD (Advanced)
1. **Connect SWD**: ST-Link to FSESC debug pins
2. **OpenOCD**: `make fw_fsesc_75_200_alu_flash`
3. **Verify**: Power cycle and check operation

## Initial Configuration Steps

### 1. Motor Detection (Critical)
```
Motor → Motor Detection → FOC
Expected Results:
- Resistance: ~139 mΩ (±20%)
- Inductance: ~275 μH (±20%) 
- Poles: 20 (exact)
- Flux Linkage: ~0.017 (calculated)
```

### 2. Current Limit Validation
```
Motor → Current Limits:
- Motor Current Max: 100A (start with 50A)
- Battery Current Max: 70A (start with 35A)
- Absolute Current: 120A
```

### 3. FOC Configuration Verification
```
Motor → FOC → Controller:
- Current KP: Should be ~0.04
- Current KI: Should be ~0.4
- Switching Frequency: 20000 Hz
- Observer Gain: 0.50
```

### 4. Low-Speed Optimization Check
```
Motor → FOC → Sensorless:
- Sensorless ERPM: 250
- Openloop ERPM: 50
- Hall sensor hybrid: 2000 ERPM
```

## Testing Protocol

### Phase 1: Basic Operation (30 min)
1. **No-Load Test**: Motor spins freely, no vibration
2. **Hall Sensor Test**: Verify 120° spacing in VESC_TOOL
3. **Current Monitoring**: Check current sensing accuracy
4. **Temperature Monitoring**: Baseline temps at idle

### Phase 2: Low-Current Testing (1 hour)
1. **Start Conservative**: 50A motor, 35A battery limits
2. **Low-Speed Test**: 5-15 km/h operation smoothness
3. **Phase Shorting Test**: Apply brake at <10 km/h, verify engagement
4. **Temperature Check**: Monitor controller and motor temps

### Phase 3: Progressive Load Testing (2 hours)
1. **Increment Limits**: Increase by 25% every 30 minutes
2. **Thermal Monitoring**: Stop if temps exceed 80°C
3. **Performance Validation**: Efficiency and smoothness
4. **Full Current Test**: Final validation at 100A/70A

## Safety Protocols

### Temperature Limits
- **Controller**: Stop if >85°C, reduce current if >75°C
- **Motor**: Stop if >100°C, reduce current if >90°C
- **Battery**: Monitor cell temperatures during high current

### Current Monitoring
- **Phase Current**: Should not exceed 100A sustained
- **Battery Current**: Should not exceed 70A sustained  
- **Power**: Monitor instantaneous power <3kW

### Emergency Procedures
- **Thermal Runaway**: Immediate shutdown, cooling period
- **Overcurrent**: Reduce limits, check connections
- **Motor Vibration**: Stop immediately, check motor detection
- **Phase Shorting Issues**: Disable feature, use current braking

## Performance Validation

### Efficiency Testing
- **Baseline**: Measure efficiency at 10, 20, 30 km/h
- **Compare**: Against previous firmware if available
- **Target**: >80% efficiency at cruising speeds

### Low-Speed Performance
- **Stuttering**: Should be eliminated below 10 km/h
- **Startup**: Smooth acceleration from standstill
- **Torque**: Consistent torque delivery at low speeds

### Brake Testing
- **Phase Shorting**: Effective below 2000 ERPM
- **Current Braking**: Smooth transition above 2000 ERPM
- **Thermal**: Reduced brake heating with phase shorting

## Troubleshooting

### Motor Detection Fails
- Check hall sensor connections and sequence
- Verify motor parameters match Bafang specifications
- Try sensorless detection if hall sensors faulty

### High Temperature Issues
- Reduce current limits by 25%
- Improve controller cooling/airflow
- Check for motor overheating (hub motor thermal limits)

### Low-Speed Stuttering Persists
- Verify observer gain is 0.50
- Check sensorless ERPM threshold (250)
- Validate current controller gains (Kp=0.04, Ki=0.4)

### Phase Shorting Not Working
- Confirm RPM <2000 when engaging
- Check FOC mode is active (not BLDC)
- Verify brake current >0 when calling function

## Success Metrics
- [ ] Motor detection matches research parameters
- [ ] Smooth operation 0-40 km/h
- [ ] Phase shorting brake functional <10 km/h
- [ ] Temperatures stable under load
- [ ] Efficiency improved vs baseline
- [ ] No fault codes during operation