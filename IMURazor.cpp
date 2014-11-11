#include "IMURazor.h"

void IMURazor::init(){
  while (!calibrateGyro()){
    //Retry calibration until success
  }
}

void IMURazor::update(){

  //------------------
  // Gyro
  //------------------
  static Vector3D wG;
  wG.set(
      (analogRead(_gyro_x_pin) - _gyro_x_zero) * _gyro_x_reverse,
      (analogRead(_gyro_y_pin) - _gyro_y_zero) * _gyro_y_reverse,
      (analogRead(_gyro_z_pin) - _gyro_z_zero) * _gyro_z_reverse
    );

  //convert wG to rad/ms
  wG.mult(_GYRO_SCALE);

  //Convert to radians this interval
  unsigned long now = millis();
  int deltaTime = now - _lastTime;
  _lastTime = now;
  wG.mult(deltaTime);


  //------------------
  // Accelerometer
  //------------------
  //Get Accelerometer forces
  static Vector3D Kacc;
  Kacc.set(
      (analogRead(_accel_x_pin) - _accel_x_zero) * _accel_x_reverse,
      (analogRead(_accel_y_pin) - _accel_y_zero) * _accel_y_reverse,
      (analogRead(_accel_z_pin) - _accel_z_zero) * _accel_z_reverse
    );

  //convert Kacc to g
  //Kacc.mult(_ACCEL_SCALE); //we ar going to normalize so this is not nessesary

  //Calculat correction vector
  static Vector3D wA;
  wA.set(&dcm.k).cross(
      &Kacc.mult(-1).norm()
    );


  //------------------
  // Magnetometer
  //------------------
  //Default to North in XZ plane in absens of device
  static Vector3D Kmag;
  Kmag.set(
      sqrt(1 - dcm.i.z * dcm.i.z ),
      0,
      dcm.i.z
    );

  //Calculat correction vector
  static Vector3D wM;
  wM.set(&dcm.i).cross(&Kacc);


  //------------------
  // Update DCM
  //-----------------
  wG
    .add(&wA.mult(_accel_weight))
    .add(&wM.mult(_mag_weight))
    .div(1.0 + _accel_weight + _mag_weight);

  dcm.rotate(&wG);

  IMU::update();
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

void IMURazor::setAccelTrim(float x, float y, float z){
  _accel_x_zero = _ACCEL_ZERO + x;
  _accel_y_zero = _ACCEL_ZERO + y;
  _accel_z_zero = _ACCEL_ZERO + z;
}


void IMURazor::setAccelWeight(float weight){
  _accel_weight = weight;
}

void IMURazor::setMagWeight(float weight){
  _mag_weight = weight;
}

bool IMURazor::calibrateGyro(){
  int x_max = 0;
  int x_min = 1024;
  int y_max = 0;
  int y_min = 1024;
  int z_max = 0;
  int z_min = 1024;

  float x_sum = 0;
  float y_sum = 0;
  float z_sum = 0;

  for(int i = 0; i < 50; i++){
    int x = analogRead(_gyro_x_pin);
    int y = analogRead(_gyro_y_pin);
    int z = analogRead(_gyro_z_pin);

    if (x > x_max) x_max = x;
    if (x < x_min) x_min = x;
    if (y > y_max) y_max = y;
    if (y < y_min) y_min = y;
    if (z > z_max) z_max = z;
    if (z < z_min) z_min = z;

    x_sum += x;
    y_sum += y;
    z_sum += z;
    delay(50);
  }

  //check if copter was moved during mesurements (All mesurements are within aceptable range)
  //TODO: test if working and treshold is ok
  if(
    x_max - x_min > _GYRO_CALIBRATION_TRESHOLD or
    y_max - y_min > _GYRO_CALIBRATION_TRESHOLD or
    z_max - z_min > _GYRO_CALIBRATION_TRESHOLD
    ) {
    return false;
  }

  _gyro_x_zero = x_sum / 50;
  _gyro_y_zero = y_sum / 50;
  _gyro_z_zero = z_sum / 50;

  return true;
}

