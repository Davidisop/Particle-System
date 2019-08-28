#include "TextureManager.h"

David_TextureManager* David_TextureManager::uniqueInstance_ptr = nullptr;


HRESULT	David_Texture::Load_Get_SRV(ID3D11Device* pDevice, const TCHAR* str_FileName)//strFilePath����  str_FileName�� ���� �����߽��ϴ�.
{ 
	//���� ��ΰ� �ܺο��� �־�����,

	if (str_FileName == NULL) return S_OK;
	HRESULT hr = S_OK;
	TCHAR sz_merged_FileName[MAX_PATH] = { 0, };
	_stprintf_s(sz_merged_FileName, _T("%s%s"), Da_szPath.c_str(), str_FileName);
	// ���ۿ� ���� �����ϱ�._stprintf_s(m_csBuffer, L"FPS:%d TIME:%10.4f SPF:%10.4f", m_dwFPS, m_fGameTimer, m_fSecPerFrame);
	
	Da_szName = str_FileName; // �� ���� Path�� ���ΰ�?
	Da_merged_path_name = sz_merged_FileName;

	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));

	loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadInfo.Format = DXGI_FORMAT_FROM_FILE;//����.

	hr = D3DX11CreateShaderResourceViewFromFile(pDevice, sz_merged_FileName, &loadInfo, NULL, &m_pTextureSRV, NULL);

	if (FAILED(hr))//hr�� �����ϸ�,
	{
		return hr;
	}
	return hr;
}


bool David_Texture::Apply_thisSRV_to_PipeLine(ID3D11DeviceContext* pImmedateContext)
{
	pImmedateContext->PSSetShaderResources(0, 1, &m_pTextureSRV);
	//pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);
	return true;
}

bool David_Texture::Release()
{
	m_pTextureSRV->Release(); m_pTextureSRV = nullptr;
	m_pSamplerState->Release(); m_pSamplerState = nullptr;
	return true;
}

bool David_Texture::Set_to_MyPath(const TCHAR* pPath)
{
	Da_szPath = pPath;
	return true;
}

David_Texture::David_Texture(void)
{
	m_pTextureSRV = nullptr;
	m_pSamplerState = nullptr;
	Da_szPath = _T("");
	Da_merged_path_name = _T("");
}


David_Texture::~David_Texture(void)
{

}


int	David_TextureManager::ADD(ID3D11Device* pDedvice, const TCHAR* pFileName) //�ܺο��� ������ ���� �̸�.
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];



	if (pFileName) 
	{//���� �Ͱ� ���� �� ������, �� �ε��� ��ȯ.
		_tsplitpath(pFileName, Drive, Dir, FName, Ext); // �̸��� ������ �ɰ���.
		Ext[4] = 0; //5��° ���Ҹ� 0���� �Ѵ�.	���ڿ� ������ ���(\0 = NULL ���� ����)
		
		memset(szFileName, 0, sizeof(TCHAR)*MAX_PATH); //szFileName �޸𸮹ٸ� 0���� ä���ִ´�.

		if (!_tcsicmp(Ext, _T(".tga"))) //������ 0��ȯ.
		{
			_tcscpy(Ext, _T(".bmp"));//���ڿ������. �׷� bmp�� �� ���̴�.
		}
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);
		//���ۿ� ���� �����ϱ�.

		for (Texture_Map_Itor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			//TemplateMap  map<int, David_TextureManager*> TMap
			David_Texture *pPoint = (David_Texture*)(*itor).second;//itor���� second�����ߴ�.

			if (!_tcsicmp(pPoint->Da_szName.c_str(), szFileName)) ////�ܺο��� ������ ���� �̸�. ������ �̸��� ��ġ�ϴ� �� Ȯ���Ѵ�.
			{   ////������ 0��ȯ.
				return (*itor).first; // map ������ִ� ������ �ε��� ��ȣ ��ȯ�Ѵ�. ������ �����ص����� ��� ����ض�. �̷� ���ε�.
			}
		}
	}

	//���� �Ͱ� ���� �� ������, ���� ����� �ε��� ��ȯ.

	David_Texture *pdPoint;
	pdPoint = new David_Texture;

	TCHAR szPath[MAX_PATH] = { 0, };
	
	_stprintf_s(szPath, _T("%s%s"), Drive, Dir);// �տ��� �ɰ��� ����Ǿ��� �͵���, ���ۿ� ���� �����ϱ�.
	pdPoint->Set_to_MyPath(szPath);

	if(FAILED(pdPoint->Load_Get_SRV(pDedvice, szFileName)))
	{
		return 0;//SRV ����� �� �����ϸ�, 0��ȯ.
	}
	//SRV����� �� ����������, MAP�� �����ϰ�, �� �ε����� ��ȯ�մϴ�.

	TMap[++m_iCurIndex]= pdPoint;

	return m_iCurIndex;
}

int David_TextureManager::ADD(ID3D11Device* pDevice, const TCHAR* pFileName, const TCHAR* szpath)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	if (pFileName)
	{

		_tsplitpath(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;//�ټ���ĭ���� ���ڿ� �� Null����
		memset(szFileName, 0, sizeof(TCHAR)*MAX_PATH);// szFileName�� �ϴ� �� Null���ڷ� ä����

		if (_tcsicmp(Ext, _T(".tga")) == 0)//������, �ٲ��.
		{
			_tcscpy(Ext, _T(".dds"));
		}
		_stprintf_s(szFileName, _T("%s,%s"), FName, Ext);// ���ۿ� ���� �����ϱ�.

		for (Texture_Map_Itor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			David_Texture* pPoint = (David_Texture*)(*itor).second;
		
			if (!_tcsicmp(pPoint->Da_szName.c_str(), szFileName))
			{
				return (*itor).first;//���� ����� ���� �˻��ؼ�, ������, �߰� �ʿ� ������, �׳� �� �ؽ��� �ε����� ��ȯ�ϰ�, �� �Լ� ��!
			}
		}
	}

	David_Texture* pPoint = NULL;
	pPoint = new David_Texture;
	pPoint->Set_to_MyPath(szpath);

	if(FAILED(pPoint->Load_Get_SRV(pDevice, szFileName)))
	{
		return 0; // 
	}
	
	TMap[++m_iCurIndex] = pPoint;//�� 1������ �ؽ��� ����ȴ�.
	return m_iCurIndex;
}

David_Texture* const David_TextureManager::Getptr(int iIndex)
{
	Texture_Map_Itor itor = TMap.find(iIndex);
	if (itor == TMap.end()) return nullptr; //���� end���� ���� �ʽ��ϴ�.
	else
	{
		David_Texture* pPoint = (*itor).second;
		return pPoint;
	}
}

David_Texture* const David_TextureManager::Getptr(T_STR strFindName)
{
	for (Texture_Map_Itor itor = TMap.begin(); itor != TMap.end(); itor++)//�ѹ��� �� ����
	{
		David_Texture* pPoint = (David_Texture*)(*itor).second;
		if (pPoint->Da_szName == strFindName)
		{
			return(*itor).second;
		}
	}
	//�̸� ���� �� �� ã����,
	return nullptr;

}



bool David_TextureManager::Release()
{
	David_Texture* pPoint;

	for (Texture_Map_Itor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		pPoint = (David_Texture*)(*itor).second;
		pPoint->Release();
	}
	TMap.clear();
	return true;
}


David_TextureManager::David_TextureManager()
{

	m_pd3Device = nullptr;
	m_iCurIndex = 0;
	TMap.clear();

}

David_TextureManager::~David_TextureManager()
{
	David_Texture* pPoint;

	for (Texture_Map_Itor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		pPoint = (David_Texture*)(*itor).second;
		pPoint->Release();
	}
	TMap.clear();
	m_iCurIndex = 0;
}
