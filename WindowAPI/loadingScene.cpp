#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//�ε�Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�ε� �̹��� �� ���� �ʱ�ȭ
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//�ε�Ŭ���� ����
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��Ϸ��� ȭ�� ����
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("��������");
	}
}

void loadingScene::render()
{
	//�ε�Ŭ���� ����
	_loading->render();
}


//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//��׶��� �̹��� �ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO ������ �̹��� �ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	_loading->loadImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	for (int i = 0; i < 1; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("ball", "ball.bmp", 60, 60);

	_loading->loadFrameImage("citytile", "map/citytile.bmp", 160, 96, 10, 6);
}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
}
