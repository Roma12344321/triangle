#version 330 core
in vec2 textCoords;

uniform sampler2D tex;

out vec4 frag_color;

void main() {
    vec4 c = texture(tex, textCoords);

    if (c.a < 0.1) {
        discard;
    }

    frag_color = c;
}