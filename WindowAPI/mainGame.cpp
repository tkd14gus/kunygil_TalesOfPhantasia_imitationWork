#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//클래스 초기화를 이곳에서 한다
	
	/*앞으로 메인게임은 가각의 씬들만 관리를 한다*/
	//각각의 씬들은 메인게임 역할을 한다

	/*씬추가*/
	SCENEMANAGER->addScene("시작화면", new startScene);
	SCENEMANAGER->addScene("게임화면", new inGameScene);
	SCENEMANAGER->addScene("INI테스트", new iniTestScene);
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	SCENEMANAGER->addScene("픽셀충돌", new pixelCollisionScene);
	SCENEMANAGER->addScene("사운드", new soundTestScene);
	SCENEMANAGER->addScene("맵툴기초", new maptoolScene);
	

	/*현재씬 설정*/
	SCENEMANAGER->loadScene("맵툴기초");


	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	
	
	//글자색 배경 없애기
	SetBkMode(getMemDC(), TRANSPARENT);
	//씬매니져 렌더
	SCENEMANAGER->render();

//=============================================================
	//백버퍼의 내용을 화면DC에 그린다
	this->getBackBuffer()->render(getHDC());
}
