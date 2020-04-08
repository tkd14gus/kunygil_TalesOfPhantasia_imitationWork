#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	bool _tileSetting;
	bool _canMove;
	char _fileName[128];	//파일 이름(맵, 맵 데이터)을 받아올 변수
	int _startFile;			/*파일 명은 0번부터 시작
							ex) MAP0.map	MAP0.mapdata
							*/
	unsigned int _palettePage;
	bool _layer[3];
private:
	tagTile _tiles[TILEX * TILEY];	//인게임화면에 사용되는 타일 총 400개
	tagSampleTile _sampleTile[60]; //샘플타일 총 (12-2)*6 = 60개
	tagCurrentTile _currentTile;	//현재타일
private:
	RECT _rcScreen;		//화면 카메라 Rect;
						//이 Rect와 충돌한 타일만 화면에 그려진다.
	RECT _rcArrow[2];	//샘플타일을 변경할 화살표를 그려주는 Rect
						//0번 : LeftArrow, 1번 : RightArrow
	RECT _rcPalette;	//샘플타일을 그려줄 Rect;
	RECT _rcSave;		//세이브
	RECT _rcLoad;		//로드
	RECT _rcTerrain;	//지형
	RECT _rcObject;		//오브젝트
	RECT _rcEraser;		//지우개(오브젝트만 지운다, 지형은 덮어씌운다)

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//맵툴세팅
	void maptoolSetup();
	void setMap();
	void uiMove();
	void save();
	void load();

	void selectLayer1();
	void selectLayer2();
	void selectLayer3();

	//지형, 오브젝트 세터
	TERRAIN terrainSelect(int frameX, int frameY, int page);

	maptoolScene() {}
	~maptoolScene() {}
};

