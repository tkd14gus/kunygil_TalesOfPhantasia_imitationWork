#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͸� �����

enum MINIONTYPE
{
	MUMMY,
	GOLEM,
	ETC//���Ÿ� �� ������ �����ؼ� �ӽ÷�
};

enum ENEMYTYPE {
	BOSS,
	MINION
};

enum STATE
{
	IDLE,
	WALK,
	HIT,
	ATTACK1,
	ATTACK2,
	GUARD,
	DEAD
};

class enemy : public gameNode
{
private:
	image* _imageIdle;		//���ʹ� �̹���
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//�浹�� ��Ʈ
	bool collision;		//�浹�ߴ��� ���ߴ���
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;

	int type;	
	MINIONTYPE _minionType;	//�� ����
	STATE _state;

	//������ �̹����� ������ ���� ����
	int _count;
	int _currentFrameX;
	int _currentFrameY;

	//�������� �Ѿ˹߻� ��Ÿ�� �ֱ�
	int _fireCount;
	int _rndFireConut;

public:
	HRESULT init();
	HRESULT init(POINT position);
	void release();
	void update();
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

	bool bulletCountFire();

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }
	void setCollision(bool set) { collision = set; }

	enemy() {}
	~enemy() {}
};
