#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터를 만든다

enum MINIONTYPE
{
	MUMMY,
	GOLEM,
	ETC//원거리 적 뭐할지 안정해서 임시로
};

enum ENEMYTYPE {
	BOSS,
	MINION
};

enum STATE
{
	eIDLE=1,
	eWALK,
	eHIT,
	eATTACK1,
	eATTACK2,
	eGUARD,
	eDEAD
};

class enemy : public gameNode
{
private:
	image* _imageIdle;		//에너미 이미지
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//충돌용 렉트
	bool collision;		//충돌했는지 안했는지
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;

	int type;	
	MINIONTYPE _minionType;	//몹 종류
	STATE _state;

	//프레임 이미지를 돌리기 위한 변수
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//랜덤으로 총알발사 쿨타임 주기
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }
	void setCollision(bool set) { collision = set; }

	STATE getActionK() { return _state; }
	void setActionK(int pattern);

	int getAttCountK() { return _fireCount;}
	void setAttCountK(int fireCount) { _fireCount = fireCount; }
	enemy() {}
	~enemy() {}
};

