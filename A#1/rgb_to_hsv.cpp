#include "rgb_to_hsv.h"
#include<cmath>
#include<algorithm>
void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
	// step 1. compare the value of r,g,b and get a max and a min
	double max = b > (r > g ? r : g) ? b : (r > g ? r : g);
	double min = b < (r < g ? r : g) ? b : (r < g ? r : g);
	double diff = max - min;

	// calculate h
	if (max == min) {
		h = 0;
	}
	else if (max == r) {
		h = 60 * ((g - b) / diff);
	}
	else if (max == g) {
		h = 60 * (2 + (b - r) / diff);
	}
	else if (max == b) {
		h = 60 * (4 + (r - g) / diff);
	}

	if (h < 0) {
		h += 360;
	}
	else if (h >= 360) {
		h -= 360;
	}

	// calculate s
	if (max == 0) {
		s = 0;
	}
	else {
		s = fabs(diff / max);
	}

	// calculate v
	v = max;

  ////////////////////////////////////////////////////////////////////////////
}
