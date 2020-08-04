attribute vec3 a_posL;

varying float v_fogDepth;
varying vec3 v_pos;

uniform mat4 u_WVP;
uniform mat4 u_W;
uniform mat4 u_V;


void main()
{
    vec4 posL = vec4(a_posL, 1.0);
	vec4 worldPos=u_W*posL;
    vec4 distanceToCam=u_V*worldPos;
    gl_Position = u_WVP * posL ;
	v_fogDepth = -distanceToCam.z;
    v_pos = a_posL;
}
   