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
		//SCENEMANAGER->loadScene("����ȭ��");
		SCENEMANAGER->loadScene("��������");
		//SCENEMANAGER->loadScene("����ȭ��");
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

	//_loading->loadFrameImage("layer", "Images/UI/layer.bmp", 384, 96, 3, 1);

	//#====================================================================================================================#
	//#									�� Ÿ��																			   #
	//#									���� �ȸ����� �����ϴ�															   #
	//#====================================================================================================================#

	//Ÿ�� 10x6 �̹ؿ� �ٸ�Ÿ�� �߰����� �� 
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
	_loading->loadFrameImage("map47", "map/indoortile (3).bmp", 160, 96, 10, 6);

	_loading->loadFrameImage("map48", "map/interior (1).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map49", "map/interior (2).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map50", "map/interior (3).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map51", "map/interior (4).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map52", "map/interior (5).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map53", "map/interior (6).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map54", "map/interior (7).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map55", "map/interior (8).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map56", "map/interior (9).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map57", "map/interior (10).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map58", "map/interior (11).bmp", 160, 96, 10, 6);

	_loading->loadFrameImage("map59", "map/interior (12).bmp", 160, 96, 10, 6);

	_loading->loadFrameImage("map60", "map/cityObject (1).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map61", "map/cityObject (2).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map62", "map/cityObject (3).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map63", "map/cityObject (4).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map64", "map/cityObject (5).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map65", "map/cityObject (6).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map66", "map/cityObject (7).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map67", "map/cityObject (8).bmp", 160, 96, 10, 6);
	_loading->loadFrameImage("map68", "map/cityObject (9).bmp", 160, 96, 10, 6);

	_loading->loadFrameImage("map69", "map/citytile.bmp", 160, 96, 10, 6);

	//#====================================================================================================================#
	//#									UI �̹���																		   #
	//#====================================================================================================================#
	_loading->loadImage("FrameLT", "Images/UI/FrameLT.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameRT", "Images/UI/FrameRT.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameLB", "Images/UI/FrameLB.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	_loading->loadImage("FrameRB", "Images/UI/FrameRB.bmp", 17, 17);	 //������ �𼭸��κ� Ű����� �����Ϸ��� ����� ��
	

	_loading->loadImage("FrameL", "Images/UI/FrameL.bmp", 17, 800);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameR", "Images/UI/FrameR.bmp", 17, 800);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameT", "Images/UI/FrameT.bmp", 600, 17);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 
	_loading->loadImage("FrameB", "Images/UI/FrameB.bmp", 600, 17);		 //�����ε�� �Լ��� ���ϴ¸�ŭ�� ©�� ���� 		 

	_loading->loadImage("activeYes", "Images/UI/activeYes.bmp", 50, 50);
	_loading->loadImage("deactiveYes", "Images/UI/deactiveYes.bmp", 50, 50);
	_loading->loadImage("activeNo", "Images/UI/activeNo.bmp", 50, 50);
	_loading->loadImage("deactiveNo", "Images/UI/deactiveNo.bmp", 50, 50);
	
	
	_loading->loadImage("save", "Images/UI/save.bmp", 81, 36);
	_loading->loadImage("load", "Images/UI/load.bmp", 81, 36);
	_loading->loadImage("textbox", "Images/UI/textbox.bmp", 600, 800);
	_loading->loadImage("activetextbox", "Images/UI/activetextbox.bmp", 600, 800);
	_loading->loadImage("accountbox", "Images/UI/accountbox.bmp", 600, 300);			//��������

	//#====================================================================================================================#
	//#									Layer �� ǥ�� �̹���																   #
	//#====================================================================================================================#
	_loading->loadFrameImage("Layer", "Images/UI/layer.bmp", 384, 96, 3, 1);

	//#====================================================================================================================#
	//#									��ư �̹���																		   #
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
	_loading->loadImage("Eraser", "Images/UI/Eraser.bmp", 96, 48);
	_loading->loadImage("slide", "Images/UI/slide.bmp", 96, 48);
	_loading->loadImage("slideOff", "Images/UI/slide_off.bmp", 96, 48);
	_loading->loadImage("inGame", "Images/UI/inGame.bmp", 96, 48);
	_loading->loadImage("inGameOff", "Images/UI/inGame_off.bmp", 96, 48);

	_loading->loadImage("leftArrow", "Images\\UI\\Arrow0.bmp", 48, 48);
	_loading->loadImage("rightArrow", "Images\\UI\\Arrow1.bmp", 48, 48);
	_loading->loadImage("leftArrow5", "Images\\UI\\Arrow5_0.bmp", 48, 48);
	_loading->loadImage("rightArrow5", "Images\\UI\\Arrow5_1.bmp", 48, 48);

	//#====================================================================================================================#
	//#									UI �̹��� ����																	   #
	//#====================================================================================================================#

	//#====================================================================================================================#
	//#									Battle bg																		   #
	//#====================================================================================================================#

	//_loading->loadImage("commonbattlebg","Images/battlebackground/commonbattlebg",2000,433);

	//#====================================================================================================================#
	//#								Charicter, Enemy �̹���																   #
	//#====================================================================================================================#
	
	
	//#================================ M U M M Y =========================================================================#	

	_loading->loadFrameImage("mummydead", "Images/enemy/mummy/dead.bmp", 64 * 2, 46 * 4, 1, 2);
	_loading->loadFrameImage("mummyguard", "Images/enemy/mummy/guard.bmp", 64 * 2, 46 * 4, 1, 2);
	_loading->loadFrameImage("mummyhit", "Images/enemy/mummy/hit.bmp", 64 * 2, 46 * 4, 1, 2);
	_loading->loadFrameImage("mummyidle", "Images/enemy/mummy/idle.bmp", 64 * 2, 46 * 4, 1, 2);

	_loading->loadFrameImage("mummyatt1", "Images/enemy/mummy/attack1.bmp", 320 * 2, 46 * 4, 5, 2);
	_loading->loadFrameImage("mummyatt2", "Images/enemy/mummy/attack2.bmp", 256 * 2, 46 * 4, 4, 2);
	_loading->loadFrameImage("mummywalk", "Images/enemy/mummy/walk.bmp", 192 * 2, 46 * 4, 3, 2);

	//#================================ G O L E M =========================================================================#	

	_loading->loadFrameImage("golemguard", "Images/enemy/golem/guard.bmp", 80 * 2, 63 * 4, 1, 2);
	_loading->loadFrameImage("golemhit", "Images/enemy/golem/hit.bmp", 80 * 2, 63 * 4, 1, 2);
	_loading->loadFrameImage("golemidle", "Images/enemy/golem/idle.bmp", 80 * 2, 63 * 4, 1, 2);

	_loading->loadFrameImage("golematt1", "Images/enemy/golem/attack1.bmp", 240 * 2, 63 * 4, 3, 2);
	_loading->loadFrameImage("golematt2", "Images/enemy/golem/attack2.bmp", 160 * 2, 63 * 4, 2, 2);
	_loading->loadFrameImage("golemwalk", "Images/enemy/golem/walk.bmp", 240 * 2, 63 * 4, 3, 2);


	//#====================================================================================================================#
	//#									inGameScene�ȿ��� ���� �̹���															   #
	//#====================================================================================================================#
	_loading->loadFrameImage("cress", "Images/inGameSprite/cress.bmp", 320, 512, 5, 4);
	_loading->loadImage("stateWindow", "Images/inGameSprite/stateWIndow.bmp", WINSIZEX, WINSIZEY);

}


//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound()
{
}
