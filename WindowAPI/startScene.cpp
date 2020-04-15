#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//��Ʈ ��ġ �ʱ�ȭ
	_rc[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 300, 350, 35);
	_rc[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 350, 35);

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
			SCENEMANAGER->loadScene("����ȭ��");
		}
		if (PtInRect(&_rc[1], _ptMouse))
		{
			SCENEMANAGER->loadScene("��������");
		}
	}

}

void startScene::render()
{
	IMAGEMANAGER->findImage("startBackGround")->render(getMemDC());


	if (PtInRect(&_rc[0], _ptMouse))
		IMAGEMANAGER->findImage("gameStartOn")->render(getMemDC(), _rc[0].left, _rc[0].top);
	else 
		IMAGEMANAGER->findImage("gameStartOff")->render(getMemDC(), _rc[0].left, _rc[0].top);

	RECT rc = RectMake(_rc[1].left + 35, _rc[1].top, 350 - 70, 35);
	if (PtInRect(&rc, _ptMouse))
		IMAGEMANAGER->findImage("mapToolOn")->render(getMemDC(), _rc[1].left, _rc[1].top);
	else
		IMAGEMANAGER->findImage("mapToolOff")->render(getMemDC(), _rc[1].left, _rc[1].top);
}
