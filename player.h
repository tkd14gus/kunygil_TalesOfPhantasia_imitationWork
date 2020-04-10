#pragma once
#include "gameNode.h"

enum tagstate
{
	IDLE,
	DEAD,
	RUN,
	WALK,
	JUMP,
	ATTACK,
	GUARD,
	WIN
};

struct tagPlayer
{
	bool sight;	 //�÷��̾� �ð�(0 - ����, 1 - ������)
	int hp;		 //�÷��̾� hp
	float x, y;    //�÷��̾� ��ǥ
	float speed;
	float gravity;  //�߷°�

	image* idle;
	image * walk;
	image* run;
	image* guard;

	image* atkSlash;
	image* atkstab;
	image* atkshot;
	image* atkmelee;
	image* jump;

	image * dead;
	image* win;

	RECT player;  //�÷��̾� �浹 �簢��

	RECT attack;      //���� �浹 �簢��
	RECT jumpAttack;  //���� �浹 �簢��
	float atkTime;
};
class player : public gameNode
{
private:
	//������ �̹��� 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;


	//�����浹 �׽�Ʈ
	RECT _TESTenemy;
	float _enemyX, _enemyY;
	int _enemyHP;

	//private:
	//	bool _sight;	 //�÷��̾� �ð�(0 - ����, 1 - ������)
	//	int _hp;		 //�÷��̾� hp
	//	float _x, _y;    //�÷��̾� ��ǥ
	//	float _speed;
	//	float _gravity;  //�߷°�
	//
	//private:
	//	image* _idle;
	//	image * _walk;
	//	image* _run;
	//	image* _guard;
	//
	//	image* _atkSlash;
	//	image* _atkstab;
	//	image* _jump;
	//	
	//	image * _dead;
	//	image* _win;

private:
	RECT _rcPlayer;		//�÷��̾� �浹 �簢��
	RECT _stage;		//����
	float _enemyCenterX, _enemyCenterY;		//�簢�� �߾�

	float _immoTime;		//�浹�� �����ð�

	//�±� ����
	tagstate _state;

public:

	HRESULT init();
	void release();
	void update();
	void render();



	float getenemyCenterx() { return _enemyCenterX; }
	float getenemyCentery() { return _enemyCenterY; }
	RECT getenemyRect() { return _TESTenemy; }

	//enum�±� ��ȭ�� ���� ���ϴ� �÷��̾� ���
	void animation();


	player() {}
	~player() {}
};

class subplayer : public gameNode
{
private:
	//������ �̹��� 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

	player* _mainplayer;

	//private:
	//	bool _sight;	 //�÷��̾� �ð�(0 - ����, 1 - ������)
	//	int _hp;		 //�÷��̾� hp
	//	float _x, _y;    //�÷��̾� ��ǥ
	//	float _speed;
	//	float _gravity;  //�߷°�
	//
	//private:
	//	image* _idle;
	//	image * _walk;
	//	image* _run;
	//	image* _guard;
	//
	//	image* _atkSlash;
	//	image* _atkstab;
	//	image* _jump;
	//	
	//	image * _dead;
	//	image* _win;

private:
	RECT _rcPlayer;		//�÷��̾� �浹 �簢��
	float _chargeTime;	//ȭ�� ���� �ð�

	float _distance;	//ai�� ���� �Ÿ�
	float _cX, _cY;		//ai�簢�� �߾�
	float _speed;		//ȭ��ӵ�

	RECT _arrow;		//ȭ�� �簢��
	image* _arrowImg;		//ȭ�� �簢��
	bool _arrowIs;		//ȭ�� ���󰡴¿���
	bool _melee;		//�������ݿ���

	//�±� ����
	tagstate _state;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	//enum�±� ��ȭ�� ���� ���ϴ� �÷��̾� ���
	void animation();


	subplayer() {}
	~subplayer() {}
};

