#include "David_Timer.h"


	float David_SecPerFrame = 0.0f;
	float David_GameTimer = 0.0f;

	//�����ھ�� ����ϴ� �����Լ�

	bool David_Timer::Init() 
	{
		QueryPerformanceCounter(&m_dwBeforeTick); //Init() ȣ��� �������� Tick��.
 		Start();
		return true;
	}


	bool David_Timer::Frame() 
	{
		// 1�������� �ð� üũ 
		// ���� �ð��� ã�´�. 
		QueryPerformanceCounter(&m_Current); //������� ���� Tick��.
		m_fSecPerFrame = static_cast<float> (m_Current.QuadPart - m_dwBeforeTick.QuadPart) / static_cast<float>(m_Frequency.QuadPart);
		// 1������ ������ Tick���� ���ļ��� �������� SPF�� ���´�.
		David_SecPerFrame = m_fSecPerFrame;
		David_GameTimer += m_fSecPerFrame; //�� Frame ���� second�� ���δ�.

		m_fTimer += m_fSecPerFrame;

		if (m_fTimer >= 1.0f) //1�ʰ� ���̸�, �� 1�ʸ��� ������Ʈ ��.
		{
			m_dwFPS = m_dwFrameCount;
			m_dwFrameCount = 0; 
			m_fTimer= m_fTimer-1.0f;

			_stprintf_s(m_csBuffer, L" FPS:%d,  Time : %10.4f, SPF : %10.4f", m_dwFPS, David_GameTimer, m_fSecPerFrame);
		}
		m_dwFrameCount++;
		m_dwBeforeTick = m_Current;

		return true;
	}


	bool David_Timer::Render() { return true; }
	bool David_Timer::Release() { return true; }


	// FPS,SPF ���� ���ϱ�.
	int    David_Timer::GetFPS() { return m_dwFPS; }
	float  David_Timer::GetSPF() { return m_fSecPerFrame; }


	David_Timer::David_Timer()
	{
		m_fSecPerFrame = 0.0f;

		m_bStarted = false;
		m_fEventTime = 0.0f;
		m_fTimer = 0.0f;

		m_dwFrameCount = 0;
		m_dwFPS = 0;
		memset(m_csBuffer, 0, sizeof(m_csBuffer));

		// �ý����� ���ļ� �������� ��� �´�. // �ʴ� ���ļ�TICK (�ý��� ������)
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_Frequency);
	}



	David_Timer::~David_Timer()
	{
	}





	// �̺�Ʈ Ÿ�̸ӿ� ���� ���� �Լ���

	void  David_Timer::Start()
	{
		m_fEventTime = 0.0f;
		m_bStarted = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_Start); // �̺�Ʈ Ÿ�̸� ���� ���� Tick.
	}


	void  David_Timer::Reset() 
	{
		m_bStarted = false;
		m_fEventTime = 0.0f;
		memset(&m_Start, 0, sizeof(LARGE_INTEGER));
		memset(&m_Elapse, 0, sizeof(LARGE_INTEGER));
	}

	float  David_Timer::Stop() 
	{
		float result = GetElapsedTime();
		m_bStarted = false;
		return result;
	}

	bool  David_Timer::IsStarted() const { return m_bStarted; }

	float David_Timer::GetElapsedTime() 
	{
		if (m_bStarted == true)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_Elapse);
			m_fEventTime = static_cast<float>(m_Elapse.QuadPart - m_Start.QuadPart) / static_cast<float>(m_Frequency.QuadPart);
			//Ÿ�̸� INIT()�ǰ� ���� ���ݱ��� �帥 �ð�.
		}
		return m_fEventTime;
	}



