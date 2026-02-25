#version 460

uniform vec2 texelSize;

layout(location = 0)in vec4 point;

out vec2 texCoord;

void main() {
  texCoord = point.zw;
  texCoord *= 1 - 2 * texelSize;
  texCoord += texelSize * 2;
  gl_Position = vec4(point.xy, 0, 1);
}
