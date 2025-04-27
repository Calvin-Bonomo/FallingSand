#version 430

uniform vec2 texelSize;

in vec2 pos;

out vec2 texCoord;

void main() {
  texCoord = (pos + 1) * 0.5;
  texCoord *= 1 - 2 * texelSize;
  texCoord += texelSize;
  gl_Position = vec4(pos, 0, 1);
}