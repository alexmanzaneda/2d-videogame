#version 330

in vec2 position;
uniform vec2 scale;

void main()
{
	vec2 pos = position * scale;
	gl_Position = vec4(pos, 0.0, 1.0);
}
