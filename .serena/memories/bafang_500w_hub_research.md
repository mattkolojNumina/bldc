# Bafang 500W Front Hub Motor Research

## Key Technical Specifications

### Electrical Parameters
- **Rated Voltage**: 36V/48V DC (typically 48V for 500W model)
- **Rated Power**: 500W continuous
- **Phase Resistance**: 70-145 mΩ (10T variant: ~139 mΩ)
- **Phase Inductance**: 190-275 μH 
- **No-Load Current**: ≤1.4A at 48V
- **No-Load RPM**: 330 RPM at 48V (Kv ≈ 6.875 RPM/V)
- **Pole Pairs**: 10 (20 magnetic poles total)
- **Winding**: 10 turns standard (10T), 6.5T fast-wind variant available

### Mechanical Specifications  
- **Weight**: 3.4 kg
- **Max Torque**: 45 Nm peak (≤30s duty)
- **Gear Reduction**: 5:1 helical planetary gears
- **Dropout Width**: 100mm (front fork)
- **Spoke Holes**: 36H, 122mm flange diameter
- **Brake**: Disc compatible (6-bolt, 160mm rotor)

### Efficiency Characteristics
- **Peak Efficiency**: ≥80% at 18-28 km/h (medium speeds)
- **Low-Speed Inefficiency**: Drops to 46% at 6.4 km/h (4 mph)
- **Thermal Limits**: Derates to 250W after 5-8 minutes at full 500W
- **Operating Temperature**: -20°C to 45°C

## Critical Performance Insights

### Efficiency Curve Analysis
- Hub motors are inherently inefficient at low speeds
- Peak efficiency zone: 18-28 km/h
- Below 10 km/h: Efficiency drops dramatically due to gear losses
- Above 32 km/h: Efficiency falls due to eddy currents

### Thermal Management
- Continuous power rating: ~250W (thermal limited)
- Peak power: 500W for short bursts only
- Nylon gear heating limits sustained performance
- Controller thermal protection at 120°C

### Winding Variants Impact
- 10T Standard: Better torque at low RPM, 325 RPM no-load
- 6.5T Fast-wind: Higher top speed, 400 RPM no-load
- Lower turn count = less copper loss but reduced torque

## Motor Control Implications

### Hall Sensor Configuration
- 3x Hall sensors at 120° spacing
- Enables trapezoidal commutation
- Sensorless fallback mode available (10% torque loss)

### Optimal Operating Points
- Best efficiency: 18-25 km/h with moderate load
- Avoid sustained operation below 10 km/h
- Thermal management critical above 300W continuous

### FOC Control Advantages
- Improved low-speed efficiency vs hall commutation
- Better torque ripple control
- Field weakening capability for extended speed range