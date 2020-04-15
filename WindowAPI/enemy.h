#pragma once
#include "gameNode.h"

//�θ�Ŭ���� => �̳��� ��ӹ޾Ƽ� ����, �Ϲݸ��͸� �����

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
	 
	virtual void move() = 0;		//������Ʈ
	virtual void draw() = 0;		//����
	virtual void animation() = 0;	//������Ʈ
	 
	virtual bool bulletCountFire() = 0;
	 
	 //�浹�� ��Ʈ ��������
	virtual RECT getRect() = 0;					//���� ��ü ��Ʈ
	virtual RECT getAtt() = 0; 			//���� ���� ��Ʈ
	virtual int getAttCd() = 0;				//���� ���� ��Ÿ��
	virtual void setCollision(bool set) = 0;
	 
	virtual ENEMYTYPE getEnemyType() = 0;					//���� ������Ű���Լ�
	virtual STATE getActionK() = 0;							//���º��������� �Լ�
	virtual void setActionK(int pattern) = 0;			   					//���º��������� �Լ�
	 
	virtual int getAttCountK() = 0;					//����->���� ��Ÿ�Ӽ���������
	virtual void setAttCountK(int fireCount) = 0;	//����->���� ��Ÿ�Ӽ���������
	
	virtual bool getHitAtt() = 0;						//��Ʈ ����������
	virtual void setHitAtt(bool hit) = 0;					//��Ʈ ����������
	
	virtual int getCountK() = 0;							//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�
	virtual void setCountK(int count) = 0;				//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�
	 
	virtual int getHpMax() = 0;				//��������
	virtual int getHpK() = 0;
	virtual void setHpK(int hp) = 0;

	virtual int getEnemyX() = 0;				//���� ĳ���Ͱ� ���� ����
	virtual void setLeft(bool isLeft) = 0;				//���� �¿� ����

	enemy() {}
	virtual ~enemy() {}
};
class mummy : public enemy
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
	bool _isLeft;		//�¿�����
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;

	ENEMYTYPE _type;	//�� ����
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
	void update(int playerViewX);
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

	bool bulletCountFire();

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }					//���� ��ü ��Ʈ
	RECT getAtt() { return _attRcK; }				//���� ���� ��Ʈ
	int getAttCd() { return _attCd; }				//���� ���� ��Ÿ��
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
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

	int getEnemyX(){ return playerX; }								//���� ĳ���Ͱ� ���� ����
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//���� �¿� ����

	mummy() {}
	~mummy() {}
};

class golem : public enemy
{
private:
	image* _imageIdle;		//���ʹ� �̹���
	image* _imageWalk;
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2;
	image* _imageGuard;
	//image* _imageDead;

	RECT _rc;			//�浹�� ��Ʈ(���ͺ�ü)
	RECT _attRcK;			//���ݿ� ��Ʈ
	int _hp;			//ü��
	bool _hitAtt;		//������ ��ȿ�Ҷ� On �¾Ѱų� ��ǳ�����off
	bool collision;		//�浹�ߴ��� ���ߴ���
	bool _isLeft;		//�¿�����
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;
	ENEMYTYPE _type;	//�� ����
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
	void update(int playerViewX);
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

	bool bulletCountFire();

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }					//���� ��ü ��Ʈ
	RECT getAtt() { return _attRcK; }				//���� ���� ��Ʈ
	int getAttCd() { return _attCd; }				//���� ���� ��Ÿ��
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
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

	int getEnemyX() { return playerX; }								//���� ĳ���Ͱ� ���� ����
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//���� �¿� ����

	golem() {}
	~golem() {}
};


class jamir : public enemy
{
private:
	image* _imageIdle;		//���ʹ� �̹���
	image* _imageWalk;	
	image* _imageHit;
	image* _imageAttack1;
	image* _imageAttack2; //Dash
	image* _imageGuard;
	image* _imageDead;

	RECT _rc;			//�浹�� ��Ʈ(���ͺ�ü)
	RECT _attRcK;			//���ݿ� ��Ʈ
	int _hp;			//ü��
	int _hpMax;
	bool _hitAtt;		//������ ��ȿ�Ҷ� On �¾Ѱų� ��ǳ�����off
	bool collision;		//�浹�ߴ��� ���ߴ���
	bool _isLeft;		//�¿�����
	int playerX;
	int playerY;
	int playerWidth;
	int playerheight;
	int type;
	int _attCd;

	ENEMYTYPE _type;	//�� ����
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
	void update(int playerViewX);
	void render();

	virtual void move();		//������Ʈ
	virtual void draw();		//����
	virtual void animation();	//������Ʈ

	bool bulletCountFire();

	//�浹�� ��Ʈ ��������
	RECT getRect() { return _rc; }					//���� ��ü ��Ʈ
	RECT getAtt() { return _attRcK; }				//���� ���� ��Ʈ
	int getAttCd() { return _attCd; }				//���� ���� ��Ÿ��
	void setCollision(bool set) { collision = set; }

	ENEMYTYPE getEnemyType() { return _type; }
	STATE getActionK() { return _state; }							//���º��������� �Լ�
	void setActionK(int pattern);				   					//���º��������� �Լ�

	int getAttCountK() { return _fireCount; }						//����->���� ��Ÿ�Ӽ���������
	void setAttCountK(int fireCount) { _fireCount = fireCount; }	//����->���� ��Ÿ�Ӽ���������

	bool getHitAtt() { return _hitAtt; }							//��Ʈ ����������
	void setHitAtt(bool hit) { _hitAtt = hit; }						//��Ʈ ����������

	int getCountK() { return _count; }								//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�
	void setCountK(int count) { _count = count; }					//�ܺ� �ڱ����κ��� ����� ������ 0���� �ؾ��ϴ� ���¸� ���� �Լ�

	int getHpMax() { return _hpMax; }
	int getHpK() { return _hp; }
	void setHpK(int hp) { _hp = hp; }

	int getEnemyX() { return playerX; }								//���� ĳ���Ͱ� ���� ����
	void setLeft(bool isLeft) { _isLeft = isLeft; }					//���� �¿� ����

	jamir() {}
	~jamir() {}
};