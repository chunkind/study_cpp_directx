#pragma once


class CEngine
{
// 데이터 영역 메모리 : 전역 변수
// 프로세스 시작할때 초기화
// 프로세스 종료시 해제
// 프로세스가 실행도중 상시 유지되는 메모리
private:
	static CEngine* g_This;

private:
	HWND	m_hMainWnd;

public:
	// 정적 맴버함수 : 객체가 없어도 호출 가능
	static CEngine* GetInst()
	{
		if (g_This == nullptr) {
			g_This = new CEngine;
		}
		return g_This;
	}

	static void Destroy() {
		delete g_This;
		g_This = nullptr;
	}
private:
	CEngine();

};

