#include "pch.h"
#include "CEngine.h"

//old
/*CEngine::CEngine() {

}*/
//new
CEngine::CEngine() 
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{

}

//new
int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resolution;

	// 클라이언트 영역 기준 해상도 설정
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };

	// 윈도우 스타일(타이틀바, 테두리 등)을 포함한 전체 창 크기 계산
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 계산된 크기로 실제 윈도우 크기 설정
	SetWindowPos(
		m_hMainHwnd,        /* 대상 윈도우 핸들 */
		nullptr,            /* hWndInsertAfter Z-Order 기준 nullptr이면 순서 변경 안 함 */
		0,                  /* X 좌표 */
		0,                  /* Y 좌표 */
		rt.right - rt.left, /* 너비 */
		rt.bottom - rt.top, /* 높이 */
		0                   /* 추가 옵션 플래그 0 이면 기본*/
	);

	return S_OK;
	// return E_FAIL;
}