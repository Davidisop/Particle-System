#pragma once

#include "xDevice.h"
class xWindow : public xDevice
{
public:
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_rtClient;
	RECT		m_rtWindow;
private:
	DWORD		m_dwStyle;
public:
	void		Set(DWORD dwStyle);
	void		CenterWindow();
	bool		SetWindow(HINSTANCE	hInstance,
		const TCHAR* pTitleName = L"KGCA Sample",
		UINT iWidth = 800, UINT iHeight = 600);
public:
	bool		Run();
public:
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool	GameInit();
	virtual bool	GameRun();
	virtual bool	GameRelease();
	
	void MsgEvent(MSG msg);
public:
	xWindow();
	virtual ~xWindow();
};

