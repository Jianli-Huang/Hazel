#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_EntityID;

uniform mat4 u_ViewProjection;

out vec4 v_Color;
out vec2 v_Texcoord;
flat out int v_EntityID;

void main()
{
	v_Color = a_Color;
	v_Texcoord = a_TexCoord;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;
layout(location = 1) out int color2;

uniform sampler2D u_FontAtlas;

in vec4 v_Color;
in vec2 v_Texcoord;
flat in int v_EntityID;

float screenPxRange() {
	float pxRange = 2.0; // set to distance field's pixel range
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(u_FontAtlas, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(v_Texcoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}


void main()
{
	vec4 texColor = texture(u_FontAtlas, v_Texcoord) * v_Color;

	vec3 msd = texture(u_FontAtlas, v_Texcoord).rgb;
	float sd = median(msd.r, msd.g, msd.b);
	float screenPxDistance = screenPxRange() * (sd - 0.5);
	float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
	if(opacity == 0.0)
		discard;

	vec4 bgColor = vec4(0.0);
	color = mix(bgColor, v_Color, opacity);	
	if(color.a == 0.0)
		discard;
	
	color2 = v_EntityID;	//vec4(0.9, 0.2, 0.3, 1.0);
}