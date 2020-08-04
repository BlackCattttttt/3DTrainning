precision mediump float;

uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
uniform vec4 u_fogColor;
uniform float u_fogNear;
uniform float u_fogFar;

varying vec2 v_uv;
varying float v_fogDepth;

void main()
{
	vec4 blend_color = texture2D(u_texture0,v_uv);
	vec4 color = (texture2D(u_texture1,v_uv)*blend_color.r + texture2D(u_texture2,v_uv)*blend_color.g + texture2D(u_texture3,v_uv)*blend_color.b) / (blend_color.r+blend_color.g+blend_color.b) ;
	float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
	gl_FragColor = mix(color, u_fogColor, fogAmount);
}
