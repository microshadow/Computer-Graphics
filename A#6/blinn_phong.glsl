// Compute Blinn-Phong Shading given a material specification, a point on a
// surface and a light direction. Assume the light is white and has a low
// ambient intensity.
//
// Inputs:
//   ka  rgb ambient color
//   kd  rgb diffuse color
//   ks  rgb specular color
//   p  specular exponent (shininess)
//   n  unit surface normal direction
//   v  unit direction from point on object to eye
//   l  unit light direction
// Returns rgb color
vec3 blinn_phong(
  vec3 ka,
  vec3 kd,
  vec3 ks,
  float p,
  vec3 n,
  vec3 v,
  vec3 l)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

  // l' 
  vec3 l_prime = vec3(1.0, 1.0, 1.0); // because we assume the light is white color
  vec3 h = normalize(normalize(v) + normalize(l));

  return ka * l_prime + kd * l_prime * max(dot(n, l), 0.0) + ks * l_prime * pow(max(dot(n, h), 0.0), p);
  // note: 0.0 is safer than 0..
  /////////////////////////////////////////////////////////////////////////////
}


