#pragma once
#include "gameNode.h"
#include "minion.h"  //미니언 클래스 사용하기 위해
#include "bullet.h"	 //공용총알 클래스 사용하기 위해

//상호참조용 클래스 전방선언
class player;

class enemyManager : public gameNode
{
private:
	player* _player;

private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	//vector<enemy*> _vBoss;
	bullet* _bullet; //공용총알 클래스
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//미니언 세팅 => 초기화에 넣는다
	void setMinion();
	//미니언 총알발사
	void minionBulletFire();
	//미니언 삭제
	void removeMinion(int index);

	//미니언 벡터 가져오기
	vector<enemy*> getMinion() { return _vMinion; }

	//충돌함수 (미니언들의 총알들, 플레이어)
	void collision();

	//상호참조시 플레이어 포인터를 받을 셋터함수
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

