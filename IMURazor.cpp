#include "IMURazor.h"

IMURazor::IMURazor(){
  calibrateGyro();
}


void IMURazor::update(){


  //------------------
  // Gyro
  //------------------
  static Vector3D wG;
  wG.set(
      analogRead(_gyro_x_pin) - _gyro_x_zero,
      analogRead(_gyro_y_pin) - _gyro_y_zero,
      analogRead(_gyro_z_pin) - _gyro_z_zero
    )

  //TODO: convert wG to rad/ms
  //wG.mult(?)

  //Convert to radians this interval
  unsigned long int now = millis;
  int deltaTime = now - _lastTime;
  wG.mult(deltaTime);

  //------------------
  // Accelerometer
  //------------------
  //Get Accelerometer forces
  static Vector3D Kacc;
  Kacc.set(
      analogRead(_accel_x_pin) - _accel_x_zero,
      analogRead(_accel_y_pin) - _accel_y_zero,
      analogRead(_accel_z_pin) - _accel_z_zero
    )

  //Calculat correction vector
  static Vector3D wA;
  wA.set(&dcm.z).cross(
      Kacc.mult(-1).norm()
    );


  //------------------
  // Magnetometer
  //------------------
  //Default to North in XZ plane in absens of device
  static Vector3D Kmag;
  Kmag.set(
      sqrt(1 - dcm.x.z * dcm.x.z ),
      0,
      dcm.x.z
    );

  //Calculat correction vector
  static Vector3D wM;
  wM.set(&dcm.x).cross(Kacc);


  //------------------
  // Update DCM
  //-----------------
  wG
    .add(wA.mult(_accel_weight))
    .add(wM.mult(_mag_weight))
    .div(1.0 + _accel_weight + _mag_weight);

  dcm.rotate(wG);
}

void IMURazor::setPins(int acc_x, int acc_y, int acc_z, int gyro_x, int gyro_y, int gyro_z) {
  _accel_x_pin = acc_x;
  _accel_y_pin = acc_y;
  _accel_z_pin = acc_z;
  _gyro_x_pin = gyro_x;
  _gyro_y_pin = gyro_y;
  _gyro_z_pin = gyro_z;
}

void IMURazor::setReversing(bool acc_x, bool acc_y, bool acc_z, bool gyro_x, bool gyro_y, bool gyro_z) {
  _accel_x_reverse = (acc_x) ? -1 : 1;
  _accel_y_reverse = (acc_y) ? -1 : 1;
  _accel_z_reverse = (acc_z) ? -1 : 1;
  _gyro_x_reverse = (gyro_x) ? -1 : 1;
  _gyro_y_reverse = (gyro_y) ? -1 : 1;
  _gyro_z_reverse = (gyro_z) ? -1 : 1;
}

void IMURazor::setAccelTrim(int x, int y, int z){
  _accel_x_zero += x;
  _accel_y_zero += y;
  _accel_z_zero += z;
}


void IMURazor::setAccelWeight(float weight){
  _accel_weight = weight;
}

void IMURazor::setMagWeight(float weight){
  _mag_weight = weight;
}

void IMURazor::calibrateGyro(){
  //TODO: check if copter was moved during mesurements (All mesurements are within aceptable range)
  long x_sum = 0;
  long y_sum = 0;
  long z_sum = 0;
  for(int i = 0; i < 50; i++){
    x_sum += analogRead(_gyro_x_pin);
    y_sum += analogRead(_gyro_y_pin);
    z_sum += analogRead(_gyro_z_pin);
    //TODO: Add delay?
  }

  _gyro_x_zero = x_sum / 50;
  _gyro_y_zero = y_sum / 50;
  _gyro_z_zero = z_sum / 50;
}

