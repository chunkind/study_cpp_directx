#include "pch.h"
#include "CDevice.h"

CDevice::CDevice()
	: m_hMainWnd(nullptr)
	, m_RenderResolution{}
	, m_Device(nullptr)
	, m_Context(nullptr)
	, m_SwapChain(nullptr)
	, m_RenderTargetTex(nullptr)
	, m_RTV(nullptr)
	, m_DepthStencilTex(nullptr)
	, m_DSV(nullptr)
{

}

CDevice::~CDevice()
{
	m_Device->Release();
	m_Context->Release();
	//new
	m_SwapChain->Release();
}

int CDevice::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainWnd = _hWnd;
	m_RenderResolution = _Resolution;

	UINT iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION
		, &m_Device, &level, &m_Context);

	//new
	// SwapChain 생성
	if (FAILED(CreateSwapchain()))
	{
		return E_FAIL;
	}

	return S_OK;
}

//new
int CDevice::CreateSwapchain()
{
	// 스왑 체인 방식
	// 1. 비트 블록 전송 모델 :: 데이터를 복사하여 전송 (프레임제한이 없다)
	// DXGI_SWAP_EFFECT_DISCARD -> 화면 출력하고 버퍼에있는 내용 버린다.
	// DXGI_SWAP_EFFECT_SEQUENTIAL

	// 2. 대칭 이동 프레젠테이션 모델 :: 버퍼가2개 필요한다 복사가 아니라 포인터를 전달 (프레임이 고정된다)
	// DXGI_SWAP_EFFECT_FLIP_DISCARD  -> 화면 출력하고 버퍼에있는 내용 버린다.
	// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL

	DXGI_SWAP_CHAIN_DESC Desc = {};

	// SwapChain 이 화면을 게시(Present) 할때 출력 목적지 윈도우
	Desc.OutputWindow = m_hMainWnd;
	Desc.Windowed = true;

	// SwapChain 이 만들어질때 버퍼 옵션
	Desc.BufferCount = 1;
	//Desc.BufferCount = 2;
	Desc.BufferDesc.Width = (UINT)m_RenderResolution.x;
	Desc.BufferDesc.Height = (UINT)m_RenderResolution.y;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	IDXGIDevice* pDXGIDevice = nullptr;
	IDXGIAdapter* pAdapter = nullptr;
	IDXGIFactory* pFactory = nullptr;

	m_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	if (FAILED(pFactory->CreateSwapChain(m_Device, &Desc, &m_SwapChain)))
		return E_FAIL;

	pDXGIDevice->Release();
	pAdapter->Release();
	pFactory->Release();

	return S_OK;
}
