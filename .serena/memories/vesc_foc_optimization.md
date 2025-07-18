# VESC FOC Optimization for Low-Speed Hub Motor Efficiency

## Key Optimization Strategies

### Current Controller Tuning
- **Control Mode**: Current control preferred over duty-cycle/PID for hub motors
- **PI Gains**: Kp <0.05, Ki <0.5 for hub motors to prevent back-EMF destabilization
- **Low-Speed Settings**: Open-loop ERPM=50, Sensorless ERPM=250 reduces stuttering
- **ABS Current**: Use "slow ABS" current limiting for smooth torque transitions

### Switching Frequency Optimization
- **Optimal Range**: 20-30 kHz balances precision and switching losses
- **Efficiency Peak**: 20 kHz achieves 88% system efficiency at 50% load
- **Dual Sampling**: VESC6 dual ADC sampling at 20 kHz equals 40 kHz single-shunt precision
- **High-Inductance Motors**: >10µH work best at 20 kHz
- **Ultra-Low Inductance**: <10µH may need up to 500 kHz (requires GaN FETs)

### Observer Parameters
- **Hub Motor Gains**: Reduce observer gain to 0.50 (vs default 3.14) for stability
- **Stability Threshold**: Gains >2.0 trigger ABS overcurrent faults
- **mxlemming Observer**: VESC FW6 eliminates gain dependency, stable to 5 ERPM
- **Adaptive Scaling**: Gain should scale with ERPM for varying loads

### Field Weakening Configuration
- **Current Limits**: FW Max Current ≤30A to prevent battery overvoltage
- **Duty Start**: Begin FW at 50-65% duty cycle
- **Efficiency Impact**: 7-12% loss at partial load, but net gain under overloads
- **Safety**: Tiltback at 85% duty, thermal derating above 100°C

### Thermal Management
- **Ferrofluid Cooling**: Doubles thermal conductivity, reduces temps by 34°C
- **Temperature Derating**: Linear current reduction from 80°C to 50% at 100°C
- **Active Monitoring**: Real-time thermal feedback via NTC sensors
- **Predictive Algorithms**: Thermal models enable preemptive power reduction

## Practical Implementation Guidelines

### Starting Configuration for Hub Motors
- Current control mode
- Open-loop ERPM: 50
- Sensorless ERPM: 250
- Observer gain: 0.50
- Switching frequency: 20 kHz
- FW max current: 30A
- FW duty start: 60%

### Common Issues and Solutions
- **Low-Speed Stuttering**: Lower open-loop ERPM, reduce observer gain
- **Desynchronization**: Increase sensorless ERPM threshold
- **Overheating**: Apply ferrofluid, enable thermal derating
- **Oscillations**: Reduce PI gains, use current control mode
- **Speed Limitations**: Enable field weakening with proper thermal management