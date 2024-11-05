# waste_segregation_arduino

### Overview
This code is designed for an automatic waste segregation system using an ESP32 or Arduino-compatible microcontroller. The system utilizes various sensors and servos to detect and sort different types of waste into designated categories (e.g., wet, inductive, and other waste).

### Libraries and Variables
- **Wire.h**: Used for I2C communication.
- **LiquidCrystal_I2C.h**: Controls a 16x2 or 20x4 I2C LCD display to provide system status updates.
- **Servo.h**: Allows control of servo motors used in the sorting mechanism.

#### Key Variables:
- **lcd**: LCD object for displaying information.
- **servodrop** and **servosort**: Servo objects to control the drop and sort mechanisms.
- **IRsensor**: An infrared sensor connected to pin 12, which detects incoming waste.
- **Indsensor**: An inductive sensor on analog pin A0, which identifies metallic waste.
- **wls**: Analog pin A1 is used for a wet waste sensor, which measures moisture levels.
- **wastestate**: Indicates if there is waste detected in the system.

### Setup
1. **LCD Initialization**: Sets up and initializes the LCD display with a welcome message.
2. **Servo Attachments**: Attaches the servos to specific pins for waste dropping and sorting actions.
3. **Sensor Setup**: Defines the IR, inductive, and wet sensors as input devices.
4. **Servo Calibration**: Moves the servos to initial positions for calibration.

### Main Loop
The main loop continuously checks sensor readings and performs the following actions:

1. **Reading Sensors**: 
   - **IRsensor** detects the presence of incoming waste.
   - **Indsensor** determines if the waste is metallic.
   - **WetSensor** checks for moisture to identify wet waste.
   - Sensor values are displayed on the LCD.

2. **Waste Detection**:
   - **IRsensor Activation**: If waste is detected (IR sensor triggered), the code sets `wastestate` to 1 and pauses for further inspection.
   
3. **Waste Sorting**:
   - If `wastestate` is 1, the system inspects the waste using the Indsensor and WetSensor.
   - **Wet Waste**: If the wet sensor value exceeds a threshold and the inductive sensor is not triggered, it is categorized as wet waste.
     - The servo sorts the waste to the "wet" position, drops it, and resets.
   - **Inductive Waste**: If the inductive sensor is triggered, it is categorized as metallic waste.
     - The servo sorts to the "metal" position, drops it, and resets.
   - **Other Waste**: If neither wet nor metallic waste is detected, the system classifies it as other waste.
     - The system moves the waste to a default drop location.

4. **Reset**: Once waste is sorted and dropped, the system resets `wastestate` to 0, ready to process the next piece of waste.

### Functions
- **drop(int x)**: Sets the angle of `servodrop` to open or close the waste drop mechanism.
- **sort(int y)**: Sets the angle of `servosort` to move the sorting mechanism to designated positions.

### Usage
This code enables automatic segregation of waste into categories with appropriate sorting and disposal using servos. The LCD provides real-time feedback on waste type and system status, and the Serial Monitor outputs detailed sensor readings for debugging.
