#version 420 core

// I didn't write this, burrowed somone's code

// steps to Bloom: 
// step 1. Thersold -> highlights
// step 2 -> Blur
// step 3 -> Layering

// Using what COD uses for bloom

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

out vec4 ouptColor;

void main() {

    float exposure = 1.0;
    float gamma = 2.2;

    vec3 hdrColor = texture(texture0, fragTexCoord).rgb;
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    mapped = pow(mapped, vec3(1.0 / gamma));

    ouptColor = vec4(mapped, 1.0);
}
