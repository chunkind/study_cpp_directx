#include "pch.h"
#include "CEngine.h"

CEngine::CEngine() 
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{

}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resolution;

	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	return S_OK;
}