#pragma once
#include "gameNode.h"
#include "player.h"
#include "tileNode.h"

class inGameScene : public gameNode
{
private:
	player* _player; //플레이어 클래스
	subplayer* _subPlayer;
private:
	tagTile _tiles[TILEX * TILEY];	//인게임화면에 사용되는 타일 총 400개
	RECT _rcScreen;		//화면 카메라 Rect;
						//이 Rect와 충돌한 타일만 화면에 그려진다.
	RECT rc;			//IntersectRect하기 위해 만드는 빈 렉트

	RECT _stateRC[4];	//state를 켰을 때 캐릭터창 하나를 담당하는 렉트
private:

	int _mapLocation;	// 현재 가져와야 하는 맵이 무엇인지
						// 0이면 마을
						// 1이면 필드
						// 2이면 집안

	char _fileName[128] = { 0, };	//맵 파일의 이름을 받아올 변수

	char _stateWin[128];			//스테이터 창에서 TextOut할 것을 모두 여기에 담아두고 사용한다.

	bool _isStateWinOpen;			// 상태창을 켰는지 확인하는 함수

	int _saveDirect;				//player클래스의 _direct를 저장할 함수
									//상태창에 들어갔다 나올때 같은 곳을 바라볼 수 있게 하기 위한 장치


public:
	HRESULT init();
	void release();
	void update();
	void render();

	inGameScene() {}
	~inGameScene() {}

	//_mapLocation을 받아 맵을 셋팅해주는 함수.
	void mapSetting(int mapLocation);
	//맵 넘어가는 함수
	//void changeMap();

	//타일이 플레이어 위치에 맞게 조정해주는 함수
	void tileSetting();
	//필드일 때 확률적으로 배틀씬으로 넘어가는 함수
	void changeBattleScene();
};



