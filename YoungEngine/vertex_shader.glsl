#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform vec2 uPosition;
uniform vec2 uSize;
uniform vec2 uTexOffset;
uniform vec2 uTexScale;

out vec2 TexCoord;

void main() {
    vec2 scaledPos = aPos * uSize + uPosition;
    gl_Position = vec4(scaledPos * 2.0 - 1.0, 0.0, 1.0); // NDC로 변환
    TexCoord = (aTexCoord) * uTexScale + uTexOffset;
}