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

	//_loading->loadFrameImage("layer", "Images/UI/layer.bmp", 384, 96, 3, 1);

	//#====================================================================================================================#
	//#									맵 타일																			   #
	//#									서식 안맞으면 터집니다															   #
	//#====================================================================================================================#
	//타일 10x6 이밑에 다른타일 추가해줄 것 
	_loading->loadFrameImage("map1", "map/castleObject (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map2", "map/castleObject (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map3", "map/castleObject (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map4", "map/castleObject (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map5", "map/castleObject (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map6", "map/castleObject (6).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map7", "map/castleObject (7).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map8", "map/castleObject (8).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map9", "map/castleObject (9).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map10", "map/castleObject (10).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map11", "map/castleObject (11).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map12", "map/castleObject (12).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map13", "map/castletile (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map14", "map/castletile (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map15", "map/castletile (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map16", "map/castletile (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map17", "map/castletile (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map18", "map/castletile (6).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map19", "map/castletile (7).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map20", "map/castletile (8).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map21", "map/castletile (9).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map22", "map/fieldObject (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map23", "map/fieldObject (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map24", "map/fieldObject (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map25", "map/fieldObject (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map26", "map/fieldObject (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map27", "map/fieldObject (6).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map28", "map/fieldtile (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map29", "map/fieldtile (2).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map30", "map/indoorObject (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map31", "map/indoorObject (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map32", "map/indoorObject (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map33", "map/indoorObject (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map34", "map/indoorObject (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map35", "map/indoorObject (6).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map36", "map/indoorObject (7).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map37", "map/indoorObject (8).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map38", "map/indoorObject (9).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map39", "map/indoorObject (10).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map40", "map/indoorObject (11).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map41", "map/indoorObject (12).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map42", "map/indoorObject (13).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map43", "map/indoorObject (14).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map44", "map/indoorObject (15).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map45", "map/indoortile (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map46", "map/indoortile (2).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map47", "map/interior (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map48", "map/interior (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map49", "map/interior (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map50", "map/interior (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map51", "map/interior (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map52", "map/interior (6).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map53", "map/interior (7).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map54", "map/interior (8).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map55", "map/interior (9).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map56", "map/interior (10).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map57", "map/interior (11).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map58", "map/interior (12).bmp", 160, 96, 10, 6); 

	_loading->loadFrameImage("map59", "map/cityObject (1).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map60", "map/cityObject (2).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map61", "map/cityObject (3).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map62", "map/cityObject (4).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map63", "map/cityObject (5).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map64", "map/cityObject (6).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map65", "map/cityObject (7).bmp", 160, 96, 10, 6); 
	_loading->loadFrameImage("map66", "map/cityObject (7).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map67", "map/cityObject (8).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map68", "map/cityObject (9).bmp", 160, 96, 10, 6);

	_loading->loadFrameImage("map69", "map/citytile.bmp", 160, 96, 10, 6);
	


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
	//#									Layer 층 표시 이미지																   #
	//#====================================================================================================================#
	_loading->loadFrameImage("Layer", "Images/UI/layer.bmp", 384, 96, 3, 1);
	
	//#====================================================================================================================#
	//#									버튼 이미지																		   #
	//#====================================================================================================================#
	_loading->loadImage("Eraser", "Images/UI/erase_off.bmp", 96, 48);
	_loading->loadImage("EraserOff", "Images/UI/erase.bmp", 96, 48);
	_loading->loadImage("saveLoad", "Images/UI/saveLoad.bmp", 96, 48);
	_loading->loadImage("saveLoadOff", "Images/UI/saveLoad_off.bmp", 96, 48);
	_loading->loadImage("terrain", "Images/UI/terrain.bmp", 96, 48);
	_loading->loadImage("terrainOff", "Images/UI/terrain_off.bmp", 96, 48);
	//_loading->loadImage("object", "Images/UI/object.bmp", 96, 48);
	//_loading->loadImage("objectOff", "Images/UI/object_off.bmp", 96, 48);
	_loading->loadImage("home", "Images/UI/home.bmp", 96, 48);
	_loading->loadImage("homeoff", "Images/UI/home_off.bmp", 96, 48);
	_loading->loadImage("slide", "Images/UI/slide.bmp", 96, 48);
	_loading->loadImage("slideOff", "Images/UI/slide_off.bmp", 96, 48);
	_loading->loadImage("inGame", "Images/UI/inGame.bmp", 96, 48);
	_loading->loadImage("inGameOff", "Images/UI/inGame_off.bmp", 96, 48);

	//#====================================================================================================================#
	//#									UI 이미지 종료																	   #
	//#====================================================================================================================#
	


	//#====================================================================================================================#
	//#								Charicter, Enemy 이미지																   #
	//#====================================================================================================================#
	_loading->loadImage("mummydead", "Images/enemy/mummy/dead.bmp", 64*2,46*2);
	_loading->loadImage("mummyguard", "Images/enemy/mummy/guard.bmp",64*2,46*2);
	_loading->loadImage("mummyhit", "Images/enemy/mummy/hit.bmp", 64*2,46*2);
	_loading->loadImage("mummyidle", "Images/enemy/mummy/idle.bmp", 64*2,46*2);

	_loading->loadFrameImage("mummyatt1", "Images/enemy/mummy/attack1.bmp", 320*2, 46*2, 5, 1);
	_loading->loadFrameImage("mummyatt2", "Images/enemy/mummy/attack2.bmp", 256*2, 46*2, 4, 1);
	_loading->loadFrameImage("mummywalk", "Images/enemy/mummy/walk.bmp", 192*2, 46*2, 3, 1);
	//#====================================================================================================================#
	//#									inGameScene안에서 쓰일 이미지															   #
	//#====================================================================================================================#
	_loading->loadFrameImage("cress", "Images/inGameSprite/cress.bmp", 320, 512, 5, 4);

}

//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
