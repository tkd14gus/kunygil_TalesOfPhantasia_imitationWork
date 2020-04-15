#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 300, 200, 50);
	_rc[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 200, 50);

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc[0], _ptMouse))
		{
			SCENEMANAGER->loadScene("게임화면");
		}
		if (PtInRect(&_rc[1], _ptMouse))
		{
			SCENEMANAGER->loadScene("맵툴기초");
		}
	}

}

void startScene::render()
{
	IMAGEMANAGER->findImage("startBackGround")->render(getMemDC());

	Rectangle(getMemDC(), _rc[0]);
	Rectangle(getMemDC(), _rc[1]);
	//중앙정렬
	SetTextAlign(getMemDC(), TA_CENTER);
	TextOut(getMemDC(), WINSIZEX / 2, _rc[0].top + 15, "START", strlen("START"));

	TextOut(getMemDC(), WINSIZEX / 2, _rc[1].top + 15, "MAP_TOOL", strlen("MAP_TOOL"));
	//원상복구
	SetTextAlign(getMemDC(), TA_LEFT);
}
