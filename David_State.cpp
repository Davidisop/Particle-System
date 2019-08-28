﻿#include "David_State.h"

namespace David_DX
{
	//
	ID3D11BlendState* David_DX_State::David_BSNoBlend=0;
	ID3D11BlendState* David_DX_State::David_BS_Color_One = 0;
	ID3D11BlendState* David_DX_State::David_BSAlphaBlend=0;
	ID3D11BlendState* David_DX_State::David_BS_AlphaMaxOneOne = 0;
	//
	ID3D11DepthStencilState*   David_DX_State::David_DSVStateDetphWriteDisable = 0;
	ID3D11DepthStencilState*   David_DX_State::David_DSVStateEnableLessEqual =0;
	ID3D11DepthStencilState*   David_DX_State::David_DSVStateEnableGreater =0;
	ID3D11DepthStencilState*   David_DX_State::David_DSVStateDisable = 0;
	//
	ID3D11RasterizerState* David_DX_State::David_RSWireFrame=0;
	ID3D11RasterizerState* David_DX_State::David_RSSolid = 0;
	ID3D11RasterizerState* David_DX_State::David_RSBackCull_Solid = 0;
	ID3D11RasterizerState* David_DX_State::David_RSFrontCull_Solid = 0;
	ID3D11RasterizerState* David_DX_State::David_RSNoneCull_Solid = 0;
	ID3D11RasterizerState* David_DX_State::David_RSBackCull_WireFrame = 0;
	ID3D11RasterizerState* David_DX_State::David_RSFrontCull_WireFrame = 0;
	ID3D11RasterizerState* David_DX_State::David_RSNoneCull_WireFrame = 0;
	//
	ID3D11SamplerState*	David_DX_State::David_SSWrapLinear=NULL;
	ID3D11SamplerState*	David_DX_State::David_SSWrapPoint = NULL;
	//


	HRESULT David_DX_State::Create_States(ID3D11Device* pd3dDevice)
	{
		HRESULT hr;
		///////////////////////// blend //////////////
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; //The blend factor is (Aₛ, Aₛ, Aₛ, Aₛ), that is alpha data (A) from a pixel shader.
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;//The blend factor is ( 1 - Aₛ, 1 - Aₛ, 1 - Aₛ, 1 - Aₛ), that is alpha data (A) from a pixel shader.
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; //	Add source 1 and source 2.

		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; //The blend factor is (1, 1, 1, 1).
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; //The blend factor is (0, 0, 0, 0).
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; //Add source 1 and source 2.

		bd.RenderTarget[0].RenderTargetWriteMask = 	D3D11_COLOR_WRITE_ENABLE_ALL;

		pd3dDevice->CreateBlendState(&bd, &David_BSAlphaBlend);

		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO; // The blend factor is (0, 0, 0, 0). 
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; // The blend factor is (1, 1, 1, 1).
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // Add source 1 and source 2.

		hr = pd3dDevice->CreateBlendState(&bd, &David_BSNoBlend);

		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;// Add source 1 and source 2.;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;//The blend factor is (Rₛ, Gₛ, Bₛ, Aₛ), that is color data (RGB) from a pixel shader
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;// The blend factor is (1, 1, 1, 1). 
		pd3dDevice->CreateBlendState(&bd, &David_BS_Color_One);


	
		bd.AlphaToCoverageEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_MAX; //Find the maximum of source 1 and source 2.
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; //The blend factor is (1, 1, 1, 1).
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE; //The blend factor is (1, 1, 1, 1).

		pd3dDevice->CreateBlendState(&bd, &David_BS_AlphaMaxOneOne);





		/////////////////////////////
		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory(&dsd, sizeof(dsd));

		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&David_DSVStateDetphWriteDisable);

		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&David_DSVStateEnableLessEqual);

		dsd.DepthEnable = TRUE;
		dsd.DepthFunc = D3D11_COMPARISON_GREATER;
		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&David_DSVStateEnableGreater);


		dsd.DepthEnable = FALSE;
		hr = pd3dDevice->CreateDepthStencilState(
			&dsd,
			&David_DSVStateDisable);




		////////////////////////////////


		//////////////////////////////////
		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_BACK;
		rd.DepthClipEnable = TRUE;

		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSWireFrame);
		rd.FillMode = D3D11_FILL_SOLID;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSSolid);
		rd.CullMode = D3D11_CULL_FRONT;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSFrontCull_Solid);
		rd.CullMode = D3D11_CULL_BACK;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSBackCull_Solid);
		rd.CullMode = D3D11_CULL_NONE;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSNoneCull_Solid);

		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_FRONT;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSFrontCull_WireFrame);
		rd.CullMode = D3D11_CULL_BACK;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSBackCull_WireFrame);
		rd.CullMode = D3D11_CULL_NONE;
		hr = pd3dDevice->CreateRasterizerState(&rd,	&David_RSNoneCull_WireFrame);
		//////////////////////////////////
		
		D3D11_SAMPLER_DESC descSamp;
		descSamp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.MipLODBias = 0;
		descSamp.MaxAnisotropy = 16;	
		descSamp.ComparisonFunc = D3D11_COMPARISON_NEVER;

		descSamp.BorderColor[0] = 1.0f;
		descSamp.BorderColor[1] = 0.0f;
		descSamp.BorderColor[2] = 0.0f;
		descSamp.BorderColor[3] = 1.0f;
		descSamp.MinLOD = 0;
		descSamp.MaxLOD = D3D10_FLOAT32_MAX;
		

		descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		pd3dDevice->CreateSamplerState(&descSamp,&David_SSWrapLinear);


		descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		pd3dDevice->CreateSamplerState(&descSamp, &David_SSWrapPoint);
		
		return hr;
	}
	bool David_DX_State::Release()
	{
		if(David_DSVStateEnableLessEqual)David_DSVStateEnableLessEqual->Release();
		if(David_DSVStateEnableGreater) David_DSVStateEnableGreater->Release();
		if(David_RSWireFrame) David_RSWireFrame->Release();
		if(David_RSSolid) David_RSSolid->Release();
		if(David_RSBackCull_Solid) David_RSBackCull_Solid->Release();
		if(David_RSFrontCull_Solid) David_RSFrontCull_Solid->Release();
		if(David_RSNoneCull_Solid) David_RSNoneCull_Solid->Release();
		if(David_RSBackCull_WireFrame) David_RSBackCull_WireFrame->Release();
		if(David_RSFrontCull_WireFrame) David_RSFrontCull_WireFrame->Release();
		if(David_RSNoneCull_WireFrame) David_RSNoneCull_WireFrame->Release();
		if(David_BSNoBlend) David_BSNoBlend->Release();
		if(David_BS_AlphaMaxOneOne) David_BS_AlphaMaxOneOne->Release();
		if(David_BSAlphaBlend) David_BSAlphaBlend->Release();
		if(David_SSWrapLinear) David_SSWrapLinear->Release();
		return true;
	}

	David_DX_State::David_DX_State()
	{
		
	}


	David_DX_State::~David_DX_State()
	{
	}
}
