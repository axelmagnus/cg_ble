
#include <Adafruit_seesaw.h>
#include <seesaw_motor.h
#include <seesaw_servo.h>

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
Adafruit_Seesaw ss;

const int JOY_X_PIN = 2; // Analog input channel for X-axis of joystick
const int JOY_Y_PIN = 3; // Analog input channel for Y-axis of joystick

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("RC_Car_Controller"); // Bluetooth device name

  if (!ss.begin())
  {
    Serial.println("Failed to initialize Seesaw!");
    while (1)
      ;
  }
}

void loop()
{
  // Read joystick values
  int16_t x = ss.analogRead(JOY_X_PIN);
  int16_t y = ss.analogRead(JOY_Y_PIN);

  // Convert joystick values to motor speeds
  int16_t speedA = y + x;
  int16_t speedB = y - x;

  // Send motor speeds over Bluetooth
  SerialBT.print(speedA);
  SerialBT.write(',');
  SerialBT.print(speedB);
  SerialBT.write('\n');

  delay(50); // Adjust delay as needed
}
