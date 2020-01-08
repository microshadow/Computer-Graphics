// Generate a pseudorandom unit 3D vector
// 
// Inputs:
//   seed  3D seed
// Returns psuedorandom, unit 3D vector drawn from uniform distribution over
// the unit sphere (assuming random2 is uniform over [0,1]²).
//
// expects: random2.glsl, PI.glsl
vec3 random_direction( vec3 seed)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

	//vec3 unit = vec3(1.0, 1.0, 1.0);

	// radiance --> r
	vec2 r = 2 * random2(seed) * M_PI;

	// direction --> d
	vec3 d = vec3(0.0, 0.0, 0.0);
	d.x = sin(r.x) * cos(r.y);
	d.y = sin(r.x) * sin(r.y);
	d.z = cos(r.x);

  	return d;
  /////////////////////////////////////////////////////////////////////////////
}
