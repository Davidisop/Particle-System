#pragma once
#include "xStd.h"


class David_Timer
{
public:
	LARGE_INTEGER m_Frequency; // �ʴ� ���ļ�TICK (�ý��� ������)
	LARGE_INTEGER m_Current; // ������� TICK
	LARGE_INTEGER m_dwBeforeTick;  // ���� �������� �ð� üũ
	float         m_fSecPerFrame;    // 1�������� ��� �ð�seconds
	
public:

	float m_fTimer;
	TCHAR m_csBuffer[256];
	int m_dwFrameCount;
	int m_dwFPS;

public:

	LARGE_INTEGER m_Start;    //�̺�Ʈ Ÿ�̸� ���� ƽ
	LARGE_INTEGER m_Elapse;   // �̺�Ʈ Ÿ�̸� �����ĺ��� ���� ƽ ��

	bool          m_bStarted; // �̺�Ʈ Ÿ�̸� �۵� ����
	float         m_fEventTime;

public:
	
	//�����ھ�� ����ϴ� �����Լ�
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	// �̺�Ʈ Ÿ�̸ӿ� ���� ���� �Լ���
	void  Reset();
	void  Start();
	float Stop();
	bool  IsStarted() const;
	float GetElapsedTime();


	// FPS,SPF ���� ���ϱ�.
	int    GetFPS();
	float  GetSPF();

public:
	David_Timer();
	virtual ~David_Timer();
};

