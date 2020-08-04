precision mediump float;
varying float v_fogDepth;
varying vec3 v_pos;

uniform samplerCube u_samplerCubeMap;
uniform vec4 u_fogColor;
uniform float u_fogNear;
uniform float u_fogFar;


void main()
{
      vec4 color = textureCube(u_samplerCubeMap, v_pos);
	  float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
	  gl_FragColor = mix(color, u_fogColor, fogAmount);
      //gl_FragColor = textureCube(u_samplerCubeMap, v_pos);
}
