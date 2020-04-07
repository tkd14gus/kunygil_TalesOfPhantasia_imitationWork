#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init()
{
	return S_OK;
}

void iniTestScene::release()
{
}

void iniTestScene::update()
{
	//세이브
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류
		INIDATA->addData("플밍19기", "민본", "100.99");
		INIDATA->addData("플밍19기", "승윤", "1");
		INIDATA->addData("플밍19기", "승윤", "10");

		//이와 같은 방법도 가능
		//다만 인자로 char*를 받고 있기때문에 string을 char*형태로 변경해줘야 함
		vector<string> vStr;
		vStr.push_back("50.5");
		vStr.push_back("111");
		vStr.push_back("7");

		INIDATA->addData("플레이어", "공격력", vStr[0].c_str());
		INIDATA->addData("플레이어", "방어력", vStr[1].c_str());

		//파일 이름으로 세이브
		INIDATA->saveINI("플밍플밍");
	}
	//로드
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("플밍플밍", "플밍19기", "민본");
		cout << num << endl;
	}
}

void iniTestScene::render()
{
}
