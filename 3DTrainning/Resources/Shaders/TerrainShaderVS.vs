
attribute vec3 a_posL;
attribute vec2 a_uv;

uniform mat4 u_WVP;
uniform mat4 u_W;
uniform mat4 u_V;

varying vec2 v_uv;
varying float v_fogDepth;

void main()
{
    vec4 posL = vec4(a_posL, 1.0);
	vec4 worldPos=u_W*posL;
    vec4 distanceToCam=u_V*worldPos;
    gl_Position = u_WVP * posL ;
	v_fogDepth = -distanceToCam.z;
    v_uv = a_uv;
}
   