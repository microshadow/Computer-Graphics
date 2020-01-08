#include "fast_mass_springs_precomputation_dense.h"
#include "signed_incidence_matrix_dense.h"
#include <Eigen/Dense>
#include <cmath>

bool fast_mass_springs_precomputation_dense(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::MatrixXd & M,
  Eigen::MatrixXd & A,
  Eigen::MatrixXd & C,
  Eigen::LLT<Eigen::MatrixXd> & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());

  r.resize(E.rows());
  for (auto i = 0; i < E.rows(); ++i)
  {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();     // P_i - P_j
  }

  M = Eigen::MatrixXd::Zero(V.rows(), V.rows());  // #V by #V
  // calculate for M
  // M_ij = m_i if i == j, otherwise it is 0
  for(auto i = 0; i < V.rows(); ++i){
    M(i, i) = m(i);
  }

  // calculate for A
  A = Eigen::MatrixXd::Zero(E.rows(), V.rows());   // #E by #V
  signed_incidence_matrix_dense(V.rows(), E, A);


  C = Eigen::MatrixXd::Zero(b.rows(), V.rows());   // #b by #V
  // calculate for C
  for (auto i = 0; i < b.rows(); ++i)
  {
    C(i, b(i)) = 1;
  }

  Q = k * A.transpose() * A + 1 / (pow(delta_t, 2)) * M + 1e10 * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
