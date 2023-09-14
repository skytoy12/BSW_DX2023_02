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
	ID3D11UnorderedAccessView* uav; // �б� ���Ⱑ �Ѵ� ���������� ���ı��� Ư���� �б�� ȿ���� �������Ƿ� ��ǻ� ��������� ���
	ID3D11ShaderResourceView*  srv; // CPU�� �����͸� GPU�� �ѱ�� GPU�� �����͸� �о�� �ϹǷ� �б���� srv�� ���

	ID3D11Resource* input;
	ID3D11Resource* output;
	ID3D11Resource* result;

	void* inputData;
	UINT inputStride;
	UINT inputCount;

	UINT outputStride;
	UINT outputCount;
};

