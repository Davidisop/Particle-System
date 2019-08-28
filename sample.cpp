#include "Sample.h"


	bool Sample::Init()
	{
		// Sprite Type  = A// 단일 알파가 붙은 텍스쳐
		int david_int =	SpriteManager->Add(g_pd3dDevice, L"../../data/effect/DeferredParticle.dds", L"../../data/shader/Plane.hlsl", David_DX_State::David_BSAlphaBlend);


		//Sprite Type = B; // 1  장 16개 스탬프.
		david_int = SpriteManager->Add(g_pd3dDevice, L"../../data/effect/s.dds", L"../../data/shader/Plane.hlsl", David_DX_State::David_BS_Color_One);
		Sprite* David_Sprite_ptr = SpriteManager->GetPtr(david_int);
		David_Sprite_ptr->SetRectAnimation(5.0f, 4, 128, 4, 128);
		
		//Sprite Type  = C // 10장 스프라이트.
		david_int = SpriteManager->Add(g_pd3dDevice, nullptr, L"../../data/shader/plane.hlsl", David_DX_State::David_BS_Color_One);
		David_Sprite_ptr = SpriteManager->GetPtr(david_int);
		T_STR_VECTOR FileList;  // vector<T_STR> // typedef std::basic_string<TCHAR : 문자 1개에 16비트 유니코드> T_STR;
		
		for (int iTexture = 0; iTexture < 10; iTexture++)
		{
			TCHAR pBuffer[50];
			_stprintf_s(pBuffer, L"../../data/effect/shine%d.bmp", iTexture); //_stprintf_s 버퍼에 담아주는 함수 입니다
			FileList.push_back(pBuffer);
		}

		David_Sprite_ptr->SetTextureArray(FileList);
		David_Sprite_ptr->SetRectAnimation(2.0f);


		// 파티클 시스템 생성
		m_Particle_system.Create(g_pd3dDevice, 100, D3DX_PI*2.0f, 50.0f, D3DXVECTOR3(30.0f, 30.0f, 30.0f));
		return true;
	}

	bool Sample::Frame()
	{
		Sample_David_Timer_Accumulated += David_SecPerFrame;// 매 프레임 쌓인다
		float David_Radius = 1.0f;

		//  EffectType이 0~12까지 총 13개 있나보다.

		if (g_Input.prior_effect)
		{
			efftect_type++;
			if (efftect_type > 12) { efftect_type = 1; }

			m_Particle_system.ReSet_Start_End_Timer();
			Sample_David_Timer_Accumulated = 0.0f;
		}

		if (g_Input.next_effect)
		{
			efftect_type--;
			if (efftect_type < 1) { efftect_type = 12; }

			m_Particle_system.ReSet_Start_End_Timer();
			Sample_David_Timer_Accumulated = 0.0f;
		}


		switch (efftect_type)
		{
		case 1: //세잎장미
			David_Radius = sinf(Sample_David_Timer_Accumulated / 2);
			break;
		case 2://네잎장미
			David_Radius = sinf(2 * Sample_David_Timer_Accumulated);
			break;
		case 3://별
			David_Radius = sinf(4 * Sample_David_Timer_Accumulated);
			break;
		case 4://심장형 곡선좌
			David_Radius = 1 + cosf(Sample_David_Timer_Accumulated);
			break;
		case 5://심장형 곡선우
			David_Radius = 1 - cosf(Sample_David_Timer_Accumulated);
			break;
		case 6://심장형 곡선상
			David_Radius = 1 - sinf(Sample_David_Timer_Accumulated);
			break;
		case 7://심장형 곡선상
			David_Radius = 1 + sinf(Sample_David_Timer_Accumulated);
			break;
		case 8://파형 가로
			David_Radius = 1 + cosf(2 * Sample_David_Timer_Accumulated);
			break;
		case 9://파형 세로
			David_Radius = 1 - cosf(2 * Sample_David_Timer_Accumulated);
			break;
		case 10:// 트랙 가로
			David_Radius = 2 + cosf(2 * Sample_David_Timer_Accumulated);
			break;
		case 11:// 트랙 세로
			David_Radius = 2 - cosf(2 * Sample_David_Timer_Accumulated);
			break;
		case 12:// 별
			David_Radius = tanf(Sample_David_Timer_Accumulated);
			break;
		}

		m_Particle_system.SetRadius(David_Radius);
		m_Particle_system.Frame(m_pContext, Sample_David_Timer_Accumulated, David_SecPerFrame);

		return true;	
	}

	bool Sample::Render()
	{
		Apply_Blend_State(m_pContext, David_DX_State::David_BS_Color_One);
		Apply_Raterizer_State(m_pContext, David_DX_State::David_RSNoneCull_Solid);
		Apply_DS_State(m_pContext, David_DX_State::David_DSVStateDisable);

		m_Particle_system.set_three_Matrixs_inParticleSystem(nullptr, &MainCamera->m_matView, &MainCamera->m_matProj);
		m_Particle_system.Render(m_pContext);
		return true;
	}


	bool Sample::Release()
	{
		m_Particle_system.Release();
		return true;
	}


	Sample::Sample() 
	{
		efftect_type = 0;
		Sample_David_Timer_Accumulated = 0.0f;
	}
	Sample::~Sample() {}


GAME_RUN("Sample", 800, 600)