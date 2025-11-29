#version 450 core

layout(location = 0) in vec4 vertex;

out vec2 vShapeUV;
out vec2 vTextUV;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 uResolution;

void main()
{
    vec4 clipCenter = projection * view * model * vec4(0.0, 0.0, 0.0, 1.0);
    vec4 clipVertex = projection * view * model * vec4(vertex.xy, 0.0, 1.0);

    vec2 offset = clipVertex.xy - clipCenter.xy;

    vec2 pixelSizeInClipSpace = (clipCenter.w * 2.0) / uResolution;
    vec2 minSize = pixelSizeInClipSpace * 0.5;

    if (abs(offset.x) < minSize.x) {
        offset.x = sign(offset.x) * minSize.x;
        if (offset.x == 0.0) offset.x = sign(vertex.x) * minSize.x;
    }

    if (abs(offset.y) < minSize.y) {
        offset.y = sign(offset.y) * minSize.y;
        if (offset.y == 0.0) offset.y = sign(vertex.y) * minSize.y;
    }

    vec2 normalized = offset / max(abs(offset.x), abs(offset.y));
    vShapeUV = normalized * 0.5 + 0.5;

    vTextUV = vertex.zw;

    gl_Position = vec4(clipCenter.xy + offset, clipCenter.z, clipCenter.w);
}
