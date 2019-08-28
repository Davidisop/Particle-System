#include "Particle_System.h"


Particle::Particle() 
//�ʱⰪ���� ��������.
{
	int david_random = rand();
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAdd = D3DXVECTOR3(cosf(rand()), sinf(rand()), (cosf(rand())+sinf(rand()))/2);// rand()�� ��ȯ���� int �����̴�.
	D3DXVec3Normalize(&m_vAdd, &m_vAdd);

	m_vColor.x = (float)(rand() % RAND_MAX) / RAND_MAX; // % �������� ������ ������ ������ ���� �� ���´�.
	m_vColor.y = (float)(rand() % RAND_MAX) / RAND_MAX;
	m_vColor.z = (float)(rand() % RAND_MAX) / RAND_MAX;
	m_vColor.w = (float)(rand() % RAND_MAX) / RAND_MAX;
	
	m_fTimer = 0;
	m_fLifeTime = (float)(rand() % 10);
	m_bRender = true;

	m_iApplyIndex = 0;
	m_iSpriteIndex = (rand() % SpriteManager->Sprite_Map.size()) + 1; // 1������ ��������Ʈ�� ����Ǿ���.	
		
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

		// Create���� matWorld�� ������ķ� �ʱ�ȭ��
		return true;
	}

	//�ִ� ��ƼŬ ���� ���ϰ�, �����Ѵ�.
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
		D3DXVECTOR3 vReturnVaule = Circle_Coordinate_Set(m_fRadius, extern_time); // ������ m_fRadius �� �� (������  0,0,0, z=�׻�0) ���� �� ���� ��ǥ. (radius , radian)
		vReturnVaule *= m_multiply_Radius_times; // (0,0,0)�� �߽�����, �ܼ� Ȯ��.

		if ((extern_time - PS_some_fTimer) > m_fAddTime_per_oneParticle)
		{

			if (m_iEndCount + 1 <= iMax_Particles_Number_Count)
			{
				david_particles[m_iEndCount].m_vPos.x = vReturnVaule.x;
				david_particles[m_iEndCount].m_vPos.y = vReturnVaule.y;
				david_particles[m_iEndCount].m_vPos.z = sqrt(vReturnVaule.x*vReturnVaule.x + vReturnVaule.y*vReturnVaule.y);//��Ʈ
				
				m_iEndCount += 1; //��ŸƮ ī��Ʈ, ���� ī��Ʈ�� �����̴°�, �̰� �ٽ��� �� ����.
			}

			else if (m_iEndCount + 1 > iMax_Particles_Number_Count)
			{
				//m_iEndCount = iMax_Particles_Number_Count;
				m_iStartCount++; // �̰� ���� �Ѱ��� �پ���.

				if (m_iStartCount >= m_iEndCount)
				{
					m_iStartCount = 0, m_iEndCount = 1; //�ʱ�ȭ�ȴ�.  Render() ���� 'iParticle<End_Count'�̱� ������, �ƿ� Draw() �Ǵ°� ���°��̴�. �� ����
					//EndCount�� �þ�� �����.
				}
			}

			PS_some_fTimer = extern_time;// �Ź� �̰ɷ� ���ΰ� ������Ʈ �Ǿ�, ���� �����ӿ���, �� m_fAddTime_per_oneParticle�� ������ �ǰ� ��.
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
				david_particles[iParticle].m_vPos.z);//1�ֱ� �ȿ����� �Ⱥ��ؿ�.

			D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);//1�ֱ� �ȿ����� �Ⱥ��ؿ�.
			D3DXMatrixMultiply(&m_matWorld, &matScale, &Billboard); //ī�޶� �� ȸ���ϴ� �� �Ⱥ��ؿ�.
			D3DXMatrixMultiply(&m_matWorld, &m_matWorld, &matTrans);  //�̰͵� �� ���ؿ�.

		        //������->�����������ڸ�ȸ��->������ǥ�����̵�.

			david_pSprite_inPS = SpriteManager->GetPtr(david_particles[iParticle].m_iSpriteIndex);
			// ó�� ��ƼŬ�� ������ ��, 
			david_pSprite_inPS->m_cbData.vColor = david_particles[iParticle].m_vColor;
			// Į��� Particle �����ڿ��� ������ �ɷ� ���� ����. �� ���ؿ�.
		
			david_pSprite_inPS->Updata(pContext,
			david_particles[iParticle].m_fTimer, // Particle�� ��� ����, ��� ��� ������? ��������Ʈ Updata()�Լ� �ȿ��� &��.
			david_particles[iParticle].m_iApplyIndex, //Particle�� ��� ����, ��� ��� ������? ��������Ʈ Updata()�Լ� �ȿ��� &��.
			David_GameTimer,
			David_SecPerFrame);

			david_pSprite_inPS->Set_three_Matrixs_to_cbData(&m_matWorld, &m_matView, &m_matProj);
			david_pSprite_inPS->Render(pContext);
			// ���� ��������Ʈ�� Render()�Ѵ�.
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
		assert(pmatView && pmatProj); // pmatView �� pmatProj�� 0���� üũ�ؼ�, 0�̸� ���α׷��ߴ�.
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
