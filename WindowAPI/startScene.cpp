#include "stdafx.h"
#include "startScene.h"

HRESULT startScene::init()
{
	//��Ʈ ��ġ �ʱ�ȭ
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

	Rectangle(getMemDC(), _rc[0]);
	Rectangle(getMemDC(), _rc[1]);
	//�߾�����
	SetTextAlign(getMemDC(), TA_CENTER);
	TextOut(getMemDC(), WINSIZEX / 2, _rc[0].top + 15, "START", strlen("START"));

	TextOut(getMemDC(), WINSIZEX / 2, _rc[1].top + 15, "MAP_TOOL", strlen("MAP_TOOL"));
	//���󺹱�
	SetTextAlign(getMemDC(), TA_LEFT);
}
