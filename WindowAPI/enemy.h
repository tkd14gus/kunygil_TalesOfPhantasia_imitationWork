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
	eIDLE = 1,
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
	image* _imageIdle;		//���ʹ� �̹���
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//�浹�� ��Ʈ(���ͺ�ü)
	RECT _attRcK;			//���ݿ� ��Ʈ
	int _hp;			//ü��
	bool _hitAtt;		//������ ��ȿ�Ҷ� On �¾Ѱų� ��ǳ�����off
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
	RECT getRect() { return _rc; }					//���� ��ü ��Ʈ
	RECT getAtt() { return _attRcK; }				//���� ���� ��Ʈ
	void setCollision(bool set) { collision = set; }

	STATE getActionK() { return _state; }							//���º��������� �Լ�
	void setActionK(int pattern);				   					//���º��������� �Լ�

	int getAttCountK() { return _fireCount; }						//����->���� ��Ÿ�Ӽ���������
	void setAttCountK(int fireCount) { _fireCount = fireCount; }	//����->���� ��Ÿ�Ӽ���������

	bool getHitAtt() { return _hitAtt; }							//��Ʈ ����������
	void setHitAtt(bool hit) { _hitAtt = hit; }						//��Ʈ ����������

	int getCountK() { return _count; }								//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�
	void setCountK(int count) { _count = count; }					//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�

	int getHpK() { return _hp; }
	void setHpK(int hp) { _hp = hp; }

	enemy() {}
	~enemy() {}
};

