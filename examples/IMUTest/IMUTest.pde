#include <IMU.h>

//Sensor pins
#define GYRO_ROLL_PIN 4
#define GYRO_NICK_PIN 3
#define GYRO_YAW_PIN 5
#define ACC_ROLL_PIN 1
#define ACC_NICK_PIN 2
#define ACC_VERT_PIN 0
#define YAW_SERVO_PIN 9

IMU imu;

float gyro_scale = 11.044;//(1024/360)/1024 * 3,3/0,00083 (0,83mv/deg/sec)
float acc_scale = (float)1024 / 4 / 102;//(float) 300 / 3300 * 1024; //300[mV pr g] / 3300[Aref] * 1024 = 93 [val at 1g] //Adjusted to 102 after trail and error

void setup(){
  analogReference(EXTERNAL);
  
  imu.setGyroScale(gyro_scale);
  imu.setAccScale(acc_scale);
  imu.setAccGain(0.04);
  imu.setAccTrim(-12, -4, 40);
  imu.setPins(GYRO_ROLL_PIN, GYRO_NICK_PIN, GYRO_YAW_PIN, ACC_ROLL_PIN, ACC_NICK_PIN, ACC_VERT_PIN);
  imu.setReversing(true, true, true, false, false, false);
  imu.calibrateGyro();
  Serial.begin(115200);
}

void loop(){
  imu.update();
  
  //appy Killmore Ground station protocol
  send_attitude();
  send_location();
  
  /*
  Serial.print(imu.getAccRoll());
  Serial.print("\t");
  Serial.print(imu.getAccNick());
  Serial.print("\t");*/
  
  
  /*Serial.print(imu.getRollDegree());
  Serial.print("\t");
  Serial.print(imu.getNickDegree());
  Serial.print("\t");
  Serial.print(imu.getYawDegree());
  Serial.print("\t");*/
  
  //Enable to find acc trim
  /*Serial.print(analogRead(ACC_ROLL_PIN) - 511); //Should be 0 (example if this value is -10 your trim should be -10)
  Serial.print("\t");
  Serial.print(analogRead(ACC_NICK_PIN) - 511); //Should be 0 (example if this value is -10 your trim should be -10)
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