#include "Framework.h"
#include "Material.h"

Material::Material()
{
	buffer = new MaterialBuffer();
}

Material::Material(wstring file)
{
	SetShader(file);

	buffer = new MaterialBuffer();
}

Material::~Material()
{
	delete buffer;
}

void Material::SetVertexShader(wstring file)
{
	vertexShader = Shader::GetVS(file);
}

void Material::SetPixelShader(wstring file)
{
	pixelShader = Shader::GetPS(file);
}

void Material::SetShader(wstring file)
{
	SetVertexShader(file);
	 SetPixelShader(file);
}

void Material::SetMaterial()
{
	vertexShader->SetShader();
	 pixelShader->SetShader();

	 if (diffuseMap)
		 diffuseMap->PSSetShaderResources(0);

	 if (specularMap)
		 specularMap->PSSetShaderResources(1);

	 buffer->SetPSBuffer(1);
}

void Material::SetDuffuseMap(wstring file)
{
	diffuseMap = Texture::Get(file);

	buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	specularMap = Texture::Get(file);

	buffer->data.hasSpecularMap = true;
}

void Material::PostRender()
{
	ImGui::ColorEdit4("Diffuse",  (float*)&buffer->data.diffuse);
	ImGui::ColorEdit4("Specular", (float*)&buffer->data.specular);
	ImGui::ColorEdit4("Ambient",  (float*)&buffer->data.ambient);

	ImGui::Checkbox("HasDiffuseMap",  (bool*)&buffer->data.hasDiffuseMap);
	ImGui::Checkbox("HasSpecularMap", (bool*)&buffer->data.hasSpecularMap);
	ImGui::Checkbox("HasNormalMap",   (bool*)&buffer->data.hasNormalMap);

	ImGui::SliderFloat("Shininess", &buffer->data.shininess, 1.0f, 50.0f);
}
