#pragma once
class ConstBuffer
{
public:
	ConstBuffer(void* data, UINT dataSize);
	virtual ~ConstBuffer();

	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);
	void SetCSBuffer(UINT slot);
	void SetHSBuffer(UINT slot);
	void SetDSBuffer(UINT slot);

	void UpdateSubResource();

protected:
	void* data;
	UINT dataSize;

	ID3D11Buffer* constBuffer;

	D3D11_MAPPED_SUBRESOURCE subResource;
};



