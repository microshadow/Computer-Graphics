#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <string>


bool write_obj(
  const std::string & output_filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:

  std::ofstream output_file;

  output_file.open(output_filename, std::ios::out);
  if(!output_file){
      std::cerr << "Cannot open output_file..." << std::endl;
      return false;
  }

  if(output_file.fail()){
      std::cout << "some other error, eg. file type is not .obj" << std::endl;
      return false;
  }

  for (auto i = 0; i < V.rows(); ++i){
      output_file << "v";
      for (auto j = 0; j < V.cols(); ++j){
          output_file << " " << V(i, j);
      }
      output_file << std::endl;
  }

  for (auto i = 0; i < UV.rows(); ++i){
      output_file << "vt";
      for (auto j = 0; j < UV.cols(); ++j){
          output_file << " " << UV(i, j);
      }
      output_file << std::endl;
  }

  for (auto i = 0; i < NV.rows(); ++i){
      output_file << "vn";
      for (auto j = 0; j < NV.cols(); ++j){
          output_file << " " << NV(i, j);
      }
      output_file << std::endl;
  }

  for (auto i = 0; i < F.rows(); ++i){
      output_file << "f";
      for (auto j = 0; j < F.cols(); ++j){
          output_file << " " << F(i, j) + 1 << "/" << UF(i, j) + 1 << "/" << NF(i, j) + 1;
      }
      output_file << std::endl;
  }

  output_file.close();
  return true;

  ////////////////////////////////////////////////////////////////////////////
}
