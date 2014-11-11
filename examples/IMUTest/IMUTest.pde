#include <IMURazor.h>

//Sensor pins
#define GYRO_ROLL_PIN 4
#define GYRO_NICK_PIN 5
#define GYRO_YAW_PIN 3
#define ACC_ROLL_PIN 1
#define ACC_NICK_PIN 2
#define ACC_VERT_PIN 0
#define YAW_SERVO_PIN 9

IMURazor imu;

void setup(){
  analogReference(EXTERNAL);
  Serial.begin(115200);
  
  imu.setAccelWeight(0.04);
  imu.setMagWeight(0.0);
  imu.setAccelTrim(-5, -7.5, 40);
  imu.setPins(ACC_NICK_PIN, ACC_ROLL_PIN, ACC_VERT_PIN, GYRO_ROLL_PIN, GYRO_NICK_PIN, GYRO_YAW_PIN);
  imu.setReversing(false, true, true, false, false, false);
  imu.init();
}

void loop(){
  imu.update();
  
  //appy Killmore Ground station protocol
  send_attitude();
  send_location();
  
  /*Serial.print(imu.getRollDegree());
  Serial.print("\t");
  Serial.print(imu.getNickDegree());
  Serial.print("\t");
  Serial.print(imu.getYawDegree());
  Serial.print("\t");*/
  
  //Enable to find acc trim
  /*Serial.print("\t");
  Serial.print(analogRead(ACC_NICK_PIN) - 511); //Should be 0 (example if this value is -10 your trim should be -10)
  Serial.print("\t");
  Serial.print(analogRead(ACC_ROLL_PIN) - 511); //Should be 0 (example if this value is -10 your trim should be -10)
  Serial.print("\t");
  Serial.print(analogRead(ACC_VERT_PIN) - 511); //Should be ca 100 (value at 1g) (example if this value is 142 your trim should be 142 - 100 = 42)
  */
  Serial.println();
  delay(19);
}

void send_attitude(){
  Serial.print("+++"); //Prefix
  Serial.print("ASP:"); //Airspeed
  Serial.print(20, DEC);
  Serial.print(",THH:"); //Throttle
  Serial.print(0);
  Serial.print (",RLL:"); //Roll
  Serial.print(imu.getRollDegree());//(analogRead(ACC_ROLL_PIN) - init_acc_roll) * acc_scale, DEC);
  Serial.print (",PCH:"); //Pitch
  Serial.print(imu.getNickDegree());
  Serial.println(",***"); //Suffix
}

void send_location(){
  Serial.print("!!!"); //Prefix
  Serial.print("LAT:"); //Latitude
  Serial.print("67967300");//"33952600");
  Serial.print(",LON:"); //Longitude
  Serial.print("14994700");//"-117409072");
  Serial.print(",SPD:"); //Speed over ground from GPS
  Serial.print(30);
  Serial.print(",CRT:"); //Climb rate m/s
  Serial.print("100");
  Serial.print(",ALT:"); //Altitude in meters
  Serial.print(1000);
  Serial.print(",ALH:"); //Target Altitude
  Serial.print("450");
  Serial.print(",CRS:"); //Course over ground in degrees
  Serial.print(imu.getYawDegree()); 
  Serial.print(",BER:"); //Bearing (target heading)
  Serial.print("94");
  Serial.print(",WPN:"); //Waypoint number
  Serial.print("0");
  Serial.print(",DST:"); //Distance from Waypoint
  Serial.print("25853");
  Serial.print(",BTV:"); //Battery voltage
  Serial.print("11840");
  Serial.println(",***"); //suffix
}