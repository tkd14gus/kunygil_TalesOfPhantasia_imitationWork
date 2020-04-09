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
		SCENEMANAGER->loadScene("맵툴기초");
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

	
	//백그라운드 이미지 초기화
	//IMAGEMANAGER->addImage("백그라운드", "Images/background.bmp", WINSIZEX, WINSIZEY);
	//UFO 프레임 이미지 초기화
	//IMAGEMANAGER->addFrameImage("ufo", "Images/ufo.bmp", 530, 32, 10, 1);
	//총알 이미지
	//IMAGEMANAGER->addImage("bullet", "Images/bullet.bmp", 21, 21);
	

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기


	//#====================================================================================================================#
	//#									맵 타일																			   #
	//#									서식 안맞으면 터집니다															   #
	//#====================================================================================================================#
	_loading->loadFrameImage("map1", "map/citytile.bmp", 160, 96, 10, 6); //타일 10x6 이밑에 다른타일 추가해줄 것 
	//#====================================================================================================================#


	//#====================================================================================================================#
	//#									UI 이미지																		   #
	//#====================================================================================================================#
	_loading->loadImage("FrameLT", "Images/UI/FrameLT.bmp", 17, 17);	 //프레임 모서리부분 키우려면 스케일랜더 사용할 것
	_loading->loadImage("FrameRT", "Images/UI/FrameRT.bmp", 17, 17);	 //프레임 모서리부분 키우려면 스케일랜더 사용할 것
	_loading->loadImage("FrameLB", "Images/UI/FrameLB.bmp", 17, 17);	 //프레임 모서리부분 키우려면 스케일랜더 사용할 것
	_loading->loadImage("FrameRB", "Images/UI/FrameRB.bmp", 17, 17);	 //프레임 모서리부분 키우려면 스케일랜더 사용할 것
	

	_loading->loadImage("FrameL", "Images/UI/FrameL.bmp", 17, 800);		 //오버로드된 함수로 원하는만큼만 짤라서 랜더 
	_loading->loadImage("FrameR", "Images/UI/FrameR.bmp", 17, 800);		 //오버로드된 함수로 원하는만큼만 짤라서 랜더 
	_loading->loadImage("FrameT", "Images/UI/FrameT.bmp", 600, 17);		 //오버로드된 함수로 원하는만큼만 짤라서 랜더 
	_loading->loadImage("FrameB", "Images/UI/FrameB.bmp", 600, 17);		 //오버로드된 함수로 원하는만큼만 짤라서 랜더 		 

	_loading->loadImage("activeYes", "Images/UI/activeYes.bmp", 50, 50);
	_loading->loadImage("deactiveYes", "Images/UI/deactiveYes.bmp", 50, 50);
	_loading->loadImage("activeNo", "Images/UI/activeNo.bmp", 50, 50);
	_loading->loadImage("deactiveNo", "Images/UI/deactiveNo.bmp", 50, 50);
	
	
	_loading->loadImage("save", "Images/UI/save.bmp", 81, 36);
	_loading->loadImage("load", "Images/UI/load.bmp", 81, 36);
	_loading->loadImage("textbox", "Images/UI/textbox.bmp", 600, 800);
	_loading->loadImage("activetextbox", "Images/UI/activetextbox.bmp", 600, 800);

	
	//#====================================================================================================================#

}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
