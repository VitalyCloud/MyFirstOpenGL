#version 330 core
layout (location = 0) in vec3 pos; //0 - is index in glVertexAttribPointer
layout (location = 1) in vec2 textureCoord;

uniform vec2 posOffset;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(pos.x + posOffset.x, pos.y + posOffset.y, pos.z, 1.0);
    TexCoord = textureCoord;
}
