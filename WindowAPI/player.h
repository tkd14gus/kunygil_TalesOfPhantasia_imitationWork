#pragma once
#include "gameNode.h"

enum tagstate
{
	pIDLE,
	pDEAD,
	pRUN,
	pWALK,
	pJUMP,
	pATTACK,
	pGUARD,
	pWIN
};

struct tagPlayer
{
	bool sight;	 //�÷��̾� �ð�(0 - ����, 1 - ������)
	int lv;				//�÷��̾� LV
	int maxHp, hp;		 //�÷��̾� hp
	int maxTp, tp;		// �÷��̾� tp
	int attXK, attYK;
	float x, y;    //�÷��̾� ��ǥ
	float inGameX, inGameY;	//������ �ƴ϶� �ΰ��� ������ �� ��ǥ
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

	RECT rc;  //�÷��̾� �浹 �簢��

	RECT attack;      //���� �浹 �簢��
	//RECT jumpAttack;  //���� �浹 �簢��
	//float atkTime;
};
class player : public gameNode
{
private:
	//������ �̹��� 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

private:
	RECT _stage;		//����
	RECT _playerDoorRc;	// �÷��̾ ���� ��Ҵ��� Ȯ�����ִ� ��Ʈ
	float _enemyCenterX, _enemyCenterY;		//�簢�� �߾�

	//float _immoTime;		//�浹�� �����ð�

	//�±� ����
	tagstate _state;

	int _direct;		// �÷��̾ ������ ���� �ִ���
						//0: ��, 1: �Ʒ�, 2: ��, 3: ��

	bool _isBattle;	//�÷��̾ ���� ��Ʋ������ �ƴ���

public:

	HRESULT init();
	void release();
	void update();
	void render();



	//float getenemyCenterx() { return _enemyCenterX; }
	//float getenemyCentery() { return _enemyCenterY; }
	//RECT getenemyRect() { return _TESTenemy; }

	//enum�±� ��ȭ�� ���� ���ϴ� �÷��̾� ���
	void animation();
	tagPlayer* getPlayer() { return &_player; }
	void setPlayer(tagPlayer player) { _player = player; }

	//�÷��̾��� X,Y��ǥ�� �ֱ����� get�Լ�
	float getPlayerX() { return _player.inGameX; }
	float getPlayerY() { return _player.inGameY; }
	//���� �̵����� �� �÷��̾��� ��ġ�� ��������� �ϹǷ� set���� �÷��̾��� x,y���� ��Ʈ���� �ٲ��ش�.
	void setPlayerRect(int x, int y);
	//����â�� ������ �� �̹����� ��� �����̷��� pWALK���¿��� �ϹǷ� ���¸� �ٲ���� �Ѵ�.
	void setPlayerState(tagstate state) { _state = state; }
	//����â�� ���� ���� ������ �� ���� ���� �ٶ󺸰� �־�� �ϴ� ������ ����������Ѵ�.
	int getDirect() { return _direct; }
	//�׸��� ���� ���� �־�� �Ѵ�.
	void setDirect(int direct) { _direct = direct; }
	//�÷��̾��� ��Ʈ�� �ֱ����� get�Լ�
	RECT getPlayerRc() { return _player.rc; }
	//�÷��̾ �� ��ó�� �ִ��� Ȯ���ϱ� ���� get�Լ�
	RECT getPlayerDoorRc() { return _playerDoorRc; }

	// �÷��̾� ����ü�� �ʱ�ȭ �ϴ� �Լ�
	void settingTagPlayer();
	// �÷��̾� ���Ʈ �÷��̾� ��ġ�� ���� ��ġ�� �������ִ� �Լ�.
	void settingPlayerDoorRect();
	// ������Ʈ â Ʋ���� �� ĳ���Ͱ� ȸ���ϴ� �̹���
	void spinPlayer();


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

