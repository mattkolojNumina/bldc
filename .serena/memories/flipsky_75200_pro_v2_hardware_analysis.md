# Flipsky 75200 Pro V2.0 Hardware Analysis

## Critical Hardware Information
- **Model**: Flipsky 75200 Pro V2.0 with Aluminum PCB (FSESC_75_200_ALU)
- **CPU**: STM32 F405 @ 168MHz (same as official VESC)
- **Voltage**: 14-84V (4-20S battery)
- **Current**: 200A@50V, 150A@75V continuous, 300A burst
- **MOSFETs**: TOLL package, Low side 15N10 from Hawaii
- **Gate Drivers**: EG3112 from EG Micro
- **Capacitors**: 6x 470µF 100V from Rich Caps

## Critical Deviations from VESC Spec
1. **Phase Filter**: Many units DON'T have physical phase filters despite claims
2. **Current Sensing**: Low-side shunt implementation only
3. **Temperature Sensor**: Single sensor on corner (inadequate coverage)
4. **Quality Control**: Poor solder joints, loose components, thermal paste issues

## Known Issues & Failures
- **MOSFET Failures**: Common shorts, witness marks from case contact
- **Capacitor Problems**: Come loose, cause controller death
- **Firmware Issues**: 5.3+ versions can damage ESC if phase filter enabled
- **Thermal Management**: Inconsistent thermal paste application
- **Hall Sensor**: Loose connectors cause stuttering

## Critical Safety Considerations
- **Phase Filter Setting**: MUST be disabled in VESC Tool 5.3+ to prevent damage
- **Gate Resistors**: May need 16-22Ω for voltages >30-45V
- **Switching Frequency**: May need reduction to 13-16kHz for stability
- **Dead Time**: Requires careful tuning for gate driver compatibility

## Hardware Limitations for Advanced Control
- Single temperature sensor limits thermal monitoring
- Low-side current sensing only during MOSFET conduction
- Quality control issues may affect high-frequency switching
- Phase filter absence affects noise filtering