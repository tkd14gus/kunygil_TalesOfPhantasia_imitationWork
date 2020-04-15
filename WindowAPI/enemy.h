#pragma once
#include "gameNode.h"

//부모클래스 => 이놈을 상속받아서 보스, 일반몬스터를 만든다

enum ENEMYTYPE
{
	MUMMY,
	GOLEM,
	JAMIR
};

enum STATE
{
	eIDLE = 1,
	eHIT,
	eWALK, //JAMIR = Dash
	eATTACK1,
	eATTACK2, 
	eGUARD,
	eDEAD
};
class enemy : public gameNode
{
public:
	virtual HRESULT init()=0;
	virtual HRESULT init(POINT position) = 0;
	virtual void release() = 0;
	virtual void update(int playerViewX) = 0;
	virtual void render() = 0;
	 
	virtual void move() = 0;		//업데이트
	virtual void draw() = 0;		//렌더
	virtual void animation() = 0;	//업데이트
	 
	virtual bool bulletCountFire() = 0;
	 
	 //충돌용 렉트 가져오기
	virtual RECT getRect() = 0;					//몬스터 본체 렉트
	virtual RECT getAtt() = 0; 			//몬스터 어택 렉트
	virtual int getAttCd() = 0;				//몬스터 어택 쿨타임
	virtual void setCollision(bool set) = 0;
	 
	virtual ENEMYTYPE getEnemyType() = 0;					//몬스터 구별시키는함수
	virtual STATE getActionK() = 0;							//상태변경을위한 함수
	virtual void setActionK(int pattern) = 0;			   					//상태변경을위한 함수
	 
	virtual int getAttCountK() = 0;					//조우->공격 쿨타임설정을위함
	virtual void setAttCountK(int fireCount) = 0;	//조우->공격 쿨타임설정을위함
	
	virtual bool getHitAtt() = 0;						//히트 판정을위함
	virtual void setHitAtt(bool hit) = 0;					//히트 판정을위함
	
	virtual int getCountK() = 0;							//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수
	virtual void setCountK(int count) = 0;				//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수
	 
	virtual int getHpMax() = 0;				//보스전용
	virtual int getHpK() = 0;
	virtual void setHpK(int hp) = 0;

	virtual int getEnemyX() = 0;				//몬스터 캐릭터간 방향 설정
	virtual void setLeft(bool isLeft) = 0;				//몬스터 좌우 설정

	enemy() {}
	virtual ~enemy() {}
};
class mummy : public enemy
{
private:
	image* _imageIdle;		//에너미 이미지
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//충돌용 렉트(몬스터본체)
	RECT _attRcK;			//공격용 렉트
	int _hp;			//체력
	bool _hitAtt;		//공격이 유효할때 On 맞앗거나 모션끝나면off
	bool collision;		//충돌했는지 안했는지
	bool _isLeft;		//좌우판정
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;

	ENEMYTYPE _type;	//몹 종류
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
	void update(int playerViewX);
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }					//몬스터 본체 렉트
	RECT getAtt() { return _attRcK; }				//몬스터 어택 렉트
	int getAttCd() { return _attCd; }				//몬스터 어택 쿨타임
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
	STATE getActionK() { return _state; }							//상태변경을위한 함수
	void setActionK(int pattern);				   					//상태변경을위한 함수

	int getAttCountK() { return _fireCount; }						//조우->공격 쿨타임설정을위함
	void setAttCountK(int fireCount) { _fireCount = fireCount; }	//조우->공격 쿨타임설정을위함

	bool getHitAtt() { return _hitAtt; }							//히트 판정을위함
	void setHitAtt(bool hit) { _hitAtt = hit; }						//히트 판정을위함

	int getCountK() { return _count; }								//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수
	void setCountK(int count) { _count = count; }					//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수

	int getHpK() { return _hp; }
	void setHpK(int hp) { _hp = hp; }

	int getEnemyX(){ return playerX; }								//몬스터 캐릭터간 방향 설정
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//몬스터 좌우 설정

	mummy() {}
	~mummy() {}
};

class golem : public enemy
{
private:
	image* _imageIdle;		//에너미 이미지
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	//image* _imageDead;

	RECT _rc;			//충돌용 렉트(몬스터본체)
	RECT _attRcK;			//공격용 렉트
	int _hp;			//체력
	bool _hitAtt;		//공격이 유효할때 On 맞앗거나 모션끝나면off
	bool collision;		//충돌했는지 안했는지
	bool _isLeft;		//좌우판정
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;
	ENEMYTYPE _type;	//몹 종류
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
	void update(int playerViewX);
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }					//몬스터 본체 렉트
	RECT getAtt() { return _attRcK; }				//몬스터 어택 렉트
	int getAttCd() { return _attCd; }				//몬스터 어택 쿨타임
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
	STATE getActionK() { return _state; }							//상태변경을위한 함수
	void setActionK(int pattern);				   					//상태변경을위한 함수

	int getAttCountK() { return _fireCount; }						//조우->공격 쿨타임설정을위함
	void setAttCountK(int fireCount) { _fireCount = fireCount; }	//조우->공격 쿨타임설정을위함

	bool getHitAtt() { return _hitAtt; }							//히트 판정을위함
	void setHitAtt(bool hit) { _hitAtt = hit; }						//히트 판정을위함

	int getCountK() { return _count; }								//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수
	void setCountK(int count) { _count = count; }					//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수


	int getHpK() { return _hp; }
	void setHpK(int hp) { _hp = hp; }

	int getEnemyX() { return playerX; }								//몬스터 캐릭터간 방향 설정
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//몬스터 좌우 설정

	golem() {}
	~golem() {}
};


class jamir : public enemy
{
private:
	image* _imageIdle;		//에너미 이미지
	image* _imageWalk;	
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2; //Dash
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//충돌용 렉트(몬스터본체)
	RECT _attRcK;			//공격용 렉트
	int _hp;			//체력
	int _hpMax;
	bool _hitAtt;		//공격이 유효할때 On 맞앗거나 모션끝나면off
	bool collision;		//충돌했는지 안했는지
	bool _isLeft;		//좌우판정
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;

	ENEMYTYPE _type;	//몹 종류
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
	void update(int playerViewX);
	void render();

	virtual void move();		//업데이트
	virtual void draw();		//렌더
	virtual void animation();	//업데이트

	bool bulletCountFire();

	//충돌용 렉트 가져오기
	RECT getRect() { return _rc; }					//몬스터 본체 렉트
	RECT getAtt() { return _attRcK; }				//몬스터 어택 렉트
	int getAttCd() { return _attCd; }				//몬스터 어택 쿨타임
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
	STATE getActionK() { return _state; }							//상태변경을위한 함수
	void setActionK(int pattern);				   					//상태변경을위한 함수

	int getAttCountK() { return _fireCount; }						//조우->공격 쿨타임설정을위함
	void setAttCountK(int fireCount) { _fireCount = fireCount; }	//조우->공격 쿨타임설정을위함

	bool getHitAtt() { return _hitAtt; }							//히트 판정을위함
	void setHitAtt(bool hit) { _hitAtt = hit; }						//히트 판정을위함

	int getCountK() { return _count; }								//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수
	void setCountK(int count) { _count = count; }					//외부 자극으로부터 모션을 무조건 0부터 해야하는 상태를 위한 함수

	int getHpMax() { return _hpMax; }
	int getHpK() { return _hp; }
	void setHpK(int hp) { _hp = hp; }

	int getEnemyX() { return playerX; }								//몬스터 캐릭터간 방향 설정
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//몬스터 좌우 설정

	jamir() {}
	~jamir() {}
};