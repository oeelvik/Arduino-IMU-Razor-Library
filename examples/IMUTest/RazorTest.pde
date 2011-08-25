#include <Razor.h>

Razor razor;

void setup(){
 Serial.begin(19200);  
 analogReference(EXTERNAL);
 razor.calibrateGyro();
}

void loop(){
 Serial.print("AccX: ");
 Serial.print(razor.getAccX());
 Serial.print("\tAccY: ");
 Serial.print(razor.getAccY());
 Serial.print("\tAccZ: ");
 Serial.print(razor.getAccZ());
 Serial.print("\tGyroX: ");
 Serial.print(razor.getGyroX());
 Serial.print("\tGyroY: ");
 Serial.print(razor.getGyroY());
 Serial.print("\tGyroZ: ");
 Serial.print(razor.getGyroZ());
 Serial.println();
 
}
