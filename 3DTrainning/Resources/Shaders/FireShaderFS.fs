precision mediump float;
varying vec4 v_color;varying vec2 v_uv;
uniform sampler2D u_displacementtexture;
uniform sampler2D u_firetexture;
uniform sampler2D u_firemasktexture;

uniform float u_time;

const float dMax = 0.1;
void main()
{
    vec2 disp = texture2D(u_displacementtexture, vec2(v_uv.x, v_uv.y + u_time)).rg;
	vec2 offset = (2.0 * disp - 1.0) * dMax;
	vec2 uv_displaced = v_uv + offset;
	vec4 fire_color = texture2D (u_firetexture, uv_displaced);
	vec4 AlphaValue = texture2D(u_firemasktexture, v_uv);
	gl_FragColor = fire_color * (1.0, 1.0, 1.0, AlphaValue.r);
}
