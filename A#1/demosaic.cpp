#include "demosaic.h"

bool check_exist(int index, int bottom, int top);

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  int size = width * height;
  std::vector<unsigned char> r_matrix, g_matrix, b_matrix;
  r_matrix.resize(size);
  g_matrix.resize(size);
  b_matrix.resize(size);

  // G - B - R - G
  // step 1. we divide the input matrix into 3 sub-matrix
  for (int i = 0; i < height; ++i) {
	  // for even row
	  if (i % 2 == 0) {
		  for (int j = 0; j < width; ++j) {
			  int offset = width * i + j;
			  // for even col ---> G
			  if (j % 2 == 0) {
				  g_matrix[offset] = bayer[offset];
			  }
			  // for odd col ---> B
			  else {
				  b_matrix[offset] = bayer[offset];
			  }
		  }
	  }
	  // for odd row
	  else {
		  for (int j = 0; j < width; ++j) {
			  int offset = width * i + j;
			  // for even col ---> R
			  if (j % 2 == 0) {
				  r_matrix[offset] = bayer[offset];
			  }
			  // for odd col ---> G
			  else {
				  g_matrix[offset] = bayer[offset];
			  }
		  }
	  }
  }

  // step 2. we calculate the r_matrix to fill the blank cell.
  for (int r = 0; r < size; ++r) {
	  int total = 0;
	  unsigned char sum = 0;
	  
	  if (r_matrix[r] == 0) {
		  // check all 8 directions!!!
		  if (check_exist(r - width - 1, 0, size) && (r_matrix[r - width - 1] != 0)) {
			  total++;
			  sum += r_matrix[r - width - 1];
		  }  // 2
		  if (check_exist(r - width, 0, size) && (r_matrix[r - width] != 0)) {
			  total++;
			  sum += r_matrix[r - width];
		  }  // 3
		  if (check_exist(r - width + 1, 0, size) && (r_matrix[r - width + 1] != 0)) {
			  total++;
			  sum += r_matrix[r - width + 1];
		  }   // 4
		  if (check_exist(r - 1, 0, size) && (r_matrix[r - 1] != 0)) {
			  total++;
			  sum += r_matrix[r - 1];
		  }   // 5
		  if (check_exist(r, 0, size) && (r_matrix[r] != 0)) {
			  total++;
			  sum += r_matrix[r];
		  }  // 6
		  if (check_exist(r + 1, 0, size) && (r_matrix[r + 1] != 0)) {
			  total++;
			  sum += r_matrix[r + 1];
		  }  // 7
		  if (check_exist(r + width - 1, 0, size) && (r_matrix[r + width - 1] != 0)) {
			  total++;
			  sum += r_matrix[r + width - 1];
		  }  // 8
		  if (check_exist(r + width + 1, 0, size) && (r_matrix[r + width + 1] != 0)) {
			  total++;
			  sum += r_matrix[r + width + 1];
		  }

		  if (total == 0) {
			  total = 1;
		  }
		  else {
			  r_matrix[r] = sum / total;
		  }
	  }

  }

  // step 3. calculate the g_matrix to fill the blank cell.
  for (int g = 0; g < size; ++g) {
	  int total = 0;
	  unsigned char sum = 0;
	  if (g_matrix[g] == 0) {
		  // check all 8 directions!!!
		  if (check_exist(g - width - 1, 0, size) && (g_matrix[g - width - 1] != 0)) {
			  total++;
			  sum += g_matrix[g - width - 1];
		  }  // 2
		  if (check_exist(g - width, 0, size) && (g_matrix[g - width] != 0)) {
			  total++;
			  sum += g_matrix[g - width];
		  }  // 3
		  if (check_exist(g - width + 1, 0, size) && (g_matrix[g - width + 1] != 0)) {
			  total++;
			  sum += g_matrix[g - width + 1];
		  }   // 4
		  if (check_exist(g - 1, 0, size) && (g_matrix[g - 1] != 0)) {
			  total++;
			  sum += g_matrix[g - 1];
		  }   // 5
		  if (check_exist(g, 0, size) && (g_matrix[g] != 0)) {
			  total++;
			  sum += g_matrix[g];
		  }  // 6
		  if (check_exist(g + 1, 0, size) && (g_matrix[g + 1] != 0)) {
			  total++;
			  sum += g_matrix[g + 1];
		  }  // 7
		  if (check_exist(g + width - 1, 0, size) && (g_matrix[g + width - 1] != 0)) {
			  total++;
			  sum += g_matrix[g + width - 1];
		  }  // 8
		  if (check_exist(g + width + 1, 0, size) && (g_matrix[g + width + 1] != 0)) {
			  total++;
			  sum += g_matrix[g + width + 1];
		  }

		  if (total == 0) {
			  total = 1;
		  }
		  else {
			  g_matrix[g] = sum / total;
		  }
	  }
  }

  // step 4. calculate the b_matrix to fill the blank cell.
  for (int b = 0; b < size; ++b) {
	  int total = 0;
	  unsigned char sum = 0;
	  if (b_matrix[b] == 0) {
		  // check all 8 directions!!!
		  if (check_exist(b - width - 1, 0, size) && (b_matrix[b - width - 1] != 0)) {
			  total++;
			  sum += b_matrix[b - width - 1];
		  }  // 2
		  if (check_exist(b - width, 0, size) && (b_matrix[b - width] != 0)) {
			  total++;
			  sum += b_matrix[b - width];
		  }  // 3
		  if (check_exist(b - width + 1, 0, size) && (b_matrix[b - width + 1] != 0)) {
			  total++;
			  sum += b_matrix[b - width + 1];
		  }   // 4
		  if (check_exist(b - 1, 0, size) && (b_matrix[b - 1] != 0)) {
			  total++;
			  sum += b_matrix[b - 1];
		  }   // 5
		  if (check_exist(b, 0, size) && (b_matrix[b] != 0)) {
			  total++;
			  sum += b_matrix[b];
		  }  // 6
		  if (check_exist(b + 1, 0, size) && (b_matrix[b + 1] != 0)) {
			  total++;
			  sum += b_matrix[b + 1];
		  }  // 7
		  if (check_exist(b + width - 1, 0, size) && (b_matrix[b + width - 1] != 0)) {
			  total++;
			  sum += b_matrix[b + width - 1];
		  }  // 8
		  if (check_exist(b + width + 1, 0, size) && (b_matrix[b + width + 1] != 0)) {
			  total++;
			  sum += b_matrix[b + width + 1];
		  }

		  if (total == 0) {
			  total = 1;
		  }
		  else {
			  b_matrix[b] = sum / total;
		  }
	  }
  }

  // step 5. finally, we compose the 3 sub-matrix to one.
  for (int i = 0; i < width * height * 3; i+=3) {
	  rgb[i] = r_matrix[i/3];
	  rgb[i + 1] = g_matrix[i/3];
	  rgb[i + 2] = b_matrix[i/3];
  }
  

  ////////////////////////////////////////////////////////////////////////////
}


// helper functions
bool check_exist(int index, int bottom, int top) {
	return (index >= bottom) && (index < top);
}
