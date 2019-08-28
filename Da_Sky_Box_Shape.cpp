
#include "David_Shape.h"



HRESULT Da_Sky_Box_Shape::CreateVertexData()
{

	HRESULT hr = S_OK;
	// �ո�
	m_VertexList.resize(24);
	m_VertexList[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	// �޸�
	m_VertexList[4] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[6] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[7] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ������
	m_VertexList[8] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[9] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[10] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[11] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ����
	m_VertexList[12] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[13] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[14] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[15] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ����
	m_VertexList[16] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[17] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[18] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[19] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// �Ʒ���
	m_VertexList[20] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[21] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[22] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[23] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	m_iNumVertex = m_VertexList.size();
	return hr;
}

HRESULT Da_Sky_Box_Shape::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

	m_iNumIndex = m_IndexList.size();
	return hr;
}


	bool Da_Sky_Box_Shape::Create(ID3D11Device* pDevice, const TCHAR* szShaderName, const TCHAR* szTextureName)
	{
		D3DXMatrixScaling(&m_matWorld, 100.0f, 100.0f, 100.0f);
		David_Shape::Create( pDevice, szShaderName, szTextureName);
		return true;
	}

	HRESULT Da_Sky_Box_Shape::LoadTexture(const TCHAR* szName)
	{
		HRESULT hr = S_OK;

		const TCHAR* g_szSkyTextures[] =
		{
			L"..\\..\\data\\st00_cm_front.bmp",
			L"..\\..\\data\\st00_cm_back.bmp",
			L"..\\..\\data\\st00_cm_right.bmp",
			L"..\\..\\data\\st00_cm_left.bmp",
			L"..\\..\\data\\st00_cm_up.bmp",
			L"..\\..\\data\\st00_cm_down.bmp"
		};

		int iNumTexture = sizeof(g_szSkyTextures) / sizeof(g_szSkyTextures[0]);

		for (int i = 0; i < iNumTexture; i++)
		{
			//m_pTexSRV[i].Attach(David_DX::CreateShaderResourceView(m_pd3dDevice, g_szSkyTextures[i]));
			David_Texture_SRV[i] = David_DX::CreateShaderResourceView(m_pd3dDevice, g_szSkyTextures[i]);
		}
		return hr;	   		
	}

	bool Da_Sky_Box_Shape::Render(ID3D11DeviceContext* pContext)
	{
		David_DX::Apply_Sampler_State(pContext, David_DX::David_DX_State::David_SSWrapPoint);// �̰� ���� ��ī�� �ڽ��� �� �³�����.
		David_DX::Apply_Raterizer_State(pContext, David_DX::David_DX_State::David_RSNoneCull_Solid);
		David_DX::Apply_DS_State(pContext, David_DX::David_DX_State::David_DSVStateDetphWriteDisable);

		D3DXMATRIX matView = m_matView; // �̷��� ���� ���� ������.. .Ȥ�ó�, �ٸ� ���� �� �� �����ϱ�. ���� ����Ǹ� �ȵǴ�.
		matView._41 = 0;
		matView._42 = 0;
		matView._43 = 0;
		Set_three_Matrixs_to_cbData(&m_matWorld, &matView, &m_matProj);

		pContext->UpdateSubresource(David_Obj_C_F.m_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
		pContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_Primitive);//Ȥ�ó� �ؼ� | D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST

		PreRender(pContext);
		//--------------------------------------------------------------------------------------
		// ���徿 ������ �ϴ� ��� : ���̴� ���ҽ���� �⺻������ 1�� ��ġ�ϰ� ���ƿ�. ��ġ��, DrawIndexed�� Ư���ؿ�.
		//--------------------------------------------------------------------------------------

		for (int i = 0 ; i < MAX_SKYBOX_TEXTURE; i++)
		{
			if (David_Texture_SRV[i] == nullptr)break; // for�� ���� Ż�⤻������.

			//pContext->PSSetShaderResources(0, 1, m_pTexSRV[i].GetAddressOf());//NumViews
			
			pContext->PSSetShaderResources(0, 1, &David_Texture_SRV[i]);
			
			pContext->DrawIndexed(6, 6 * i, 0);




			//�� �ε����� 36�� �迭�̴�.
			// ��� 6����.
			//	�̷��� : m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
			// IndexCount,	 StartIndexLocation, INT BaseVertexLocation)

			//����� ���� : pContext->DrawIndexed(iCount, 0, 0);
		}

		David_DX::Apply_Sampler_State(pContext, David_DX::David_DX_State::David_SSWrapLinear);
		David_DX::Apply_Raterizer_State(pContext, David_DX::David_DX_State::David_RSBackCull_Solid);
		David_DX::Apply_DS_State(pContext, David_DX::David_DX_State::David_DSVStateEnableLessEqual);
		//�ٽ� ���������ش�.

		return true;
	}

	Da_Sky_Box_Shape::Da_Sky_Box_Shape()
	{
		m_pTexSRV[0] = nullptr;
		m_pTexSRV[1] = nullptr;
		m_pTexSRV[2] = nullptr;
		m_pTexSRV[3] = nullptr;
		m_pTexSRV[4] = nullptr;
		m_pTexSRV[5] = nullptr;

		David_Texture_SRV[0] = nullptr;
		David_Texture_SRV[1] = nullptr;
		David_Texture_SRV[2] = nullptr;
		David_Texture_SRV[3] = nullptr;
		David_Texture_SRV[4] = nullptr;
		David_Texture_SRV[5] = nullptr;
	}


	Da_Sky_Box_Shape::~Da_Sky_Box_Shape()
	{


	}
