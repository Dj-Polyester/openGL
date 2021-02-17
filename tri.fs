#version 460 core

in vec2 texCoord;
in vec3 vertexColor;
out vec4 fragColor;

uniform int bound;
uniform sampler2D textures[32];
uniform float weights[32];

void main()
{
    fragColor = vec4(0,0,0,0);
    for (int i=0; i<bound; ++i)
        fragColor += texture(textures[i],texCoord)*weights[i];
    // fragColor = texture(textures[1],texCoord);
    // fragColor = mix(texture(textures[0],texCoord),texture(textures[1],texCoord),1);
}