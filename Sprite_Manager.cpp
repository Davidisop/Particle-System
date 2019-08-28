#include "Sprite_Manager.h"

Sprite_Manager* Sprite_Manager::uniqueInstance_ptr = nullptr;

void	Sprite_Manager::SetDevice(ID3D11Device* pDevice)
{
	m_pd3Device = pDevice;
}

int		Sprite_Manager::Add(ID3D11Device* pDevice,
	const TCHAR* pTextureFileName,
	const TCHAR* pShaderFileName,
	ID3D11BlendState* m_pBlendState ,
	bool bInstancing)
{
	TCHAR szFileName[MAX_PATH]; memset(szFileName, 0, sizeof(TCHAR)*MAX_PATH);
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];

	if (pTextureFileName) // 이걸 텍스쳐로 한다고?? 스프라이트 이름이 아니라?? 왜 그러지?
	{
		_tsplitpath_s(pTextureFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);//// 버퍼에 합쳐 저장하기

		for (Sprite_TemplateMap_Itor itor = Sprite_Map.begin(); itor != Sprite_Map.end(); itor++)
		{
			Sprite *pPoint = (*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))//스프라이트 매니져에 같은게 기존에 있다면,
				//아... 스프라이트 매니져도, "한 텍스쳐" 당 한 개 = 스프라이트도 "한 텍스쳐당" 한 개구나....(?) : 여러장 스프라이트도 첫장만 등록하면 될듯.
			{
				return (*itor).first;// 이 스프라이트 인덱스 (스프라이트 매니저에 등록된) 를 반환. 함수종료
			}
		}
	}


	// 텍스쳐 이름은 넘어왔는데, 기존의 것과 같은 게 없으면

	Sprite *pPoint = nullptr;
	pPoint = new Sprite;
	pPoint->m_szPath = Dir;

	// Sprite Create 및 Load기능.
	if(FAILED(pPoint->Load(pDevice, pShaderFileName, pTextureFileName, bInstancing, m_pBlendState)))
	{
		//실패하면 삭제한다.
		pPoint->Release();
		delete pPoint;
		pPoint = nullptr;
		return false;
	}

	else // Sprite Create 및 Load기능. 성공하면,
	{
		// David : 스프라이트 거르는 무언가를 추가
		if(wcslen(szFileName) !=0) { pPoint->m_szName = szFileName; }
		//
		Sprite_Map.insert(make_pair(++Current_Index, pPoint)); //방금 만든 스프라이트를 Pipe Create 후, 스프라이트 매니저에 넣는다.
		pPoint->m_iIndex_in_spriteManager = Current_Index;
		
		return pPoint->m_iIndex_in_spriteManager;
		// 이 스프라이트 인덱스 (스프라이트 매니저에 등록된) 를 반환.
	}
}


Sprite* const Sprite_Manager::GetPtr(int iIndex)
{
	Sprite_TemplateMap_Itor itor = Sprite_Map.find(iIndex);

	if (itor == Sprite_Map.end()) 
	
	{
		//Sprite* pPoint = nullptr;
		
		return nullptr;}// 못찾으면 그냥 nullptr 반환.

	else if(itor != Sprite_Map.end())//찾으면,
	{
		Sprite* pPoint = (*itor).second;
		
		return pPoint; // 해당 스프라이트 ptr 반환.
	}
}


bool	Sprite_Manager::Release()
{
	Sprite* pPoint;
	for (Sprite_TemplateMap_Itor itor = Sprite_Map.begin(); itor != Sprite_Map.end(); itor++)
	{
		pPoint = (*itor).second; //스프라이트 맵 안의 모든 스프라이트 Release()한다.
		pPoint->Release();  // 근데 문제는 ㅋㅋ David_Shape까지 내려간다는거.. ㅋㅋ 스프라이트 클래스에 해당함수가 없다.
		delete pPoint;
		pPoint = nullptr;
	}
	Sprite_Map.clear();//MAP전체를 비운다.
	Current_Index = 0;
	return true;
}



bool Sprite_Manager::Delete(int iIndex)
{
	Sprite* const pPoint = GetPtr(iIndex);
	if (pPoint != nullptr)
	{
		pPoint->Release();
		Sprite_Map.erase(iIndex);
	}

	return true;
};

Sprite_Manager::Sprite_Manager()
{
	m_pd3Device = nullptr;
	Current_Index = 0;
	Sprite_Map.clear();
}


Sprite_Manager::~Sprite_Manager()
{

	Sprite* pPoint;
	for (Sprite_TemplateMap_Itor itor = Sprite_Map.begin(); itor != Sprite_Map.end(); itor++)
	{
		pPoint = (*itor).second; //스프라이트 맵 안의 모든 스프라이트 Release()한다.
		pPoint->Release();  // 근데 문제는 ㅋㅋ David_Shape까지 내려간다는거.. ㅋㅋ 스프라이트 클래스에 해당함수가 없다.
		delete pPoint;
		pPoint = nullptr;
	}
	Sprite_Map.clear();//MAP전체를 비운다.
	Current_Index = 0;

}
