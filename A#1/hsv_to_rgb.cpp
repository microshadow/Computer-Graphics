#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

  // step 1. get chroma
	double chroma = v * s;

	// step 2.   get h_
	double h_ = h / 60;

	double x = chroma * (1 - fabs(fmod(h_, 2) - 1));
	double r1, g1, b1;

	// case 1:
	if (h_ >= 0 && h_ <= 1) {
		r1 = chroma; g1 = x; b1 = 0;
	}  // case 2:
	else if (h_ > 1 && h_ <= 2) {
		r1 = x; g1 = chroma; b1 = 0;
	}  // case 3:
	else if (h_ > 2 && h_ <= 3) {
		r1 = 0; g1 = chroma; b1 = x;
	}   // case 4:
	else if (h_ > 3 && h_ <= 4) {
		r1 = 0; g1 = x; b1 = chroma;
	}  // case 5:
	else if (h_ > 4 && h_ <= 5) {
		r1 = x; g1 = 0; b1 = chroma;
	}  // case 6:
	else if (h_ > 5 && h_ <= 6) {
		r1 = chroma; g1 = 0; b1 = x;
	}
	else {
		r1 = 0; g1 = 0; b1 = 0;
	}

	double m = v - chroma;

	r = r1 + m; 
	g = g1 + m;
	b = b1 + m;

  ////////////////////////////////////////////////////////////////////////////
}
