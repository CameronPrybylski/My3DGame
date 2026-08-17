#version 410 core

layout(location = 0) out vec4 FragColor;
//out vec4 FragColor;
in vec2 v_TexCoord;
in vec3 v_NormCoord;
in vec3 v_FragPos;
//in vec4 v_ColorCoord;

uniform vec4 u_Color;
uniform vec3 u_LightPos;
uniform sampler2D u_Texture;

void main()
{
   //vec2 textCoord = v_TexCoord.xy;
   vec4 texColor = texture(u_Texture, v_TexCoord);
   vec4 BaseColor;
   //FragColor = u_Color;// * texColor;
   if(u_Color.w == 0.0f)
   {
      BaseColor = texColor;
   }else{
      BaseColor = u_Color * texColor;
   }
   if(v_NormCoord.x == 1.0f && v_NormCoord.y == 1.0f && v_NormCoord.z == 1.0f)
   {
      FragColor = BaseColor;
   }else {
      // 2. Normalize Inputs
      // Interpolation alters vector lengths, so re-normalizing is mandatory.
      vec3 norm = normalize(v_NormCoord);
      //vec3 LightPos = vec3(0.0f, 0.0f, 0.0f);
      vec3 lightDir = normalize(u_LightPos - v_FragPos);

      // 3. Diffuse Component
      // The dot product calculates the angle between the light and the surface normal.
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 LightColor = vec3(1.0f,1.0f,1.0f);
      vec3 diffuse = diff * LightColor;

      // 4. Combine Components
      // Add ambient light so shadows are not completely pitch black.
      vec3 AmbientColor = vec3(0.4f,0.4f,0.4f);
      vec3 lighting = AmbientColor + diffuse;

      // 5. Final Output
      // Apply the lighting calculations directly to the RGB channels of your base color.
      FragColor = vec4(BaseColor.rgb * lighting, BaseColor.a);
   }
   
}