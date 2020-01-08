#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  Eigen::Vector4d O;
  Eigen::Vector3d P(0, 0, 0);
  //double bias;  // scope issue
  U.resize(V.rows(), V.cols());

    for (auto i = 0; i < V.rows(); ++i) {
        O << V.row(i)(0), V.row(i)(1), V.row(i)(2), 1;

        for (auto j = 0; j < skeleton.size(); ++j) {
            double bias;
            if(skeleton[j].weight_index != -1){
                bias = W(i, skeleton[j].weight_index);
            }

            P += bias * ((T[j] * O).head(3) / (T[j] * O)(3));
        }

        U.row(i) = P;
    }

  U = V;
  /////////////////////////////////////////////////////////////////////////////
}
