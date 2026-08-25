#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormCoord;

out vec2 v_TexCoord;
out vec3 v_NormCoord;
out vec3 v_FragPos;
//out vec4 v_ColorCoord;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
void main()
{
   // Transform position into world space
   v_FragPos = vec3(u_Model * vec4(aPos, 1.0));

   // Transform normal into world space
   mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
   v_NormCoord = normalMatrix * aNormCoord;

   v_TexCoord = aTexCoord;

   // Final clip-space position
   gl_Position =
      u_Projection *
      u_View *
      u_Model *
      vec4(aPos, 1.0);
}