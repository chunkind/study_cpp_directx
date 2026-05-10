#pragma once

class CEngine
{
private:
	HWND m_hMainHwnd;
	POINT m_Resolution;

public:
	int init(HWND _hWnd, POINT _Resolution);
	//new
	void progress();

public:
	static CEngine* GetInst() {
		static CEngine mgr;
		return &mgr;
	}

private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
};

