#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  std::vector<Eigen::Triplet<double> > ijv;
  std::vector<Eigen::Triplet<double> > cijv;
  const int n = V.rows();
  //for(int i = 0;i<n;i++) ijv.emplace_back(i,i,1);
  Eigen::SparseMatrix<double> Q(n,n);
  //Q.setFromTriplets(ijv.begin(),ijv.end());

  // copy from dense file and modify..
  //Eigen::MatrixXd Q = Eigen::MatrixXd::Identity(V.rows(),V.rows());

  r.resize(E.rows());
  for (auto i = 0; i < E.rows(); ++i)
  {
    r(i) = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();     // P_i - P_j
  }

  M.resize(n, n);
  // calculate for M
  // M_ij = m_i if i == j, otherwise it is 0
  for(auto i = 0; i < V.rows(); ++i){
    // no idea how to interpolate Eigen::Triplet, so I write this way
    ijv.emplace_back(Eigen::Triplet<double>(i, i, m(i)));
  }
  M.setFromTriplets(ijv.begin(), ijv.end());

  // calculate for A
  signed_incidence_matrix_sparse(n, E, A);


  C.resize(b.rows(), n);
  // calculate for C
  for (auto i = 0; i < b.rows(); ++i)
  {
    cijv.emplace_back(Eigen::Triplet<double>(i, b(i), 1));
  }
  C.setFromTriplets(cijv.begin(), cijv.end());

  Q = k * A.transpose() * A + 1 / (pow(delta_t, 2)) * M + 1e10 * C.transpose() * C;

  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
