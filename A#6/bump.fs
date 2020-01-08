// Set the pixel color using Blinn-Phong shading (e.g., with constant blue and
// gray material color) with a bumpy texture.
// 
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
//                     linearly interpolated from tessellation evaluation shader
//                     output
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
//               rgb color of this pixel
out vec3 color;
// expects: model, blinn_phong, bump_height, bump_position,
// improved_perlin_noise, tangent

// declare new function
vec3 nn(bool is_moon, vec3 n){
	vec3 T;
	vec3 B;
  	tangent(sphere_fs_in, T, B);
  	float e = 0.0001;  // epsilon, it is very small

  	vec3 p = bump_position(is_moon, n);
  	vec3 pT = bump_position(is_moon, n + e * T);
  	vec3 pB = bump_position(is_moon, n + e * B);

  	return normalize(cross((pT - p) / e, (pB - p) / e));
}

void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  float theta = 0.5 * animation_seconds * M_PI;
  mat3 rotation = mat3(cos(theta), 0, -sin(theta),
	      				0, 1, 0,
	      				sin(theta), 0, cos(theta));

  vec3 l_prime = normalize(rotation * vec3(2, 0, 0));

  vec3 n_prime = nn(is_moon, (nn(is_moon, sphere_fs_in * 2.5)) / 2);

  vec3 v_prime = normalize((proj * view_pos_fs_in).xyz / (proj * view_pos_fs_in).w);


  vec3 k_d;
  if (is_moon){
    k_d = vec3(0.5, 0.5, 0.5);
  }else{
    k_d = vec3(0.0, 0.0, 1.0);
  }

  color = blinn_phong(vec3(0.01, 0.01, 0.01), k_d, vec3(0.75, 0.75, 0.75), 1000, n_prime, v_prime, l_prime);

  /////////////////////////////////////////////////////////////////////////////
}
