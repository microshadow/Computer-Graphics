// Given a 3d position as a seed, compute an even smoother procedural noise
// value. "Improving Noise" [Perlin 2002].
//
// Inputs:
//   st  3D seed
// Values between  -½ and ½ ?
//
// expects: random_direction, improved_smooth_step
float improved_perlin_noise( vec3 st) 
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

	vec3 directions[16] = vec3[16](vec3(1,1,0), vec3(-1,1,0), vec3(1,-1,0), vec3(-1,-1,0),
								vec3(1,0,1), vec3(-1,0,1), vec3(1,0,-1), vec3(-1,0,-1),
								vec3(0,1,1), vec3(0,-1,1), vec3(0,1,-1), vec3(0,-1,-1),
								vec3(1,1,0), vec3(-1,1,0), vec3(0,-1,1), vec3(0,-1,-1));

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
				vec3 w = improved_smooth_step(1 - abs(offset));
				vec3 d = random_direction(vec3(i, j, k));

				int p = int(mod(floor(dot(d, vec3(1.0, 0.0, 0.0)) * 16), 16));

				noise += w.x * w.y * w.z * dot(directions[p], normalize(offset));
			}
		}
	}

	if(noise >= -0.5 && noise <= 0.5){
		return noise;
	}else{
		return 0;
	}
  /////////////////////////////////////////////////////////////////////////////
}

