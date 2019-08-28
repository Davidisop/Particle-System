#pragma once
#include "David_Obj_Compo_Func.h"

struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
};
struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	bool operator == (const PNCT_VERTEX & Vertex)
	{
		if (p == Vertex.p  && n == Vertex.n && 	c == Vertex.c  &&	t == Vertex.t)
		{
			return true;
		}
		return  false;
	}
	PNCT_VERTEX() {}
	PNCT_VERTEX(D3DXVECTOR3		vp,
		D3DXVECTOR3		vn,
		D3DXVECTOR4		vc,
		D3DXVECTOR2     vt)
	{
		p = vp, n = vn, c = vc, t = vt;
	}
};
struct PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
};

struct T_CB_DATA
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	float fTime;
	float fActiveVP;
	float z, w;
	D3DXVECTOR4  vColor;

	T_CB_DATA()
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matView);
		D3DXMatrixIdentity(&matProj);
		fTime=0;
		fActiveVP = 0;
		z = 0; w = 0;
		vColor = { 1.0f,1.0f,1.0f,1.0f };
	}
};