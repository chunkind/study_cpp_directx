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
	m_SwapChain->Release();
	//new
	m_RenderTargetTex->Release();

	//new
	m_RTV->Release();
	m_DepthStencilTex->Release();
	m_DSV->Release();
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

	if (FAILED(CreateSwapchain()))
	{
		return E_FAIL;
	}

	//new
	if (FAILED(CreateView()))
	{
		return E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateSwapchain()
{
	DXGI_SWAP_CHAIN_DESC Desc = {};

	Desc.OutputWindow = m_hMainWnd;
	Desc.Windowed = true;

	Desc.BufferCount = 1;
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

//new
int CDevice::CreateView()
{
	// 1. RenderTarget Texture를 스왚체인으로부터 가져오기
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_RenderTargetTex);

	// 2. RenderTargetView 를 생성한다.
	m_Device->CreateRenderTargetView(m_RenderTargetTex, nullptr, &m_RTV);

	// 3. DepthStencil 용 Texture 를 제작
	D3D11_TEXTURE2D_DESC Desc = {};

	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Width = (UINT)m_RenderResolution.x;
	Desc.Height = (UINT)m_RenderResolution.y;
	Desc.ArraySize = 1;

	Desc.CPUAccessFlags = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_Device->CreateTexture2D(&Desc, nullptr, &m_DepthStencilTex);

	// 4. DepthStencil View
	m_Device->CreateDepthStencilView(m_DepthStencilTex, nullptr, &m_DSV);

	// RenderTarget 과  DepthStencilTarget 을 출력으로 지정한다.
	m_Context->OMSetRenderTargets(1, &m_RTV, m_DSV);

	return S_OK;
}
