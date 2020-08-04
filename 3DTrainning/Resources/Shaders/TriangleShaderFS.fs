precision mediump float;
varying vec4 v_color;varying vec2 v_uv;varying float v_fogDepth;
uniform sampler2D u_texture;
uniform vec4 u_fogColor;
uniform float u_fogNear;
uniform float u_fogFar;

void main()
{
    vec4 color = texture2D(u_texture, v_uv);
	float fogAmount = smoothstep(u_fogNear, u_fogFar, v_fogDepth);
	gl_FragColor = mix(color, u_fogColor, fogAmount);
	//gl_FragColor = texture2D(u_texture, v_uv);
}
