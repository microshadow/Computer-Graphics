// Generate a procedural planet and orbiting moon. Use layers of (improved)
// Perlin noise to generate planetary features such as vegetation, gaseous
// clouds, mountains, valleys, ice caps, rivers, oceans. Don't forget about the
// moon. Use `animation_seconds` in your noise input to create (periodic)
// temporal effects.
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

	float theta = animation_seconds * 0.5 * M_PI;
    mat3 rotation = mat3(cos(theta),0,-sin(theta),
  	      				0,1,0,
  	      				sin(theta),0,cos(theta));
  
    vec3 l_prime = normalize(rotation * vec3(3.0, 1.0, 0.0));
  
    float factor = abs(max(mod(animation_seconds, 24) - 4, 0) / 10 - 1);
  
    float noise1 = improved_perlin_noise(sphere_fs_in * 2.4 + vec3(1.7));
    float noise2 = improved_perlin_noise(sphere_fs_in * 1.2 + vec3(0.4));

    vec3 noise_normal = nn(is_moon, (nn(is_moon, sphere_fs_in * 2.5)) * 0.8);
  
    vec3 normal_prime = (1 - 0.8 * pow(factor, 0.5)) * noise_normal + 0.8 * pow(factor, 0.5) * normal_fs_in;
  
    vec3 n_prime;

    vec3 v_prime = normalize((proj * view_pos_fs_in).xyz / (proj * view_pos_fs_in).w);
  
  
    vec3 k_d;
    vec3 k_s;
    if (is_moon){
      k_s = vec3(0.6);
      k_d = vec3(0.5);
      k_d = min(k_d, abs(k_d - min(noise2,0.8)));
  
      n_prime = normalize((proj * vec4(noise_normal, 1.0)).xyz / (proj * vec4(noise_normal, 1.0)).w);
    }else{
      k_s = vec3(0.6) * factor + vec3(0.2);
      k_d = (1 - factor) * vec3(0.8, 0.6, 0.3) + factor * vec3(0.3, 0.3, 1);
      k_d = min(vec3(1), abs(k_d + noise1 / 2));
  
      n_prime = normalize((proj * vec4(normal_prime, 1.0)).xyz / (proj * vec4(normal_prime, 1.0)).w);
    }
  
    
  
    color = blinn_phong(vec3(0.01), k_d, k_s, 100, n_prime, v_prime, l_prime);

  /////////////////////////////////////////////////////////////////////////////
}
