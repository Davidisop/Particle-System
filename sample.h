#include "xCore.h"

#define david_MAX_Count 100

class Sample : public xCore
{
	Particle_System		m_Particle_system;
	int					efftect_type;
	float							Sample_David_Timer_Accumulated;
	D3DXMATRIX		m_matWorld;



public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	Sample();
	~Sample();

};

