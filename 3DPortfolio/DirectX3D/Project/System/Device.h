#pragma once
class Device : public Singleton<Device>
{
	friend class Singleton;
private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();

public:
	void Clear();
	void Present();
	
	ID3D11Device*        GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }
private:
	ID3D11Device*           device;         // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü 
    ID3D11DeviceContext*    deviceContext;  // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü(RENDER, HDC)

    IDXGISwapChain*         swapChain;         // �������۸��� �����ϴ� ��ü
    ID3D11RenderTargetView* renderTargetView;  // ����۸� �����ϴ� ��ü
	ID3D11DepthStencilView* depthStencilView;

};
