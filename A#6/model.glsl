// Construct the model transformation matrix. The moon should orbit around the
// origin. The other object should stay still.
//
// Inputs:
//   is_moon  whether we're considering the moon
//   time  seconds on animation clock
// Returns affine model transformation as 4x4 matrix
//
// expects: identity, rotate_about_y, translate, PI
mat4 model(bool is_moon, float time)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code 
  
  // when do not considering moon
  if(!is_moon){
    // shold stay still
    return identity();
  }else{
    // when considering moon
    float theta = time * 0.5 * M_PI;
    return rotate_about_y(theta) * translate(vec3(2.0, 0.0, 0.0)) * uniform_scale(0.3);
  }

  /////////////////////////////////////////////////////////////////////////////
}
