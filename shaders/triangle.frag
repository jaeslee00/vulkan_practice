#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 worldPos;

layout(location = 0) out vec4 outColor;

void main() {
    // const vec3 light = vec3(2.0);
    // vec3 north = (ubo.model * vec4(0, -1, 0, 0)).xyz;
    // vec3 right = (ubo.model * vec4(1, 0, 0, 0)).xyz;
    // vec3 spherePos = normalize(worldPos - vec3(0));
    // float latitude = acos(dot(spherePos, north));
    // vec3  vertical = normalize(spherePos - north * dot(spherePos, north));
    // float longitude = acos(dot(vertical, right));
    // const float PI = 3.14159265358;
    // outColor = vec4(latitude / PI, longitude / PI, 0, 1.0);
    outColor = vec4(fragColor, 1.0f);
//    outColor = texture(texSampler, fragTexCoord);
}
