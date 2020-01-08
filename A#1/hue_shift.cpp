#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here

  // step 1. convert the rgb-format image to hsv-format image.
 //  rgb_to_hsv(r,g,b,h,s,v);

  int size = rgb.size();

  double h, s, v, r, g, b;
  for (auto i = 0; i < size; i+=3) {
	  rgb_to_hsv((double)rgb[i], (double)rgb[i + 1], (double)rgb[i + 2], h, s, v);
	  h += shift;

	  if (h >= 360) {
		  h -= 360;
	  }
	  else if (h < 0) {
		  h += 360;
	  }

	  hsv_to_rgb(h, s, v, r, g, b);
	  shifted[i] = r;
	  shifted[i + 1] = g;
	  shifted[i + 2] = b;
  }

  ////////////////////////////////////////////////////////////////////////////
}
