#pragma once
#include "gameNode.h"
/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
/*헤더파일만 메인게임에 추가하기*/
#include "startScene.h"
#include "inGameScene.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "pixelCollisionScene.h"
#include "soundTestScene.h"
#include "maptoolScene.h"


class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

