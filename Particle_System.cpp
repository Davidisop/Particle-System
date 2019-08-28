#include "Particle_System.h"


Particle::Particle() 
//초기값으로 정해진다.
{
	int david_random = rand();
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAdd = D3DXVECTOR3(cosf(rand()), sinf(rand()), (cosf(rand())+sinf(rand()))/2);// rand()의 반환값은 int 랜덤이다.
	D3DXVec3Normalize(&m_vAdd, &m_vAdd);

	m_vColor.x = (float)(rand() % RAND_MAX) / RAND_MAX; // % 나머지는 무조건 나누는 수보다 작은 게 나온다.
	m_vColor.y = (float)(rand() % RAND_MAX) / RAND_MAX;
	m_vColor.z = (float)(rand() % RAND_MAX) / RAND_MAX;
	m_vColor.w = (float)(rand() % RAND_MAX) / RAND_MAX;
	
	m_fTimer = 0;
	m_fLifeTime = (float)(rand() % 10);
	m_bRender = true;

	m_iApplyIndex = 0;
	m_iSpriteIndex = (rand() % SpriteManager->Sprite_Map.size()) + 1; // 1번부터 스프라이트가 저장되었음.	
		
}

Particle::~Particle()
{
	
}

	void Particle_System::SetRadius(float fRadius_in) { m_fRadius = fRadius_in; }
	void Particle_System::SetAddTime_each_Paritcle(float fTime_in) { m_fAddTime_per_oneParticle = fTime_in; };
	void Particle_System::Set_Multiply_Radius_times(float multiply_Radius_in) { m_multiply_Radius_times = multiply_Radius_in; };
	void Particle_System::SetScale(float fX, float fY, float fZ) { m_vScale.x = fX; m_vScale.y = fY; m_vScale.z = fZ; }
	
	bool Particle_System::Init()
	{
		m_pd3dDevice =							nullptr;
		david_pSprite_inPS =					nullptr;
		david_particles =							nullptr;

		m_fRadius =									1.0f;
		m_iStartCount =								0;
		m_iEndCount =								1;
		PS_some_fTimer =						0.0f;
		iMax_Particles_Number_Count =	MAX_PARTICLE;
		m_fAddTime_per_oneParticle =	0.1f;
		m_multiply_Radius_times =			30.0f;
		m_vScale.x =									1.0f;
		m_vScale.y =									1.0f;
		m_vScale.z =									1.0f;

		// Create에서 matWorld는 단위행렬로 초기화됨
		return true;
	}

	//최대 파티클 개수 정하고, 생성한다.
	void Particle_System::Set_Particles_to_MaxCounter(int iMaxNum)
	{
		delete[] david_particles; david_particles = nullptr;
		iMax_Particles_Number_Count = iMaxNum;
		david_particles = new Particle[iMax_Particles_Number_Count];
	}

	
	bool Particle_System::Create(ID3D11Device* pDevice, INT iMaxCounter, float grossed_Time, float multiply_Radius_in, D3DXVECTOR3 vScale)
	{
		m_pd3dDevice = pDevice;
		assert(m_pd3dDevice);
		Set_Particles_to_MaxCounter(iMaxCounter);
		SetAddTime_each_Paritcle(grossed_Time / iMaxCounter);
		Set_Multiply_Radius_times(multiply_Radius_in);
		SetScale(vScale.x, vScale.y, vScale.z);
		D3DXMatrixIdentity(&m_matWorld);	
		return true;
	}

	bool Particle_System::Frame(ID3D11DeviceContext* pContext, float extern_time, float fElapsedTime)
	{
		D3DXVECTOR3 vReturnVaule = Circle_Coordinate_Set(m_fRadius, extern_time); // 반지름 m_fRadius 인 원 (중점은  0,0,0, z=항상0) 상의 한 점의 좌표. (radius , radian)
		vReturnVaule *= m_multiply_Radius_times; // (0,0,0)을 중심으로, 단순 확장.

		if ((extern_time - PS_some_fTimer) > m_fAddTime_per_oneParticle)
		{

			if (m_iEndCount + 1 <= iMax_Particles_Number_Count)
			{
				david_particles[m_iEndCount].m_vPos.x = vReturnVaule.x;
				david_particles[m_iEndCount].m_vPos.y = vReturnVaule.y;
				david_particles[m_iEndCount].m_vPos.z = sqrt(vReturnVaule.x*vReturnVaule.x + vReturnVaule.y*vReturnVaule.y);//루트
				
				m_iEndCount += 1; //스타트 카운트, 엔드 카운트가 움직이는게, 이게 핵심인 거 같다.
			}

			else if (m_iEndCount + 1 > iMax_Particles_Number_Count)
			{
				//m_iEndCount = iMax_Particles_Number_Count;
				m_iStartCount++; // 이걸 통해 한개씩 줄어든다.

				if (m_iStartCount >= m_iEndCount)
				{
					m_iStartCount = 0, m_iEndCount = 1; //초기화된다.  Render() 에서 'iParticle<End_Count'이기 때문에, 아예 Draw() 되는게 없는것이다. 그 다음
					//EndCount가 늘어나며 생긴다.
				}
			}

			PS_some_fTimer = extern_time;// 매번 이걸로 쌓인게 업데이트 되어, 다음 프레임에서, 딱 m_fAddTime_per_oneParticle이 기준이 되게 함.
		}
		return true;
	}

	bool Particle_System::Render(ID3D11DeviceContext* pContext)
	{
		D3DXMATRIX Billboard, matTrans, matScale;
		

		D3DXMatrixInverse(&Billboard, NULL, &m_matView);
		Billboard._41 = 0.0f;	Billboard._42 = 0.0f;	Billboard._43 = 0.0f;		Billboard._44 = 1.0f;


		for (int iParticle = m_iStartCount; iParticle < m_iEndCount; iParticle++)
		{

			D3DXMatrixTranslation(&matTrans, 
				david_particles[iParticle].m_vPos.x,
				david_particles[iParticle].m_vPos.y,
				david_particles[iParticle].m_vPos.z);//1주기 안에서는 안변해요.

			D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);//1주기 안에서는 안변해요.
			D3DXMatrixMultiply(&m_matWorld, &matScale, &Billboard); //카메라 안 회전하는 한 안변해요.
			D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &matTrans);  //이것도 안 변해요.

		        //스케일->렌즈향해제자리회전->절대좌표기준이동.

			david_pSprite_inPS = SpriteManager->GetPtr(david_particles[iParticle].m_iSpriteIndex);
			// 처음 파티클이 생성될 때, 
			david_pSprite_inPS->m_cbData.vColor = david_particles[iParticle].m_vColor;
			// 칼라는 Particle 생성자에서 생성된 걸로 갖다 쓴다. 안 변해요.
		
			david_pSprite_inPS->Updata(pContext,
			david_particles[iParticle].m_fTimer, // Particle의 멤버 변수, 어디서 어떻게 쌓이지? 스프라이트 Updata()함수 안에서 &로.
			david_particles[iParticle].m_iApplyIndex, //Particle의 멤버 변수, 어디서 어떻게 쌓이지? 스프라이트 Updata()함수 안에서 &로.
			David_GameTimer,
			David_SecPerFrame);

			david_pSprite_inPS->Set_three_Matrixs_to_cbData(&m_matWorld, &m_matView, &m_matProj);
			david_pSprite_inPS->Render(pContext);
			// 역시 스프라이트로 Render()한다.
		}

		return true;
	}

	bool Particle_System::Release()
	{
		delete[] david_particles;
		david_particles = nullptr;

		return true;
	}

	int  Particle_System::Get_Particles_MaxCounter() { return iMax_Particles_Number_Count; }

	void Particle_System::ReSet_Start_End_Timer()
	{
		m_iStartCount = 0;
		m_iEndCount = 1;
		PS_some_fTimer = 0.0f;
	}

	void Particle_System::set_three_Matrixs_inParticleSystem(D3DXMATRIX* pmatWorld, D3DXMATRIX* pmatView, D3DXMATRIX* pmatProj)
	{
		assert(pmatView && pmatProj); // pmatView 와 pmatProj가 0인지 체크해서, 0이면 프로그램중단.
		if (pmatWorld != nullptr) {m_matWorld = *pmatWorld;	}
		m_matView = *pmatView;
		m_matProj = *pmatProj;
	}

	D3DXVECTOR3 Particle_System::Circle_Coordinate_Set(float fRadius, float fRadian)
	{
		D3DXVECTOR3 vFinally;
		vFinally.x = fRadius * cosf(fRadian);
		vFinally.y = fRadius * sinf(fRadian);
		vFinally.z = 0.0f;
		return vFinally;
	}





	Particle_System::Particle_System()
	{
		Init();
	}


Particle_System::~Particle_System()
{
}
