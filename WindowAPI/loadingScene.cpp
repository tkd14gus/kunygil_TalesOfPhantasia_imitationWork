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

	
	//��׶��� �̹��� �ʱ�ȭ
	//IMAGEMANAGER->addImage("��׶���", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO ������ �̹��� �ʱ�ȭ
	//IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//�Ѿ� �̹���
	//IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ �����
	
	//#====================================================================================================================#
	//#									�� Ÿ��																			   #
	//#									���� �ȸ����� �����ϴ�															   #
	//#====================================================================================================================#
	_loading->loadFrameImage("map1", "map/citytile.bmp", 160, 96, 10, 6); //Ÿ�� 10x6 �̹ؿ� �ٸ�Ÿ�� �߰����� �� 
	//#====================================================================================================================#


	//#====================================================================================================================#
	//#									UI �̹���																		   #
	//#====================================================================================================================#
	_loading->loadImage("FrameLT", "Images/UI/FrameLT.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameRT", "Images/UI/FrameRT.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameLB", "Images/UI/FrameLB.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameRB", "Images/UI/FrameRB.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	
	
	_loading->loadImage("FrameL", "Images/UI/FrameL.bmp", 17, 275);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameR", "Images/UI/FrameR.bmp", 17, 275);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameT", "Images/UI/FrameT.bmp", 575, 17);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameB", "Images/UI/FrameB.bmp", 575, 17);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 		   
	//#====================================================================================================================#

}

//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
}
