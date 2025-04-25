#version 330

in vec2 texCoord;

out vec4 fragColor;

uniform usampler2D buf;
uniform vec2 texelSize;

const vec3 BG_COLOR = vec3(0.18);
const vec3 SAND_COLOR = vec3(0.9, 0.85, 0.15);
const vec3 WATER_COLOR = vec3(.28, .56, .8);
const float WATER_OPACITY = 0.6;
const vec3 SMOKE_COLOR = vec3(0.6);
const float SMOKE_OPACITY = 0.8;


// https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
float rand(vec2 n) { 
	return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
	vec2 ip = floor(p);
	vec2 u = fract(p);
	u = u*u*(3.0-2.0*u);
	
	float res = mix(
		mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
		mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
	return res*res;
}

float scaled_noise(vec2 sample, float minimum, float maximum) {
  return noise(sample) * (maximum - minimum) + minimum;
}

bool close_to(float val, float target) {
  return val < target + 2e-3 && val > target - 2e-3;
}

void main() {
  uint SAND = 0x2u;
  uint WALL = 0x1u;
  uint data = texture(buf, texCoord).r;
  vec3 color = BG_COLOR * scaled_noise(floor(texCoord * 65), 0.96, 1);
  switch (data & 0xffu) {
    case 0x2u:
      color = SAND_COLOR * scaled_noise(floor(texCoord * 65), 0.9, 1);
      break;
    case 0x1u:
      color = vec3(0.5, 0.5, 0.5);
      break;
    case 0x3u:
      color = mix(WATER_COLOR, color, WATER_OPACITY);
      break;
    case 0x4u:
      color = mix(SMOKE_COLOR * scaled_noise(floor(texCoord * 65), 0.8, 1), color, SMOKE_OPACITY);
      break;
  }
  // if (close_to(mod(texCoord.x, texelSize.x), 0) || close_to(mod(texCoord.y, texelSize.y), 0))
  //   fragColor = vec4(1, 0, 0, 1);
  // else
    fragColor = vec4(color, 1);
  // fragColor = vec4(vec3(float(data) / 4), 1);
}