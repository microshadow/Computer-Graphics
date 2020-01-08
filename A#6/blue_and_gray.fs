// Set the pixel color to blue or gray depending on is_moon.
//
// Uniforms:
uniform bool is_moon;
// Outputs:
out vec3 color;
void main()
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code:
  // when do not considering moon
  if(is_moon){
    color = vec3(0.7,0.7,0.7);
  } else{
    color = vec3(0.0, 0.0, 1.0);
  }

  /////////////////////////////////////////////////////////////////////////////
}
