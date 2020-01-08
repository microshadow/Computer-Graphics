#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  // if keyframe is empty
  if(keyframes.empty()){
      return Eigen::Vector3d::Zero(3);
  }

  float key = keyframes[0].first;
  double d;
  Eigen::Vector3d a, b;
  Eigen::Matrix4d M, P;
  P.resize(3, 4);
  M << 0, 1, 0, 3,
        0, 1, 0, 2,
        0, 1, 1, 1,
        1, 1, 0, 0;

    for (auto i = 0; i < keyframes.size() - 1; ++i) {
        if((t <= keyframes[i + 1].first) && (t >= keyframes[i].first)){
            P.col(0) = keyframes[i].second;
            P.col(1) = keyframes[i + 1].second;

            if(i == 0){
                a = (keyframes[i + 1].second - keyframes[i].second) / (keyframes[i + 1].first - keyframes[i].first);
                b = (keyframes[i + 2].second - keyframes[i].second) / (keyframes[i + 2].first - keyframes[i].first);
            } else if(i >= keyframes.size() - 2){
                a = (keyframes[i + 1].second - keyframes[i - 1].second) / (keyframes[i + 1].first - keyframes[i - 1].first);
                b = (keyframes[i + 1].second - keyframes[i].second) / (keyframes[i + 1].first - keyframes[i].first);
            } else{
                a = (keyframes[i + 1].second - keyframes[i - 1].second) / (keyframes[i + 1].first - keyframes[i - 1].first);
                b = (keyframes[i + 2].second - keyframes[i].second) / (keyframes[i + 2].first - keyframes[i].first);
            }

            d = (t - keyframes[i].first) / (keyframes[i + 1].first - keyframes[i].first);
        }
    }

    a /= 2;
    b /= 2;
    P.col(2) = a;
    P.col(3) = b;

    Eigen::MatrixXd T = P * M.inverse();
    auto result = pow(d, 3) * T.col(0) + pow(d, 2) * T.col(1) + d * T.col(2) + T.col(3);

  return result;
  /////////////////////////////////////////////////////////////////////////////
}
