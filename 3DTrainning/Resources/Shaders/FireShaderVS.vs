attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec2 a_uv;

uniform mat4 u_WVP;
uniform mat4 u_W;
uniform mat4 u_V;

varying vec2 v_uv;

void main()
{
    vec4 posL = vec4(a_posL, 1.0);
    v_uv = a_uv;
    gl_Position = u_WVP * posL ;
}
   