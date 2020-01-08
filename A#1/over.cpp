#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  
  int size = width * height * 4;
  unsigned char c0_r, c0_g, c0_b, ca_r, ca_g, ca_b, cb_r, cb_g, cb_b;

  for (int i = 0; i < height; ++i) {
	  for (int j = 0; j < width; ++j) {

		  int offset = 4 * (width * i + j);
		  double alpha_a = (double)A[offset + 3] / 255;
		  double alpha_b = (double)B[offset + 3] / 255;
		  double alpha_0 = alpha_a + alpha_b * (1 - alpha_a);
		  if (alpha_0 == 0) {
			  c0_r = ca_r; c0_g = ca_g; c0_b = ca_b;
		  }

		  else {
			  ca_r = A[offset]; ca_g = A[offset + 1]; ca_b = A[offset + 2];
			  cb_r = B[offset]; cb_g = B[offset + 1]; cb_b = B[offset + 2];

			  // calculate the result Co by the online formula
			  c0_r = (ca_r * alpha_a + cb_r * alpha_b * (1 - alpha_a)) / alpha_0;
			  c0_g = (ca_g * alpha_a + cb_g * alpha_b * (1 - alpha_a)) / alpha_0;
			  c0_b = (ca_b * alpha_a + cb_b * alpha_b * (1 - alpha_a)) / alpha_0;
		  }

		  // get the output C
		  C[offset] = (unsigned char)c0_r;
		  C[offset + 1] = (unsigned char)c0_g;
		  C[offset + 2] = (unsigned char)c0_b;
		  C[offset + 3] = (unsigned char)(alpha_0 * 255);
	  }
  }

  ////////////////////////////////////////////////////////////////////////////
}
