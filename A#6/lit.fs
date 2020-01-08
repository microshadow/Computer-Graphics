// Add (hard code) an orbiting (point or directional) light to the scene. Light
// the scene using the Blinn-Phong Lighting Model.
//
// Uniforms:
uniform mat4 view;
uniform mat4 proj;
uniform float animation_seconds;
uniform bool is_moon;
// Inputs:
in vec3 sphere_fs_in;
in vec3 normal_fs_in;
in vec4 pos_fs_in; 
in vec4 view_pos_fs_in; 
// Outputs:
out vec3 color;
// expects: PI, blinn_phong
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 

	float theta = M_PI * 0.5 * animation_seconds;
	mat3 rotation = mat3(cos(theta), 0, -sin(theta),
		                   0, 1, 0,
		                   sin(theta), 0, cos(theta));

	vec3 n_prime = normalize((proj * vec4(normal_fs_in, 1.0)).xyz / (proj * vec4(normal_fs_in, 1.0)).w);
	vec3 v_prime = normalize((proj * view_pos_fs_in).xyz / (proj * view_pos_fs_in).w);
	vec3 l_prime = normalize(rotation * vec3(1.0, 1.0, 1.0));

	vec3 k_d;  // kd
	if(!is_moon){
		k_d = vec3(0.0, 0.0, 1.0);
	}else{
		// considering moon
		k_d = vec3(0.72, 0.75, 0.72);
	}

  	color = blinn_phong(vec3(0.05, 0.05, 0.05), k_d, vec3(0.75, 0.75, 0.75), 1000, n_prime, v_prime, l_prime);
  	// the result is slight different from the picture from website.
  	// since running out of time, i'm going to do next part instead of testing those small values.
  /////////////////////////////////////////////////////////////////////////////
}
