#include "localization.hh"

Localization::Localization(){
  xHat << INIT_X[0], INIT_X[1], INIT_X[2], INIT_X[3];
  P << INIT_P[0], 0.0, 0.0, 0.0,
       0.0, INIT_P[1], 0.0, 0.0,
       0.0, 0.0, INIT_P[2], 0.0,
       0.0, 0.0, 0.0, INIT_P[3];
  Q << INIT_Q[0], 0.0, 0.0, 0.0,
       0.0, INIT_Q[1], 0.0, 0.0,
       0.0, 0.0, INIT_Q[2], 0.0,
       0.0, 0.0, 0.0, INIT_Q[3];
  R << INIT_R[0], 0.0, 0.0,
       0.0, INIT_R[1], 0.0,
       0.0, 0.0, INIT_R[2];
  I << 1.0, 0.0, 0.0, 0.0,
       0.0, 1.0, 0.0, 0.0,
       0.0, 0.0, 1.0, 0.0,
       0.0, 0.0, 0.0, 1.0;
  /* Fill other matrix 0 */
  xHatMinus.setZero();
  y.setZero();
  f.setZero();
  h.setZero();
  PMinus.setZero();
  g.setZero();
  A.setZero();
  AT.setZero();
  C.setZero();
  CT.setZero();
  /* Initialize variables */
  lpf.reserve(NUM_OF_IMU_DATA);
  lpf[0] = BIAS[0];
  lpf[1] = BIAS[1];
  lpf[2] = BIAS[2];
  lpf[3] = BIAS[3];
  lpf[4] = BIAS[4];
  lpf[5] = BIAS[5];
}

Localization::~Localization(){
  /* Do nothing */
}

void Localization::update(){
  Gyro* g = Main::mot->getHardware()->getGyro();
  /* Update only possible if gyro exists */
  if(g == NULL){
    return;
  }
  Eigen::Vector3f acc = g->getAcc();
  acc[0] *= GRAV_ACC;
  acc[1] *= GRAV_ACC;
  acc[2] *= GRAV_ACC;
  Eigen::Vector3f gyro = g->getGyro();
  gyro[0] /= TO_DEG;
  gyro[1] /= TO_DEG;
  gyro[2] /= TO_DEG;
  /* Get IMU data and add bias */
  acc[0]  = (acc[0]  * coordinateModifyFactor[0]) - BIAS[0];
  acc[1]  = (acc[1]  * coordinateModifyFactor[1]) - BIAS[1];
  acc[2]  = (acc[2]  * coordinateModifyFactor[2]) - BIAS[2];
  gyro[0] = (gyro[0] * coordinateModifyFactor[3]) - BIAS[3];
  gyro[1] = (gyro[1] * coordinateModifyFactor[4]) - BIAS[4];
  gyro[2] = (gyro[2] * coordinateModifyFactor[5]) - BIAS[5];
  /* Set LPF */
  lpf[0] = IMU_LPF * acc[0] + (1.0 - IMU_LPF) * lpf[0];
  lpf[1] = IMU_LPF * acc[1] + (1.0 - IMU_LPF) * lpf[1];
  lpf[2] = IMU_LPF * acc[2] + (1.0 - IMU_LPF) * lpf[2];
  lpf[3] = IMU_LPF * gyro[0] + (1.0 - IMU_LPF) * lpf[3];
  lpf[4] = IMU_LPF * gyro[1] + (1.0 - IMU_LPF) * lpf[4];
  lpf[5] = IMU_LPF * gyro[2] + (1.0 - IMU_LPF) * lpf[5];
  /* Update */
  prediction(lpf);
  filter(lpf);
  normXHat();
  /* Conversion */
  Eigen::Matrix<double, 3, 3> DCM = getDCM(xHat);
  Eigen::Matrix<double, 3, 1> E = getEuler(DCM);
  std::cout << E(0,0) * TO_DEG << "," << E(1, 0) * TO_DEG << "," << E(2, 0) * TO_DEG << std::endl; // TODO
}

void Localization::prediction(std::vector<double>& imu){
  std::vector<double> w,q;
  w.push_back(static_cast<double>(0));
  for(int i = 3; i < 6; ++i){
    w.push_back(imu[i]);
  }
  A << 1.0, 0.5 * DT * w[3], -0.5 * DT * w[2], 0.5 * DT * w[1],
       -0.5 * DT * w[3], 1.0, 0.5 * DT * w[1], 0.5 * DT * w[2],
       0.5 * DT * w[2], -0.5 * DT * w[1], 1.0, 0.5 * DT * w[3],
       -0.5 * DT * w[1], -0.5 * DT * w[2], -0.5 * DT * w[3], 1.0;
  f = A * xHat;
  xHatMinus = f;
  q.push_back(static_cast<double>(0));
  for(int i = 0; i < 4; ++i){
    q.push_back(xHatMinus[i]);
  }
  CT << 2 * q[3] * GRAV_ACC, -2 * q[4] * GRAV_ACC, 2 * q[1] * GRAV_ACC, -2 * q[2] * GRAV_ACC,
        2 * q[4] * GRAV_ACC, 2 * q[3] * GRAV_ACC, 2 * q[2] * GRAV_ACC, 2 * q[1] * GRAV_ACC,
        -2 * q[1] * GRAV_ACC, -2 * q[2] * GRAV_ACC, 2 * q[3] * GRAV_ACC, 2 * q[4] * GRAV_ACC;
  PMinus = A * P * A.transpose() + Q;
}

void Localization::filter(std::vector<double>& imu) {
  std::vector<double> a, q;
  a.push_back(static_cast<double>(0));
  for(int i = 0; i < 3; ++i){
    a.push_back(imu[i]);
  }
  q.push_back(static_cast<double>(0));
  for(int i = 0; i < 4; ++i){
    q.push_back(xHatMinus[i]);
  }
  C = CT.transpose();
  g = PMinus * C * (CT * PMinus * C + R).inverse();
  y << a[1], a[2], a[3];
  h << 2 * (q[3] * q[1] - q[2] * q[4]) * GRAV_ACC,
       2 * (q[2] * q[3] - q[1] * q[4]) * GRAV_ACC,
       (q[3] * q[3] - q[1] * q[1] - q[2] * q[2] + q[4] * q[4]) * GRAV_ACC;
  xHat = xHatMinus + g * (y - h);
  P = (I - g * CT) * PMinus;
}

void Localization::normXHat(){
  double norm  = sqrt(xHat(0, 0) * xHat(0, 0) +
                      xHat(1, 0) * xHat(1, 0) +
                      xHat(2, 0) * xHat(2, 0) +
                      xHat(3, 0) * xHat(3, 0));
  xHat /= norm;
}

Eigen::Matrix<double, 3, 3> Localization::getDCM(Eigen::Matrix<double, SIZE_VECTOR_X, 1>& x){
  Eigen::Matrix<double, 3, 3> dcm;
  std::vector<double> q;
  q.push_back(static_cast<double>(0));
  for(int i = 0; i < 4; ++i){
    q.push_back(x(i,0));
  }
  dcm << q[1] * q[1] - q[2] * q[2] - q[3] * q[3] + q[4] * q[4],
         2 * (q[1] * q[2] + q[3] * q[4]),
         2 * (q[3] * q[1] - q[2] * q[4]),
         2 * (q[1] * q[2] - q[3] * q[4]),
         q[2] * q[2] - q[3] * q[3] - q[1] * q[1] + q[4] * q[4],
         2 * (q[2] * q[3] + q[1] * q[4]),
         2 * (q[3] * q[1] + q[2] * q[4]),
         2 * (q[2] * q[4] - q[1] * q[4]),
         q[3] * q[3] - q[1] * q[1] - q[2] * q[2] + q[4] * q[4];
  return dcm;
}

Eigen::Matrix<double, 3, 1> Localization::getEuler(Eigen::Matrix<double, 3, 3>& dcm){
  Eigen::Matrix<double, 3, 1> euler;
  double pitch = asin(-1.0 * dcm(0, 2));
  double yaw = atan2(dcm(0, 1) / cos(pitch), dcm(0, 0) / cos(pitch));
  double roll = atan2(dcm(1, 2) / cos(pitch), dcm(2, 2) / cos(pitch));
  euler << roll, pitch, yaw;
  return euler;
}

Eigen::Matrix<double, 3, 1> Localization::getEulerFromAccData(std::vector<double>& imu){
  Eigen::Matrix<double, 3, 1> euler;
  double acc = sqrt(imu[0] * imu[0] + imu[1] * imu[1] + imu[2] * imu[2]);
  double pitch = asin(-1.0 * imu[0] / acc);
  double yaw = static_cast<double>(0);
  double roll;
  if(imu[2] > 0.0){
    roll = atan2(imu[1] / acc / cos(pitch), imu[2] / acc / cos(pitch));
  }else{
    roll = atan2(imu[1] / acc / cos(pitch), imu[2] / acc / cos(pitch));
  }
  euler << roll, pitch, yaw;
  return euler;
}
