#include "stdafx.h"
#include "soundTestScene.h"

HRESULT soundTestScene::init()
{
	//���� �߰�
	SOUNDMANAGER->addSound("����1", "���.mp3");
	SOUNDMANAGER->addSound("����2", "���1.mp3");

	SOUNDMANAGER->play("����1");

	return S_OK;
}

void soundTestScene::release()
{
}

void soundTestScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (SOUNDMANAGER->isPlaySound("����1"))
		{
			SOUNDMANAGER->stop("����1");
		}
		SOUNDMANAGER->play("����2");
	}

}

void soundTestScene::render()
{
	textOut(getMemDC(), 10, 10, "�����׽�Ʈ");
}
