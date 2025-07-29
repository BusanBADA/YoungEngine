#version 330 core
layout (location = 0) in vec2 aPos;

uniform vec2 uPosition;
uniform vec2 uSize;

void main()
{
    vec2 pos = aPos * uSize + uPosition;
    pos.y = 1.0 - pos.y;

    gl_Position = vec4(pos * 2.0 - 1.0, 0.0, 1.0);
}