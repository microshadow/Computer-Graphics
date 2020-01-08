#include "projected_gradient_descent.h"
#include "line_search.h"

void projected_gradient_descent(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const int max_iters,
  Eigen::VectorXd & z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Add your code here
  Eigen::VectorXd gradient;
  double step;
  for (auto i = 0; i < max_iters; ++i){
      gradient = grad_f(z);
      step = line_search(f, proj_z, z, gradient, 10000);
      z -= (step * gradient);
      proj_z(z);
      if (step == 0){
          break;
      }
  }

  /////////////////////////////////////////////////////////////////////////////
}
