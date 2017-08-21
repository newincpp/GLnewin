#version 430 core

layout(location = 0) uniform float uTime;
layout(location = 1) uniform mat4 uMeshTransform;
layout(location = 2) uniform mat4 uView;

layout(location = 0) in vec3 vInfVertexPos_;
layout(location = 1) in vec3 vInfVertexNormal_;
layout(location = 2) in vec2 vInfUvCoord_;

out vec3 gPosition;
out vec3 gNormal;
out vec3 gAlbedoSpec;
//out float gDepth;
//uniform layout(binding=1, rgba16f) writeonly image2D uImageRam; // float
//uniform layout(binding=1, rgba16ui) writeonly uimage2D uImageRam; // int

uniform layout(binding=2, rgba8) restrict image3D cheapGI;

vec3 getCameraPos() {
    return inverse(uView)[3].xyz;
}

void main() {
    //if (gl_FragCoord.x > 500) {
    //    discard;
    //}
    // Store the fragment position vector in the first gbuffer texture
    gPosition = vInfVertexPos_;
    // Also store the per-fragment normals into the gbuffer
    gNormal = vInfVertexNormal_;
    // And the diffuse per-fragment color
    if (gPosition.y < 0.1) {
	gAlbedoSpec.rgb = vec3(0.4, 0.4, 0.4) * clamp((1 - floor(sin(gPosition.x * 5) + 0.01)) - (1 - floor(sin(gPosition.z * 5) + 0.01)), 0.0, 1.0);
    } else {
	gAlbedoSpec.rgb = vec3(0.4, 0.4, 0.4);
    }
    //gDepth = 1.0f;

    // Fake Global Illumination (inspired by unreal's LPV)
    vec3 giBufferCenter = getCameraPos() - vec3(imageSize(cheapGI)) / 2.0f;
    const float texelToWorldUnitscaling = 8;
    ivec3 coord = ivec3(distance(giBufferCenter, vInfVertexPos_) / texelToWorldUnitscaling);
    //vec4 currentColour = imageLoad(cheapGI, coord);
    //if(currentColour.a > 0.5f) { // using alpha as a bool for "first set"
    //    imageStore(cheapGI, coord, vec4(currentColour.rgb * gAlbedoSpec.rgb, 1.0));
    //} else {
    //    imageStore(cheapGI, coord, vec4(gAlbedoSpec.rgb, 1.0));
    //}
    imageStore(cheapGI, coord, vec4(gAlbedoSpec.rgb, 1.0));
}
