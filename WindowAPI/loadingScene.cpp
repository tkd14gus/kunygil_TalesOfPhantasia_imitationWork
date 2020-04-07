#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("픽셀충돌");
	}
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();
}


//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	/*
	//백그라운드 이미지 초기화
	IMAGEMANAGER->addImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지 초기화
	IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	*/
	_loading->loadImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	_loading->loadImage("bullet", "Images/bullet.bmp", 21, 21);

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("ball", "ball.bmp", 60, 60);
}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
