#include "Sprite.h"

HRESULT Sprite::CreateInputLayout()
{
	HRESULT hr = S_OK;
	if (m_bInstancing == false)
	{
		David_Plane_Shape::CreateInputLayout();
	}
	else if(m_bInstancing == true)
	{
		D3D11_INPUT_ELEMENT_DESC DAVID_layout[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},

			{"TRANSFORM", 0 , DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1}, // 4바이트 * 4개씩 = 16바이트.
			{"TRANSFORM", 1 , DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{"TRANSFORM", 2 , DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{"TRANSFORM", 3 , DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1},
				
			{"ANIMATION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{"ANIMATION", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 80, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{"ANIMATION", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 96, D3D11_INPUT_PER_INSTANCE_DATA, 1},
			{"ANIMATION", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 112, D3D11_INPUT_PER_INSTANCE_DATA, 1},

			{"MESHCOLOR", 0 , DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 128, D3D11_INPUT_PER_INSTANCE_DATA, 1},
		};

		UINT numElements = sizeof(DAVID_layout) / sizeof(DAVID_layout[0]);
		
		David_DX::CreateInputLayout
		(g_pd3dDevice,
			DAVID_layout,
			numElements,
			David_Obj_C_F.m_pVSBlob->GetBufferPointer(),
			David_Obj_C_F.m_pVSBlob->GetBufferSize(),
			David_Obj_C_F.m_pInputLayout.GetAddressOf()
		);
		
	}
	return hr;
}

HRESULT Sprite::Create_Vertex_Instance_Buffer_Instances_in_Vector(UINT iNumInstance_in)
{
	HRESULT hr = S_OK;
	m_pInstance.resize(iNumInstance_in);

	for (int iST = 0; iST < m_pInstance.size(); iST++) // 각 Instance 당, 1개씩 돌면서
	{
		D3DXMatrixIdentity(&m_pInstance[iST].matWorld);
		m_pInstance[iST].uv[0] = D3DXVECTOR4(0, 0, 0, 0);
		m_pInstance[iST].uv[1] = D3DXVECTOR4(0.25f, 0, 0, 0);
		m_pInstance[iST].uv[2] = D3DXVECTOR4(0.25f, 0.25f, 0, 0);
		m_pInstance[iST].uv[3] = D3DXVECTOR4(0, 0.25f, 0, 0); 
		m_pInstance[iST].color = D3DXVECTOR4((rand() & RAND_MAX) / (float)RAND_MAX,	(rand()&RAND_MAX) / (float)RAND_MAX, (rand()&RAND_MAX) / (float)RAND_MAX,1);
		D3DXMatrixTranspose(&m_pInstance[iST].matWorld, &m_pInstance[iST].matWorld); // 왜 전치시켰냐면, 이걸로 셰이더에 넘어가야 하기 때문이다.
	}
	m_pVertex_Instance_Buffer.Attach(David_DX::CreateVertexBuffer(g_pd3dDevice, m_pInstance.size(), sizeof(TInstatnce), &m_pInstance[0]));
	return hr;
}

HRESULT Sprite::Load(ID3D11Device* pDevice, // Create 기능.
	const TCHAR* pLoadShaderString,
	const TCHAR* pLoadTextureString,
	bool bInstancing,
	ID3D11BlendState* pBlendState)
{
	m_bInstancing = bInstancing;

	if (!Create(pDevice, pLoadShaderString, pLoadTextureString))
	{
		MessageBox(0, _T("Create"), _T("Fatal error"), MB_OK);
		return 0;
	}

	DaSp_BlendState = pBlendState;//일단 같다고만 하고, 아직 장착Set은 안했다
  
	return S_OK;
}


void Sprite::SetUVAnimation(float fAnimTime, int iWidth, int iHeight)
{

	m_fAnimTime = fAnimTime;
	the_Number_of_Textures = iWidth * iHeight;
	// 그니까 지금 ㅋㅋ 이미지 한 장 안에, 가로로 몇개가 배열, 세로로 몇 개가 배열되어 있는 것이다.
	Sec_Per_another_Texture = m_fAnimTime / the_Number_of_Textures;


	float fStepW, fStepH;
	fStepW = 1.0f / iWidth; //UV 좌표계는 가로가 1.0이다. 그것을 가로 텍스쳐 개수로 나누고 있다.
	fStepH = 1.0f / iHeight; //UV 좌표계는 세로가 1.0이다. 그것을 세로 텍스쳐 개수로 나누고 있다.

	m_Rects_List.resize(iWidth*iHeight); // 그니까 여기 있는 Rect 각각은 '한 장의 이미지 안에서 UV좌표들'를 담고 있다.
									     // vector<RectUV>  m_Rects_List;
										//  예를 들어 가로는 6개, 세로는 4개 라고 해보자. 그럼 총 24개가 한 장 이미지 안에 있다.
	for (int iRow = 0; iRow < iHeight; iRow++) //가로 노  = 6개
	{
		for (int iCollum = 0; iCollum < iWidth; iCollum++) //세로 기둥 = 4개
		{
			m_Rects_List[iRow*iWidth + iCollum].David_UV.x = iCollum * fStepW;//왼쪽위점 X좌표
			m_Rects_List[iRow*iWidth + iCollum].David_UV.y = iRow * fStepH;//왼쪽위점 Y좌표

			m_Rects_List[iRow*iWidth + iCollum].David_UV.z = iCollum * fStepW + fStepW;//왼쪽위점 X좌표
			m_Rects_List[iRow*iWidth + iCollum].David_UV.w = iRow * fStepH + fStepH;//왼쪽위점 Y좌표
		}
	}
}



void Sprite::SetRectAnimation(  // 	vector<RectUV>  m_Rects_List;의 David_UV를 채우는 게 목적
	float fAnimTime,
	int iWidth, //가로 칸 개수
	int iWidthSize,//가로 한 칸의  길이
	int iHeight, // 세로 칸 개수
	int iHeightSize) // 세로 한 칸의 길이
{
	m_fAnimTime = 		fAnimTime; // 1Turn 총 애니메이션 시

	//public: RECT  m_RectSet; 스프라이트 클래스의 자체 RECT

	m_RectSet.left = iWidth; //가로 칸 개수
	m_RectSet.right = iWidthSize; // 한 칸의 픽셀 가로 길이.
	m_RectSet.top = iHeight; // 세로 칸 개수
	m_RectSet.bottom = iHeightSize; // 한 칸의 픽셀 세로 길이.

	if (iWidth * iHeight <= 1) // 원래 기본값 = 여러장텍스쳐-스프라이트의 경우에는 이렇게 하라.
	{
		Sec_Per_another_Texture = m_fAnimTime / the_Number_of_Textures;
		return;	// 자료 부족하게 일부러 입력할 경우, 위의 것만 실행.
	}

	else if (iWidth * iHeight > 1) // 뭔가 자료들을 제대로 입력하면
	{
		Sec_Per_another_Texture = m_fAnimTime / (iWidth * iHeight);
		the_Number_of_Textures = iWidth * iHeight;
		//음... 이걸로 보아해서, m_RectSet은 분명히 용도가 일반 Rect와 다르다.
	}

	//m_RectSet.left = iWidth; //가로 칸 개수
	for (int iHeight = 0; iHeight < m_RectSet.left; iHeight++)
	{
		//m_RectSet.top = iHeight; // 세로 칸 개수
		for (int iWidth = 0; iWidth < m_RectSet.top; iWidth++)
		{
			RectUV tRect;// 여기서 뭘 할려나보다.

			tRect.Rect.left = iWidth * m_RectSet.right;
			tRect.Rect.right = (iWidth + 1) * m_RectSet.right;
			tRect.Rect.top = iHeight * m_RectSet.bottom;
			tRect.Rect.bottom = (iHeight + 1)*m_RectSet.bottom;

			tRect.David_UV = SetUV(tRect.Rect);
			m_Rects_List.push_back(tRect);// 이게 목적이다.
		}
	}
}



D3DXVECTOR4 Sprite::SetUV(RECT& Rect) //픽셀좌표계로부터 UV좌표를 얻어냄.
{
	D3DXVECTOR4 vUV; // 여기에 정의? 그럼 어딘가 쓰겠네. UV좌표라는 건가???

#pragma region UV_LeftTop 
	
	float fOffsetX = 0.0f; //Left_X초기화

	if (Rect.left > 0)
	{
		fOffsetX = (float)Rect.left / (float)(m_RectSet.left*m_RectSet.right);
	}

	float fOffsetY = 0.0f; //Left_Y초기화

	if (Rect.top > 0)
	{
		fOffsetY = (float)Rect.top / (float)(m_RectSet.top*m_RectSet.bottom);
	}

		vUV.x = fOffsetX;
		vUV.y = fOffsetY;

#pragma endregion
#pragma region UV_RightBottom 


		fOffsetX = 1.0f; //Right_X초기화

		if (Rect.right > 0)
		{
			fOffsetX = (float)Rect.right / (float)(m_RectSet.left*m_RectSet.right);
		}

		fOffsetY = 1.0f; //Right_Y초기화

		if (Rect.bottom > 0)
		{
			fOffsetY = (float)Rect.bottom / (float)(m_RectSet.top*m_RectSet.bottom);// 기존 스프라이트 RECT와 외부 RECT를 가지고 뭐하는 거지?
		}

		vUV.z = fOffsetX;// 한 Stamp의 U 가로 단위
		vUV.w = fOffsetY;// 한 Stamp의 V 세로 단위
#pragma endregion
		return vUV;
}

bool Sprite::Frame(ID3D11DeviceContext* pContext, float fGlobalTime, float fElapsedTime_in_foreachFrame)
{
	Updata(pContext, DS_Timer, Applied_Texture_Index, fGlobalTime, fElapsedTime_in_foreachFrame);
	return true;
}


void Sprite::Updata(ID3D11DeviceContext* pContext,
	float& DS_Timer_ofSprite,
	int& Applied_Texture_Index_in,
	float fGloabalTime,
	float fElapsedTime_in_foreachFrame)
{
	//스프라이트 발생 경과 시간 : 계속 쌓이기만 한다.
	m_fElapseTime += fElapsedTime_in_foreachFrame;
	// 애니메이션 교체 주기 누적 시간 : 매 프레임 쌓이며, 특정 '길이'넘어가면 0으로 초기화된다.
	DS_Timer_ofSprite += fElapsedTime_in_foreachFrame;

	if (DS_Timer_ofSprite >= Sec_Per_another_Texture)
	{
		DS_Timer_ofSprite = 0.0f;
		
		if (++Applied_Texture_Index_in >= the_Number_of_Textures) { Applied_Texture_Index_in = 0; }
		 // Sprite 객체 내장 변수 DS_Timer //이제, 애니메이션 텍스쳐 변경해야 함.
		// 이벤트 타이머가  매번 0이되서, 늘 fElapsedTime_in_foreachFrame이 기준이 되게 함.


		// 텍스쳐 애니메이션
		if (Texture_Index_List.size()>0)// 여러장 애니메이션만 저장.
		{	

		/*	if (m_pATextureRV.Get() != (TextureManager->Getptr(Texture_Index_List[Applied_Texture_Index_in])->m_pTextureSRV))
			{
				m_pATextureRV.Attach(TextureManager->Getptr(Texture_Index_List[Applied_Texture_Index_in])->m_pTextureSRV);
			}*/

				m_pATextureSRV_in_Sprite = TextureManager->Getptr(Texture_Index_List[Applied_Texture_Index_in])->m_pTextureSRV;
			   //이건 중복의 위험이 없다.

		}

		else if(Texture_Index_List.size() ==0) // UV 텍스처 에니메이션 - 한 장안에서 Rect만 달라짐. Rect로 결정하는 것임.
		{
			if (m_Rects_List.size() == 0) return;	// 정상적인 UV 애니메이션은 이미 init() 때 저장된다. m_Rects_List
		
			else if(m_Rects_List.size() > 0) 
			{
					if (m_bInstancing==true) //인스탄싱이면, 
					{
						for (int iSt = 0; iSt < m_pInstance.size(); iSt++) //vector <TInstatnce>   m_pInstance; 
						{
							D3DXVECTOR4 vUV = m_Rects_List[m_pInstance[iSt].uv[0].z].David_UV;  // 분명히 Z값에는 UV값이 아닌, 다른 정보가 담겼다.
							D3DXVECTOR4 vColor = m_pInstance[iSt].color;

							m_pInstance[iSt].uv[0] = D3DXVECTOR4(vUV.x, vUV.y, 0, 0); 
							m_pInstance[iSt].uv[1] = D3DXVECTOR4(vUV.z, vUV.y, 0, 0);
							m_pInstance[iSt].uv[2] = D3DXVECTOR4(vUV.z, vUV.w, 0, 0); 
							m_pInstance[iSt].uv[3] = D3DXVECTOR4(vUV.x, vUV.w, 0, 0);

							D3DXMatrixTranspose(&m_pInstance[iSt].matWorld, &m_pInstance[iSt].matWorld);
							// 전치를 시켰다. 바로 콘스탄트에 넘기려 그러나? 그러면, 나중에 이거 빼야할 수도. 이미 내가 넣은 거 같기도...
						}
						//FOR문 끄나고.		
						pContext->UpdateSubresource(m_pVertex_Instance_Buffer.Get(), 0, NULL, &m_pInstance[0], 0, 0);
					}

					else if(m_bInstancing==false) 
					{
						D3DXVECTOR4 vUV = m_Rects_List[Applied_Texture_Index_in].David_UV; // 16개 저장되어 있음.
						D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

						if (David_Obj_C_F.m_pTextureRV != nullptr && m_Rects_List.size()) // 처음  한장짜리니 SRV 생성되었었음.. AND 연산임. 16개.
						{
							PNCT_VERTEX vertices[] =
							{
								{D3DXVECTOR3(-1.0f,1.0f,0.0f),D3DXVECTOR3(-1.0f,1.0f,0.0f), vColor,D3DXVECTOR2(vUV.x,vUV.y)}, //T가 핵심임.
								{D3DXVECTOR3(1.0f,1.0f,0.0f),D3DXVECTOR3(-1.0f,1.0f,0.0f), vColor,D3DXVECTOR2(vUV.z,vUV.y)},
								{D3DXVECTOR3(1.0f,-1.0f,0.0f),D3DXVECTOR3(-1.0f,1.0f,0.0f), vColor,D3DXVECTOR2(vUV.z,vUV.w)},
								{D3DXVECTOR3(-1.0f,-1.0f,0.0f),D3DXVECTOR3(-1.0f,1.0f,0.0f), vColor,D3DXVECTOR2(vUV.x,vUV.w)},
							};
							pContext->UpdateSubresource(David_Obj_C_F.m_pVertexBuffer.Get(), 0, 0, &vertices, 0, 0);
							//버텍스 버퍼만 새로운 UV 좌표로 업데이트.
						}
					}
			}
		}
	}
}


bool Sprite::Render(ID3D11DeviceContext* pContext)
{
	PreRender(pContext); // 이건 또 뭐야? 보니까 PreRender()가 맞네. 그런데, 블랜드 스테이트 바꾸고, 텍스쳐리소스뷰 바꿨네. 텍스쳐 바꿨나 보군.
	PostRender(pContext);
	return true;
}


bool Sprite::PreRender(ID3D11DeviceContext* pContext)
{
	
	if (DaSp_BlendState != nullptr)	{	David_DX::Apply_Blend_State(pContext, DaSp_BlendState);	}

	 David_Shape::PreRender(pContext); 

	 pContext->UpdateSubresource(David_Obj_C_F.m_pConstantBuffer.Get(), 0, NULL, &m_cbData, 0, 0);
	 pContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	 if (m_pATextureSRV_in_Sprite != nullptr)
	 {	 pContext->PSSetShaderResources(0, 1, &m_pATextureSRV_in_Sprite); }

	return true;
}


bool Sprite::PostRender(ID3D11DeviceContext* pContext)
{
	David_Plane_Shape::PostRender(pContext); //David_Shape::PostRender 이해가 안가는게.. 그럼 Draw 혹은 DrawIndexed야...
	return true;
}

bool Sprite::RenderInstancing(ID3D11DeviceContext* pContext)
{
	Sprite::PreRender(pContext);

#pragma region Instanc Preparation 

	ID3D11Buffer* David_vb[2] = { David_Obj_C_F.m_pVertexBuffer.Get(), m_pVertex_Instance_Buffer.Get() };
	UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(TInstatnce) };
	UINT offset[2] = { 0,0 };
	
	pContext->IASetVertexBuffers(
		0, // UINT StartSlot,
		2, // UINT NumBuffers,
		David_vb, //const *ppVertexBuffers, : A pointer to an array of vertex buffers 
		stride, //*pStrides,
		offset); //*pOffsets

#pragma endregion

	pContext->DrawIndexedInstanced(m_iNumIndex, //David_Plane_Shape이라 6개임. m_iNumIndex = m_IndexList.size();
		m_pInstance.size()
		, 0 // 인덱스 버퍼 안에서 사용하는 첫번째 인덱스.
		, 0 // 버텍스 인스탄스 버퍼 안의 PNCT_VERTEX 사용하는 첫번째 인덱스.
		, 0 // 버텍스 인스탄스 버퍼 안의 TInstatnce 사용하는 첫번째 인덱스.
		);
	// 복구

	David_DX::Apply_Blend_State(pContext, David_DX_State::David_BSAlphaBlend);

	return true;
}

void Sprite::SetTextureArray(T_STR_VECTOR FileList)
{    
	// David 추가
	TCHAR szFileName[MAX_PATH]; memset(szFileName, 0, sizeof(TCHAR)*MAX_PATH);
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	//


	for (int iList = 0; iList < FileList.size(); iList++)
	{
		// David 추가
		if (iList == 0)
		{
		_tsplitpath_s(FileList[iList].c_str(), Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);// 버퍼에 합쳐 저장하기
		m_szName = szFileName;
		}
	
		//

		int iIndex = TextureManager->ADD(m_pd3dDevice, FileList[iList].c_str());
		// 여기서 텍스쳐들 매니저에 로드하고 있음.
		// SRV를 등록.

		if (iIndex <= 0)//등록안된 것임.
		{
			MessageBox(0, _T("m_Texture가 텍스쳐 매니저에 등록 실패"), _T("Fatal Error"), MB_OK);
			return;
		}

		// 텍스쳐 매니저에 등록된 인덱스를 스프라이트 객체 안의 Vector 멤버 변수에 저장해둔다.
		Texture_Index_List.push_back(iIndex);
	}

	the_Number_of_Textures = Texture_Index_List.size();
	//이 스프라이트에 사용되는 텍스쳐들 총 숫자.
}


Sprite::Sprite()
{
	m_pVertex_Instance_Buffer = nullptr;
	m_iIndex_in_spriteManager = 1004;
	m_fAnimTime = 0.0f;
	m_fLifeTime = 0.0f;
	m_fElapseTime = 0.0f;
	m_bInstancing = false;
	m_BlendType = 0;
	DS_Timer = 0.0f;
	Applied_Texture_Index = 0;
	Sec_Per_another_Texture = 0.2f;
	the_Number_of_Textures = 1;
	m_RectSet.left = 4;
	m_RectSet.right = 64; // 텍스쳐 가로 셋 갯수 및 크기	
	m_RectSet.top = 4;
	m_RectSet.bottom = 64; // 텍스쳐 세로 셋 갯수 및 크기
	//m_pATextureRV = nullptr;
	m_pATextureSRV_in_Sprite = nullptr;
	DaSp_BlendState = nullptr;
	m_ParticleColor = D3DXVECTOR4(1, 1, 1, 1);
}


Sprite::~Sprite()
{

}

