#pragma once

#include <cmath>
#include <vector>
#include <Eigen/Dense>

/* NOTE: The following field layout:
   +-------+ (fW/2,fH/2) <- Enemy goal keeper
   |       |
   | (0,0) |
   +---+---+ (fw/2,0)
   |       |
   |       |
   +-------+ (fw/2,-fH/2) <- Our goal keeper */

    static const int NUM_OF_IMU_DATA = 6;
    static const double FIRST_TIME = 0.01;
    static const double DT = 0.01;
    static const double GRAV_ACC = 9.80665;
    static const double TO_DEG = 57.2958;
    static const double IMU_LPF = 0.07;
    static const std::vector<double> coordinateModifyFactor{ 1.0, -1.0, 1.0, -1.0, 1.0, -1.0 };
    static const std::vector<double> BIAS{ 0, 0, 0, 0, 0, 0 };

    static const std::vector<double> INIT_P{ 0.0001, 0.0001, 0.0001, 0.0001 };
    static const std::vector<double> INIT_Q{ 0.01, 0.01, 0.01, 0.01 };
    static const std::vector<double> INIT_R{ 1.0, 1.0, 10.0 };
    static const std::vector<double> INIT_X{ 0.0, 0.0, 0.0, 1.0 };
    static const int SIZE_VECTOR_X = 4;
    static const int SIZE_VECTOR_Y = 3;

/**
 * localization.hh
 *
 * Allow the player to update and track localization related information.
 **/
class Localization{
  private:
    Eigen::Matrix<double, SIZE_VECTOR_X, 1> xHat;
    Eigen::Matrix<double, SIZE_VECTOR_X, 1> xHatMinus;
    Eigen::Matrix<double, SIZE_VECTOR_Y, 1> y;
    Eigen::Matrix<double, SIZE_VECTOR_X, 1> f;
    Eigen::Matrix<double, SIZE_VECTOR_Y, 1> h;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> A;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> AT;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_Y> C;
    Eigen::Matrix<double, SIZE_VECTOR_Y, SIZE_VECTOR_X> CT;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_Y> g;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> P;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> PMinus;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> Q;
    Eigen::Matrix<double, SIZE_VECTOR_Y, SIZE_VECTOR_Y> R;
    Eigen::Matrix<double, SIZE_VECTOR_X, SIZE_VECTOR_X> I;
    std::vector<double> lpf;

  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /**
     * Localization()
     *
     * Initialize the localization system.
     **/
    Localization();

    /**
     * ~Localization()
     *
     * De-initialize the localization system and free up resources.
     **/
    ~Localization();

    void update();

  private:
    void prediction(std::vector<double>& imu);

    void filter(std::vector<double>& imu);

    void normXHat();

    static Eigen::Matrix<double, 3, 3> getDCM(Eigen::Matrix<double, SIZE_VECTOR_X, 1>& x);

    static Eigen::Matrix<double, 3, 1> getEuler(Eigen::Matrix<double, 3, 3>& dcm);

    static Eigen::Matrix<double, 3, 1> getEulerFromAccData(std::vector<double>& imu);
};
