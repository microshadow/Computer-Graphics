#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  SV = V;
  SF = F;

  int number_of_edges = V.rows() * V.rows() / 2;
  std::vector<int> C_N_count(V.rows(), 0);
  Eigen::MatrixXd SV_prime = Eigen::MatrixXd::Zero(V.rows() + F.rows() + number_of_edges, 3);
  Eigen::MatrixXi SF_prime = Eigen::MatrixXi::Zero(F.rows() * 4, 4);

  Eigen::MatrixXd C_F = Eigen::MatrixXd::Zero(V.rows(), 3);
  Eigen::MatrixXd C_R = Eigen::MatrixXd::Zero(V.rows(), 3);

  std::vector<int> l(V.rows(), -1);
  std::vector<std::vector<int>> mapping_edge(V.rows(), l);

  number_of_edges = 0;

  for (auto i = 0; i < F.rows(); ++i){
      Eigen::RowVector3d fp = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
      int fp_i = V.rows() + i;
      SV_prime.row(fp_i) = fp;

      C_F.row(F(i,0)) += fp;
      C_F.row(F(i,1)) += fp;
      C_F.row(F(i,2)) += fp;
      C_F.row(F(i,3)) += fp;
      C_N_count[F(i,0)] += 1;
      C_N_count[F(i,1)] += 1;
      C_N_count[F(i,2)] += 1;
      C_N_count[F(i,3)] += 1;

      int ep1, ep2, ep3, ep4;

      if(mapping_edge[F(i,0)][F(i,1)] == -1){
          Eigen::RowVector3d ep_prim1 = (V.row(F(i, 0)) + V.row(F(i, 1)));

          ep1 = V.rows() + F.rows() + number_of_edges;
          SV_prime.row(ep1) = ep_prim1 + fp;
          mapping_edge[F(i,0)][F(i,1)] = number_of_edges;
          mapping_edge[F(i,1)][F(i,0)] = number_of_edges;

          number_of_edges ++;
      }else{
          ep1 = V.rows() + F.rows() + mapping_edge[F(i,0)][F(i,1)];
          SV_prime.row(ep1) = (SV_prime.row(ep1) + fp) * 0.25;
          C_R.row(F(i,0)) += SV_prime.row(ep1);
          C_R.row(F(i,1)) += SV_prime.row(ep1);
      }

      if(mapping_edge[F(i,1)][F(i,2)] == -1){
          Eigen::RowVector3d ep_prim2 = (V.row(F(i, 1)) + V.row(F(i, 2)));

          ep2 = V.rows() + F.rows() + number_of_edges;
          SV_prime.row(ep2) = ep_prim2 + fp;

          mapping_edge[F(i,1)][F(i,2)] = number_of_edges;
          mapping_edge[F(i,2)][F(i,1)] = number_of_edges;

          number_of_edges ++;
      }else{
          ep2 = V.rows() + F.rows() + mapping_edge[F(i,1)][F(i,2)];
          SV_prime.row(ep2) = (SV_prime.row(ep2) + fp) * 0.25;
          C_R.row(F(i,1)) += SV_prime.row(ep2);
          C_R.row(F(i,2)) += SV_prime.row(ep2);
      }

      if(mapping_edge[F(i,2)][F(i,3)] == -1){
          Eigen::RowVector3d ep_prim3 = (V.row(F(i, 2)) + V.row(F(i, 3)));

          ep3 = V.rows() + F.rows() + number_of_edges;
          SV_prime.row(ep3) = ep_prim3 + fp;

          mapping_edge[F(i,2)][F(i,3)] = number_of_edges;
          mapping_edge[F(i,3)][F(i,2)] = number_of_edges;

          number_of_edges ++;
      }else{
          ep3 = V.rows() + F.rows() + mapping_edge[F(i,2)][F(i,3)];
          SV_prime.row(ep3) = (SV_prime.row(ep3) + fp) * 0.25;
          C_R.row(F(i,2)) += SV_prime.row(ep3);
          C_R.row(F(i,3)) += SV_prime.row(ep3);
      }

      if(mapping_edge[F(i,3)][F(i,0)] == -1){
          Eigen::RowVector3d ep_prim4 = (V.row(F(i, 3)) + V.row(F(i, 0)));

          ep4 = V.rows() + F.rows() + number_of_edges;
          SV_prime.row(ep4) = ep_prim4 + fp;

          mapping_edge[F(i,3)][F(i,0)] = number_of_edges;
          mapping_edge[F(i,0)][F(i,3)] = number_of_edges;

          number_of_edges ++;
      }else{
          ep4 = V.rows() + F.rows() + mapping_edge[F(i,3)][F(i,0)];
          SV_prime.row(ep4) = (SV_prime.row(ep4) + fp) * 0.25;
          C_R.row(F(i,3)) += SV_prime.row(ep4);
          C_R.row(F(i,0)) += SV_prime.row(ep4);
      }

      SF_prime.row(i * 4) << F(i, 0), ep1, fp_i, ep4;
      SF_prime.row(i * 4 + 1) << F(i, 1), ep2, fp_i, ep1;
      SF_prime.row(i * 4 + 2) << F(i, 2), ep3, fp_i, ep2;
      SF_prime.row(i * 4 + 3) << F(i, 3), ep4, fp_i, ep3;
  }

  SV_prime.conservativeResize(V.rows() + F.rows() + number_of_edges, 3);

  for (int i = 0; i < V.rows(); i++){
      Eigen::RowVector3d new_F = C_F.row(i) * (double(1) / C_N_count[i]);
      Eigen::RowVector3d new_R = C_R.row(i) * (double(1) / C_N_count[i]);

      SV_prime.row(i) = (new_F + 2 * new_R + (C_N_count[i] - 3) * V.row(i)) * (double(1) / C_N_count[i]);
  }

  if (num_iters == 1){
      SV = SV_prime;
      SF = SF_prime;
  }else{
      catmull_clark(SV_prime, SF_prime, num_iters - 1, SV, SF);
  }

  ////////////////////////////////////////////////////////////////////////////
}