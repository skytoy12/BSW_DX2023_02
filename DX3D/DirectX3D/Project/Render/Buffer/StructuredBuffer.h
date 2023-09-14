#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount, UINT outputStride, UINT outputCount);
	~StructuredBuffer();

	void Copy(void* data, UINT size);

	ID3D11UnorderedAccessView* GetUAV() { return uav; }
	ID3D11ShaderResourceView*  GetSRV() { return srv; }
private:
	void Createinput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV();
	void CreateResult();

private:
	ID3D11UnorderedAccessView* uav; // 읽기 쓰기가 둘다 가능하지만 병렬구조 특성상 읽기는 효율이 떨어지므로 사실상 쓰기용으로 사용
	ID3D11ShaderResourceView*  srv; // CPU가 데이터를 GPU에 넘기고 GPU가 데이터를 읽어야 하므로 읽기용인 srv를 사용

	ID3D11Resource* input;
	ID3D11Resource* output;
	ID3D11Resource* result;

	void* inputData;
	UINT inputStride;
	UINT inputCount;

	UINT outputStride;
	UINT outputCount;
};

