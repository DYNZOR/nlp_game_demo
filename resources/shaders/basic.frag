#version 430

struct MaterialProperties
{
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;


struct LightProperties
{
	vec3 Position;

	float constant;
	float linear;
	float quadratic; 

	vec3 La; 
	vec3 Ld; 
	vec3 Ls; 
};

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPosition;


uniform vec3 viewPosition; 
uniform LightProperties light;
uniform MaterialProperties material;

out vec4 fragColour;

vec3 AmbientDiffuseSpecular(LightProperties lightIn, MaterialProperties materialIn, vec3 normalIn, vec3 fragPosIn, vec3 viewDirectionIn); 
//vec3 Cartoon();

void main() {
    //fragColour = vec4(0.0, 0.3, 0.0, 1.0);

	vec3 viewDirection = normalize(viewPosition - FragPosition);

	vec3 norm = normalize(Normal);

	vec3 result = AmbientDiffuseSpecular(light, material, norm, FragPosition, viewDirection);

	fragColour = vec4(result, 1.0f);

}

vec3 AmbientDiffuseSpecular(LightProperties lightIn, MaterialProperties materialIn, vec3 normalIn, vec3 fragPosIn, vec3 viewDirectionIn)
{
	// Calculate light direction vector
	vec3 lightDirection = normalize(lightIn.Position - fragPosIn);

	// Calculate diffuse value 
	float diffuse = max(dot(normalIn, lightDirection), 0.0);

	// Calculate specular value 
	vec3 reflectDirection = reflect(-lightDirection, normalIn);
	float specular = pow(max(dot(viewDirectionIn, reflectDirection), 0.0), materialIn.Shininess);

	// Calculate light attenuation 
	float distance = length(lightIn.Position - fragPosIn);
	float attenuation = 1.0f / (lightIn.constant + lightIn.linear * distance + lightIn.quadratic * (distance * distance));

	// Combine values
	vec3 ambientComponent = lightIn.La * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuseComponent = lightIn.Ld * vec3(texture(texture_diffuse1, TexCoords)) * diffuse;
	vec3 specularComponent = lightIn.Ls * vec3(texture(texture_specular1, TexCoords)) * specular;

	ambientComponent *= attenuation;
	diffuseComponent *= attenuation;
	specularComponent *= attenuation;

	return (ambientComponent + diffuseComponent + specularComponent);
}
