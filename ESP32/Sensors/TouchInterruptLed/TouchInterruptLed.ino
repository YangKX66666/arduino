/**
 * This example demonstrates the capacitive touch sensing interrupt functionality on the ESP32. 
 * The ESP32 has 10 capacitive touch pins. We're using T6 (GPIO 14).
 * 
 * When the capacitance value on T6 falls below a set threshold (TOUCH_THRESHOLD), we turn on an LED
 * and keep it on for LED_ON_MS milliseconds 
 * 
 * Official Espressif ESP32 touch sensing docs:
 * https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/touch_pad.html
 * https://github.com/espressif/esp-iot-solution/blob/master/documents/touch_pad_solution/touch_sensor_design_en.md
 * 
 * By Jon E. Froehlich
 * @jonfroehlich
 * http://makeabilitylab.io
 * 
 * Circuit diagram and walkthrough here:
 * https://makeabilitylab.github.io/physcomp/esp32/capacitive-touch-sensing
 * 
 */

const int CAPACITIVE_TOUCH_INPUT_PIN = T6; // GPIO pin 14
const int LED_OUTPUT_PIN = 21;
const int TOUCH_THRESHOLD = 20; // turn on light if touchRead value < this threshold

volatile boolean _touchDetected = false;
volatile unsigned long _touchDetectedTimestamp = 0;
const unsigned long LED_ON_MS = 50; // how long to keep LED on after a touch

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUTPUT_PIN, OUTPUT);
  touchAttachInterrupt(CAPACITIVE_TOUCH_INPUT_PIN, touchDetected, TOUCH_THRESHOLD);
}

void loop() {
  Serial.println((String)"Touch detected: " + _touchDetected);
  if(_touchDetected && (millis() - _touchDetectedTimestamp) < LED_ON_MS){
    digitalWrite(LED_OUTPUT_PIN, HIGH);
  }else{
    _touchDetected = false;
    digitalWrite(LED_OUTPUT_PIN, LOW);
  }
}

void touchDetected(){
  _touchDetected = true;  
  _touchDetectedTimestamp = millis();
}
