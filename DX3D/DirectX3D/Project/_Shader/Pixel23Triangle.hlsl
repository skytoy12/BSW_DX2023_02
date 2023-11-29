struct DomainOutput
{
    float4 pos : SV_POSITION;
};


float4 main(DomainOutput input) : SV_TARGET
{
	return float4(1.0f, 1.0f, 0.0f, 1.0f);
}