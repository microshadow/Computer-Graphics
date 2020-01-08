// Given a 3d position as a seed, compute a smooth procedural noise
// value: "Perlin Noise", also known as "Gradient noise".
//
// Inputs:
//   st  3D seed
// Returns a smooth value between (-1,1)
//
// expects: random_direction, smooth_step
float perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

	int x_ = int(floor(st.x));
	int y_ = int(floor(st.y));
	int z_ = int(floor(st.z));
	float noise = 0.0;

	for (int i = x_; i < x_ + 2; ++i)
	{
		for (int j = y_; i < y_ + 2; ++j)
		{
			for (int k = z_; i < z_ + 2; ++k)
			{
				vec3 offset = st - vec3(i, j, k);
				vec3 w = smooth_step(1 - abs(offset));
				vec3 d = random_direction(vec3(i, j, k));

				noise += w.x * w.y * w.z * dot(d, normalize(offset));
			}
		}
	}

	if(noise >= -1 && noise <= 1){
		return noise;
	}else{
		return 0;
	}

	//return noise;

  /////////////////////////////////////////////////////////////////////////////
}

