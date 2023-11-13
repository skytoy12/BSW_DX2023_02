#include "Header.hlsli"



GBufferOutput main(LightVertexOutput input)
{
    LightMaterial material = GetLightMaterial(input);
    
    return PackBuffer(material.diffuseColor.rgb, material.normal, material.specularIntensity.r, CalculateAmbient(material));

}