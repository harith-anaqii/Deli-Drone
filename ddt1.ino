#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#include <MPU6050.h>

const char* ssid ="WIFI_STUDENT";       // Enter your WiFi SSID
const char* password ="mrsm_student"; // Enter your WiFi password
#define BUZZER_PIN 18
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define GPIO_TRIGGER 26
#define GPIO_ECHO    25
#define IN1 4
#define IN2 23 
#define IN3 5
#define IN4 34

//PID CONTROLLER
const float Kp = 0.5; // Proportional gain
const float Ki = 0.1; // Integral gain
const float Kd = 0.2; // Derivative gain

float error, prev_error = 0;
float integral = 0;
float derivative;

float target_angle_roll = 0;
float target_angle_pitch = 0;

//motor drivers pinout
//motor driver A

//motor driver B

MPU6050 mpu;
const float alpha = 0.96; // Complementary filter constant

WebServer server(80);  // Create a web server that listens on port 80

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup(){

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  // Display Text

      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("DELI-DRONE V1.3X");
  display.display();
  delay(5000);
    display.clearDisplay();

       display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("STARTING UP!");
  display.display();
  display.clearDisplay();

 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("CONNECTING TO WIFI...");
  display.display();
  delay(5000);
  display.clearDisplay();



 if (WiFi.status() == WL_CONNECTED){
        display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("WIFI CONNECTED! ");
  display.display();
      tone(BUZZER_PIN, 1000); // You can adjust the frequency as needed
  delay(300); // Change the duration of the tone
    tone(BUZZER_PIN, 3000);
  delay(300); 
    noTone(BUZZER_PIN);
  delay(5000);
  display.clearDisplay();
 }

 else{
   display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("CONNECTION FAILED,");
  display.display();
    display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println("PLEASE RESTART DRONE!");
  display.display();
  
      tone(BUZZER_PIN, 1000); // You can adjust the frequency as needed
  delay(300); // Change the duration of the tone
    tone(BUZZER_PIN, 3000);
  delay(300); 
     noTone(BUZZER_PIN);
       delay(100); 
      tone(BUZZER_PIN, 3000);
  delay(300); 
   noTone(BUZZER_PIN);
       delay(100); 
        tone(BUZZER_PIN, 3000);
  delay(300); 
   noTone(BUZZER_PIN);
  delay(5000);
  display.clearDisplay();
 }
        display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println(WiFi.localIP());
  display.display();
          display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("IP ADDRESS IS:");
  display.display();
  delay(10000);
  display.clearDisplay();

    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("INITIALIZING DRONE");
    display.setCursor(0,20);
  display.println("COMPONENTS....");
  display.display();
  delay(5000);
  display.clearDisplay();


    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("CONDUCTING SYSTEM");
    display.setCursor(0,20);
  display.println("CHECKS..");
  display.display();
  delay(5000);
  display.clearDisplay();

      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("ARMING MOTORS");
  display.display();


  display.clearDisplay();

      display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("PAWS[OK]");
  display.display();
  delay(2000);
  display.clearDisplay();



    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("DACS[OK]");
  display.display();
  delay(2000);
  display.clearDisplay();


    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("SATNAV[OK]");
  display.display();
  delay(2000);
  display.clearDisplay();

    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("ALL SYSTEMS READY");
  display.display();
  delay(2000);
  display.clearDisplay();

    tone(BUZZER_PIN, 1000); // You can adjust the frequency as needed
  delay(300); // Change the duration of the tone
    tone(BUZZER_PIN, 3000);
  delay(300); 
    noTone(BUZZER_PIN);

      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("DRONE IS READY");
    display.setCursor(0,20);
    display.println("FOR FLIGHT");
  display.display();
  delay(4000);
  display.clearDisplay();



      display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("DELI-DRONE ");
  display.display();
  delay(1000);
  display.clearDisplay();

  }

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/plain", "DELI DRONE FLIGHT CONTROL BOARD");
  });



  // Start the server
  server.begin();
}
 





  

void loop() {
    int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 float Temp = mpu.getTemperature();
 float celsius = (Temp /340.0)+ 36.53;
  // Calculate angle using complementary filter
  float gyroX = (float)gx / 131.0; // Convert raw gyro values to degrees per second
  float angleX = atan2(-ay, az) * 180.0 / M_PI; // Calculate angle from accelerometer data
  float angleXFiltered = alpha * (angleX + gyroX * 0.01) + (1 - alpha) * angleX; // Apply complementary filter
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println(angleXFiltered);


  display.display();
    delay(1000);
    display.clearDisplay();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("DEGREES:");
  display.display();
  

  // Print the angle to the serial monitor
  Serial.print("Angle X: ");
  Serial.println(angleXFiltered);

  server.handleClient();
    long duration, distance;
  
  // Clear the trigger
  digitalWrite(GPIO_TRIGGER, LOW);
  delayMicroseconds(2);
  
  // Set the trigger high for 10 microseconds
  digitalWrite(GPIO_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(GPIO_TRIGGER, LOW);
                                               
  // Measure the duration of the pulse
  duration = pulseIn(GPIO_ECHO, HIGH);
  
  // Calculate the distance
  distance = duration * 0.034 / 2; // Speed of sound is 34 cm/ms, divide by 2 for round trip
    display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,20);
  display.println(distance);
  display.display();
      display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,10);
  display.println("DISTANCE:");
  display.display();
  
   digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  

  }


