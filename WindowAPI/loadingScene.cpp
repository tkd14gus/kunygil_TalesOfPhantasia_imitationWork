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
		//SCENEMANAGER->loadScene("게임화면");
		//SCENEMANAGER->loadScene("맵툴기초");
		//SCENEMANAGER->loadScene("전투화면");
		SCENEMANAGER->loadScene("시작화면");
		//SCENEMANAGER->loadScene("상점화면임시");
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
	_loading->loadImage("accountbox", "Images/UI/accountbox.bmp", 600, 300);			//전투씬용

	_loading->loadImage("box", "Images/UI/box.bmp", 580,480);

	//캐릭터,몬스터이름
	_loading->loadImage("Tcress", "Images/UI/inbattle/Cress.bmp", 98, 18);
	_loading->loadImage("Tchester", "Images/UI/inbattle/Chester.bmp", 138, 18);
	_loading->loadImage("Tmummy", "Images/UI/inbattle/Mummy.bmp",90,18);
	_loading->loadImage("Tgolem", "Images/UI/inbattle/Golem.bmp",90,18);
	_loading->loadImage("Tjamir", "Images/UI/inbattle/Jamir.bmp",90,18);
	_loading->loadImage("Thp", "Images/UI/inbattle/hp.bmp",36,18);


	_loading->loadFrameImage("number", "Images/UI/inbattle/Numbers.bmp", 80*2, 8*2, 10, 1);
	//텍스트박스용 숫자
	//for (int i = 0; i < 10; i++)
	//{
	//	char str[32];
	//	char strr[64];
	//
	//	sprintf_s(str, "num%d", i);
	//	sprintf_s(strr, "Images/UI/inbattle/num%d.bmp", i);
	//
	//	_loading->loadImage(str, strr, 16, 16);
	//
	//}

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
	_loading->loadImage("Eraser", "Images/UI/Eraser.bmp", 96, 48);
	_loading->loadImage("slide", "Images/UI/slide.bmp", 96, 48);
	_loading->loadImage("slideOff", "Images/UI/slide_off.bmp", 96, 48);
	_loading->loadImage("inGame", "Images/UI/inGame.bmp", 96, 48);
	_loading->loadImage("inGameOff", "Images/UI/inGame_off.bmp", 96, 48);

	_loading->loadImage("leftArrow", "Images\\UI\\Arrow0.bmp", 48, 48);
	_loading->loadImage("rightArrow", "Images\\UI\\Arrow1.bmp", 48, 48);
	_loading->loadImage("leftArrow5", "Images\\UI\\Arrow5_0.bmp", 48, 48);
	_loading->loadImage("rightArrow5", "Images\\UI\\Arrow5_1.bmp", 48, 48);

	_loading->loadImage("weapon", "Images/UI/weapon.bmp", 133, 45);
	_loading->loadImage("weapon_off", "Images/UI/weapon_off.bmp", 133, 45);
	_loading->loadImage("armor", "Images/UI/armor.bmp", 133, 45);
	_loading->loadImage("armor_off", "Images/UI/armor_off.bmp", 133, 45);
	_loading->loadImage("ring", "Images/UI/ring.bmp", 133, 45);
	_loading->loadImage("ring_off", "Images/UI/ring_off.bmp", 133, 45);
	_loading->loadImage("portion", "Images/UI/portion.bmp", 133, 45);
	_loading->loadImage("portion_off", "Images/UI/portion_off.bmp", 133, 45);

	//#====================================================================================================================#
	//#									UI 이미지 종료																	   #
	//#====================================================================================================================#

	//#====================================================================================================================#
	//#									Battle bg																		   #
	//#====================================================================================================================#

	_loading->loadImage("commonbattle","Images/battlebackground/commonbattle.bmp",2000,500);
	_loading->loadImage("commonbattlebg","Images/battlebackground/commonbattlebg.bmp",2000,433);
	_loading->loadImage("bossbattle","Images/battlebackground/bossbattle.bmp",2000,500);
	_loading->loadImage("bossbattlebg","Images/battlebackground/bossbattlebg.bmp",2000,433);
	//_loading->loadImage("commonbattlebg","Images/battlebackground/commonbattlebg",2000,433);

	//#====================================================================================================================#
	//#								Charicter, Enemy 이미지																   #
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


	//#================================ J A M I R =========================================================================#	

	_loading->loadFrameImage("jamirdead", "Images/enemy/jamir/dead.bmp", 81 * 2, 60 * 4, 1, 2);
	_loading->loadFrameImage("jamirguard", "Images/enemy/jamir/guard.bmp", 81 * 2, 60 * 4, 1, 2);
	_loading->loadFrameImage("jamirhit", "Images/enemy/jamir/hit.bmp", 81 * 2, 60 * 4, 1, 2);
							  
	_loading->loadFrameImage("jamiridle", "Images/enemy/jamir/idle.bmp", 81 * 4 * 2, 60 * 4, 4, 2);
	_loading->loadFrameImage("jamirdash", "Images/enemy/jamir/dash.bmp", 81 * 5 * 2, 60 * 4, 5, 2);
	_loading->loadFrameImage("jamiratt", "Images/enemy/jamir/attack.bmp", 81 * 5 * 2, 60 * 4, 5, 2);
	_loading->loadFrameImage("jamirskill", "Images/enemy/jamir/skill.bmp", 81 * 8 * 2, 60 * 2, 8, 1); 

	//#====================================================================================================================#
	//#									inGameScene안에서 쓰일 이미지															   #
	//#====================================================================================================================#
	_loading->loadFrameImage("cress", "Images/inGameSprite/cress.bmp", 320, 512, 5, 4);
	_loading->loadImage("stateWindow", "Images/inGameSprite/stateWIndow.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("backGround_Back", "Image/background/backGround_back.bmp", WINSIZEX * 3, WINSIZEY);

	//#====================================================================================================================#
	//#									인벤/상점용 이미지															   #
	//#====================================================================================================================#
	_loading->loadImage("armorName (0)", "Images/itemInfo/armorName (0).bmp", 200, 20, true, RGB(255, 0, 255));
	_loading->loadImage("portionName (0)", "Images/itemInfo/portionName (0).bmp", 200, 20, true, RGB(255, 0, 255));
	_loading->loadImage("ringName (0)", "Images/itemInfo/ringName (0).bmp", 200, 20, true, RGB(255, 0, 255));
	_loading->loadImage("weaponName (0)", "Images/itemInfo/weaponName (0).bmp", 200, 20, true, RGB(255, 0, 255));
	_loading->loadImage("armorImage (0)", "Images/itemInfo/armorImage (0).bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("portionImage (0)", "Images/itemInfo/portionImage (0).bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("ringImage (0)", "Images/itemInfo/ringImage (0).bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("weaponImage (0)", "Images/itemInfo/weaponImage (0).bmp", 100, 100, true, RGB(255, 0, 255));
	_loading->loadImage("armorAttribute (0)", "Images/itemInfo/armorAttribute (0).bmp", 350, 35, true, RGB(255, 0, 255));
	_loading->loadImage("portionAttribute (0)", "Images/itemInfo/portionAttribute (0).bmp", 350, 35, true, RGB(255, 0, 255));
	_loading->loadImage("ringAttribute (0)", "Images/itemInfo/ringAttribute (0).bmp", 350, 35, true, RGB(255, 0, 255));
	_loading->loadImage("weaponAttribute (0)", "Images/itemInfo/weaponAttribute (0).bmp", 350, 35, true, RGB(255, 0, 255));

	_loading->loadImage("weaponG", "Images/itemInfo/weapon.bmp", 133, 45, true, RGB(255, 0, 255));
	_loading->loadImage("armorG", "Images/itemInfo/armor.bmp", 133, 45, true, RGB(255, 0, 255));
	_loading->loadImage("ringG", "Images/itemInfo/ring.bmp", 133, 45, true, RGB(255, 0, 255));
	_loading->loadImage("portionG", "Images/itemInfo/portion.bmp", 133, 45, true, RGB(255, 0, 255));

	_loading->loadImage("gold", "Images/itemInfo/gold.bmp", 64, 20, true, RGB(255, 0, 255));
	_loading->loadImage("total", "Images/itemInfo/total.bmp", 80, 20, true, RGB(255, 0, 255));


	_loading->loadImage("0", "Images/itemInfo/0.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("1", "Images/itemInfo/1.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("2", "Images/itemInfo/2.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("3", "Images/itemInfo/3.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("4", "Images/itemInfo/4.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("5", "Images/itemInfo/5.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("6", "Images/itemInfo/6.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("7", "Images/itemInfo/7.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("8", "Images/itemInfo/8.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("9", "Images/itemInfo/9.bmp", 20, 20, true, RGB(255, 0, 255));
	_loading->loadImage("x", "Images/itemInfo/x.bmp", 20, 20, true, RGB(255, 0, 255));
	//#====================================================================================================================#
	//#									startSceneUI																	   #
	//#====================================================================================================================#
	_loading->loadImage("startBackGround", "Images/startUI/startBackGround.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("gameStartOff", "Images/startUI/gameStartOff.bmp", 350, 35);
	_loading->loadImage("gameStartOn", "Images/startUI/gameStartOn.bmp", 350, 35);
	_loading->loadImage("mapToolOff", "Images/startUI/mapToolOff.bmp", 350, 35);
	_loading->loadImage("mapToolOn", "Images/startUI/mapToolOn.bmp", 350, 35);
	//#====================================================================================================================#
	//#									loadingBackGround																   #
	//#====================================================================================================================#
	//_loading->loadImage("loadingBackGround", "Images/loadingBackGround.bmp", WINSIZEX, WINSIZEY);
}


//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound()
{
}
