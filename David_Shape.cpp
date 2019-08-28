#include "David_Shape.h"
void    David_Shape::SetColor(D3DXVECTOR4 vColor)
{
	m_cbData.vColor = vColor;
}

void  David_Shape::Set_three_Matrixs_to_cbData(
	D3DXMATRIX* pWorld,
	D3DXMATRIX* pView,
	D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}

	m_vPosition.x = m_matWorld._41;
	m_vPosition.y = m_matWorld._42;
	m_vPosition.z = m_matWorld._43;
	m_vLook.x = m_matWorld._11;
	m_vLook.y = m_matWorld._12;
	m_vLook.z = m_matWorld._13;
	m_vSide.x = m_matWorld._21;
	m_vSide.y = m_matWorld._22;
	m_vSide.z = m_matWorld._23;
	m_vUp.x = m_matWorld._31;
	m_vUp.y = m_matWorld._32;
	m_vUp.z = m_matWorld._33;

	D3DXMatrixTranspose(&m_cbData.matWorld,
		&m_matWorld);
	D3DXMatrixTranspose(&m_cbData.matView,
		&m_matView);
	D3DXMatrixTranspose(&m_cbData.matProj,
		&m_matProj);
}
bool  David_Shape::Create(
	ID3D11Device* pDevice,
	const TCHAR*  szShaderName,
	const TCHAR*  szTextureName)
{
	m_pd3dDevice = pDevice;
	CreateVertexData();
	CreateIndexData();
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateConstantBuffer();
	
	LoadVertexShader(szShaderName);
	LoadPixelShader(szShaderName);
	LoadGeometryShader(szShaderName);

	CreateInputLayout();
	LoadTexture(szTextureName);
	return true;
}
HRESULT David_Shape::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	m_one_VertexSize = sizeof(PNCT_VERTEX);
	David_DX::CreateVertexBuffer(
		m_pd3dDevice,
		m_iNumVertex,
		sizeof(PNCT_VERTEX),
		&m_VertexList.at(0),
		David_Obj_C_F.m_pVertexBuffer.GetAddressOf());
	return hr;
}
HRESULT David_Shape::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	David_DX::CreateIndexBuffer(m_pd3dDevice,
		m_iNumIndex,
		sizeof(DWORD),
		&m_IndexList.at(0), 
		David_Obj_C_F.m_pIndexBuffer.GetAddressOf());
	return hr;
}
HRESULT David_Shape::CreateConstantBuffer() {
	HRESULT hr = S_OK;
	David_DX::CreateConstantBuffer(m_pd3dDevice,
		1,
		sizeof(T_CB_DATA),
		David_Obj_C_F.m_pConstantBuffer.GetAddressOf(),
		&m_cbData, false);
	return hr;
}
HRESULT David_Shape::CreateInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
			 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	David_DX::CreateInputLayout(m_pd3dDevice,
		layout,
		numElements,
		David_Obj_C_F.m_pVSBlob->GetBufferPointer(),
		David_Obj_C_F.m_pVSBlob->GetBufferSize(),	
		David_Obj_C_F.m_pInputLayout.GetAddressOf());

	return hr;
}
HRESULT David_Shape::LoadVertexShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pVertexShader.Attach(
		David_DX::LoadVertexShaderFile(m_pd3dDevice,
			szName,
			David_Obj_C_F.m_pVSBlob.GetAddressOf()));
	return hr;
}
HRESULT David_Shape::LoadPixelShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pPixelShader.Attach(
		David_DX::LoadPixelShaderFile(m_pd3dDevice,
			szName));

	return hr;
}
HRESULT David_Shape::LoadGeometryShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pGeometryShader.Attach(
		David_DX::LoadGeometryShaderFile(m_pd3dDevice,
			szName));

	return hr;
}
HRESULT David_Shape::LoadTexture(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	D3DX11_IMAGE_LOAD_INFO loadinfo;
	ZeroMemory(&loadinfo, sizeof(loadinfo));
	loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadinfo.Format = DXGI_FORMAT_FROM_FILE;
	ID3D11ShaderResourceView* pTex = NULL;
	hr=D3DX11CreateShaderResourceViewFromFile(
		m_pd3dDevice,
		szName,
		&loadinfo, NULL, 
		David_Obj_C_F.m_pTextureRV.GetAddressOf(), NULL);
	
	return hr;
}
bool  David_Shape::PreRender(
	ID3D11DeviceContext* pContext)
{
	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);
	return true;
}
bool  David_Shape::Render(ID3D11DeviceContext* pContext) {
	pContext->UpdateSubresource(
		David_Obj_C_F.m_pConstantBuffer.Get(),
		0, NULL, &m_cbData, 0, 0);
	pContext->IASetPrimitiveTopology(
		(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);
	David_Obj_C_F.PostRender(pContext, m_one_VertexSize, m_iNumIndex);
	return true;
}
bool  David_Shape::PostRender(ID3D11DeviceContext* pContext	)
{
	David_Obj_C_F.PostRender(pContext, m_one_VertexSize, m_iNumIndex);
	return true;
}
bool  David_Shape::Release()
{
	return true;
}
bool  David_Shape::Frame()
{
	return true;
}
bool  David_Shape::Init()
{
	return true;
}
David_Shape::David_Shape()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_vPosition.x = m_matWorld._41;
	m_vPosition.y = m_matWorld._42;
	m_vPosition.z = m_matWorld._43;
	m_vLook.x = m_matWorld._11;
	m_vLook.y = m_matWorld._12;
	m_vLook.z = m_matWorld._13;
	m_vSide.x = m_matWorld._21;
	m_vSide.y = m_matWorld._22;
	m_vSide.z = m_matWorld._23;
	m_vUp.x = m_matWorld._31;
	m_vUp.y = m_matWorld._32;
	m_vUp.z = m_matWorld._33;

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}


David_Shape::~David_Shape()
{
}
