#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
#include "startScene.h"
#include "inGameScene.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "pixelCollisionScene.h"
#include "soundTestScene.h"
#include "maptoolScene.h"
#include "battleScene.h"
#include "storeScene.h"

//�ӽ÷� �־��
#include "store.h"


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

