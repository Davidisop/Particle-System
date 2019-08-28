#pragma once
#include "Sprite_Manager.h"
#define MAX_PARTICLE	3000

class Particle
{
public:
	D3DXVECTOR3 m_vPos;           //��ƼŬ ��ġ
	D3DXVECTOR3 m_vAdd;           // ��ƼŬ ���� ��ġ�� �����Ӹ��� �������� ��
	D3DXVECTOR4 m_vColor;         // ��ƼŬ ����
	float	    m_fTimer;         // ����ú��� �����Ǵ� �ð�
	float       m_fLifeTime;      // ��ƼŬ�� ����
	bool		m_bRender;		  // ��������

public:
	int			m_iApplyIndex;    // �ؽ��� �ε���
	int			m_iSpriteIndex;   // ��������Ʈ Ÿ�� �ε���


	

public:
	Particle();
	~Particle();
};

class Particle_System
{
public:
	ID3D11Device*			m_pd3dDevice;
	Sprite*		david_pSprite_inPS;
	Particle*	david_particles;
	D3DXMATRIX				m_matWorld;
	D3DXMATRIX				m_matView;
	D3DXMATRIX				m_matProj;
public:
	int		m_iStartCount;
	int		m_iEndCount;
	float   PS_some_fTimer; // ��ƼŬ �ý��۾ȿ� �ִ� ������... ���� ���� Ÿ�̸�.
	float   m_fRadius;
	int     iMax_Particles_Number_Count;
	float   m_fAddTime_per_oneParticle; // ��ƼŬ 1�� �� add Ÿ��.
	float   m_multiply_Radius_times;
	D3DXVECTOR3 m_vScale;

public:
	void SetRadius(float fRadius = 1.0f);
	void SetAddTime_each_Paritcle(float fTime_in);
	void Set_Multiply_Radius_times(float m_fAddRadius_in);
	void SetScale(float fX, float fY, float fZ);

	void Set_Particles_to_MaxCounter(int iMaxNum);
	int  Get_Particles_MaxCounter();
	void ReSet_Start_End_Timer();

public:
	bool Init();
	bool Create(ID3D11Device* pDevice, INT iMaxCounter = 100, float acc_Time = 10.0f, float multiply_Radius_in = 30.0f, D3DXVECTOR3 vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	bool Frame(ID3D11DeviceContext* pContext, float extern_time, float fElapsedTime);
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();


public://�ִ� ��ƼŬ ���� ���ϰ�, �Ҵ��Ѵ�.
	void set_three_Matrixs_inParticleSystem(D3DXMATRIX* pmatWorld, D3DXMATRIX* pmatView, D3DXMATRIX* pmatProj);

public:
	D3DXVECTOR3 Circle_Coordinate_Set(float fRadius, float fRadian);

public:	
	Particle_System();
	virtual ~Particle_System();
};

