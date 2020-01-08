#include "fast_mass_springs_step_dense.h"
#include <igl/matlab_format.h>
#include <cmath>

void fast_mass_springs_step_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXi & b,
  const double delta_t,
  const Eigen::MatrixXd & fext,
  const Eigen::VectorXd & r,
  const Eigen::MatrixXd & M,
  const Eigen::MatrixXd & A,
  const Eigen::MatrixXd & C,
  const Eigen::LLT<Eigen::MatrixXd> & prefactorization,
  const Eigen::MatrixXd & Uprev,
  const Eigen::MatrixXd & Ucur,
  Eigen::MatrixXd & Unext)
{
  //////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  //Eigen::MatrixXd Q = k * A.transpose() * A + 1 / (pow(delta_t, 2)) * M + 1e10 * C.transpose() * C;
  Eigen::MatrixXd y = pow(1 / delta_t, 2) * M * (2 * Ucur - Uprev) + fext;  // y
  Eigen::MatrixXd d = Eigen::MatrixXd::Zero(E.rows(), 3);
  Unext = Ucur;

  for(int iter = 0;iter < 50;iter++)
  {
    for (auto i = 0; i < E.rows(); ++i)
    {
      d.row(i) = (A * Unext).row(i) / (A * Unext).row(i).norm() * r(i);
    }
    const Eigen::MatrixXd l = k * A.transpose() * d + y + 1e10 * C.transpose() * C * V;
    Unext = prefactorization.solve(l);
  }
  //////////////////////////////////////////////////////////////////////////////
}
