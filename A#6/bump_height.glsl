// Create a bumpy surface by using procedural noise to generate a height (
// displacement in normal direction).
//
// Inputs:
//   is_moon  whether we're looking at the moon or centre planet
//   s  3D position of seed for noise generation
// Returns elevation adjust along normal (values between -0.1 and 0.1 are
//   reasonable.
float bump_height( bool is_moon, vec3 s)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

	float noise = 0;
	if(is_moon){
		noise = improved_perlin_noise(s + vec3(3.5, 4.5, -2.5));
	}else{
		noise = improved_perlin_noise(s + 0.45);
	}

  return noise / 5 ;
  /////////////////////////////////////////////////////////////////////////////
}
