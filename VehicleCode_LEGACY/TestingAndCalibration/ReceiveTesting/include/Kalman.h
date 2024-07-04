// #ifndef KALMAN_FILTER_H
// #define KALMAN_FILTER_H

// #include "C:\Users\dalli\source\repos\BYURacing\eigen-3.4.0\Eigen\Dense"
// // #include <Eigen/Dense> // Include Eigen library for matrix operations

// using namespace Eigen;

// class KalmanFilter {
// private:
//     MatrixXd F, Q, H, R, G;
//     VectorXd u;

// public:
//     KalmanFilter(MatrixXd _F, MatrixXd _Q, MatrixXd _H, MatrixXd _R, MatrixXd _G, VectorXd _u);

//     std::tuple<MatrixXd, MatrixXd> evolve(VectorXd x0, int N);
//     MatrixXd estimate(VectorXd x0, MatrixXd P0, MatrixXd z);
//     MatrixXd predict(VectorXd x, int k);
//     MatrixXd rewind(VectorXd x, int k);
// };

// #endif // KALMAN_FILTER_H
