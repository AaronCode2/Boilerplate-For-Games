#version 420 core

// didn't write this, burrowed from raylib, it not that great

in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec2 screenSize;

out vec4 outputColor;

float offset[3] = float[](0.0, 1.3846153846, 3.2307692308);
float weight[3] = float[](0.2270270270, 0.3162162162, 0.0702702703);

void main() {

    vec3 texelColor = texture(texture0, fragTexCoord).rgb * weight[0];

    for (int i = 1; i < 3; i++){

        texelColor += texture(texture0, fragTexCoord + vec2(offset[i]/screenSize.x, 0.0), 0.0).rgb * weight[i];
        texelColor += texture(texture0, fragTexCoord - vec2(offset[i]/screenSize.x, 0.0), 0.0).rgb * weight[i];
    }

    outputColor = vec4(texelColor, 1.0);
}