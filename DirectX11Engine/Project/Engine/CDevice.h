#pragma once

class CDevice
{
private:
	HWND m_hMainWnd; // 출력대상 윈도우
	POINT m_RenderResolution; // 랜더링 타겟의 해상도

	ComPtr<ID3D11Device> m_Device; // GPU 메모리 할당, Dx11 관련 객체 생성
	ComPtr<ID3D11DeviceContext> m_Context; // GPU 렌더링 관련 명령

	ComPtr<IDXGISwapChain> m_SwapChain; // 렌더타겟 버퍼 소유, 화면에 최종 장면을 게시

	ComPtr<ID3D11Texture2D> m_RenderTargetTex;
	ComPtr<ID3D11RenderTargetView> m_RTV;

	ComPtr<ID3D11Texture2D> m_DepthStencilTex;
	ComPtr<ID3D11DepthStencilView> m_DSV;

public:
	static CDevice* GetInst()
	{
		static CDevice mgr;
		return &mgr;
	}

public:
	int init(HWND _hWnd, POINT _Resolution);
	void ClearTarget(float(&_ArrColor)[4]);
	void Present() { m_SwapChain->Present(0, 0); }

private:
	int CreateSwapchain();
	int CreateView();

private:
	CDevice();
	CDevice(const CDevice& _other) = delete;

public:
	~CDevice();
};

