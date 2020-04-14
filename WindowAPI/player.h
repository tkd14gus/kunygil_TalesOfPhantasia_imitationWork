#pragma once
#include "gameNode.h"


enum tagstate
{
	pIDLE,		//���
	pRUN,		//�޸���
	pHIT,		//�±�
	pWALK,		//�ȱ�
	pJUMP,		//����
	pATTACK,	//����
	pGUARD,		//���
	pDEAD,		//���
	pWIN		//�¸�
};

struct ARROW	//ȭ�� ����ü
{
	bool _bShoot;		//ȭ���� �߻��ߴ��� �Ǵ�
	float _speed;		//ȭ���� ���ư��� �ӵ�
	float _chargeTime;	//ȭ�� ���� �ð�

	POINT _point;	//ȭ���� �ʱ� (x, y) ��ǥ
	RECT _rc;		//ȭ�� Rect
	image* _img;	//ȭ�� �̹���
};

struct tagPlayer
{
	bool sight;			//�÷��̾� �ð�(0 - ����, 1 - ������)
	int lv;				//�÷��̾� LV
	int maxHp, hp;		//�÷��̾� hp
	int maxTp, tp;		// �÷��̾� tp
	int attXK, attYK;		//<-���� �������� Ȯ�� �ʿ�
	int viewX;				//���������Ѱ�

	float x, y;				//�÷��̾� ��ǥ
	float inGameX, inGameY;	//������ �ƴ϶� �ΰ��� ������ �� ��ǥ
	float speed;			//�÷��̾� �̵��ӵ�
	float gravity;			//�߷°�

	image* idle;	//��� �̹���
	image* walk;	//�ȱ� �̹���
	image* run;		//�޸��� �̹���
	image* guard;	//��� �̹���

	image* atkSlash;	
	image* atkstab;
	image* atkshot;		//���Ÿ� ���� �̹���
	image* atkmelee;	//���� ���� �̹���
	image* jump;		//���� �̹���

	image* hit;			//��Ʈ ��� �߰� - ���κ�
	image* dead;		//��� �̹���
	image* win;			//�¸� �̹���


	RECT cameraRc;
	RECT rc;			//�÷��̾� �浹 �簢��
	RECT attack;		//���� �浹 �簢��
	//RECT jumpAttack;  //���� �浹 �簢��

	//�±� ����
	tagstate _state;
};
class player : public gameNode
{
private:
	//������ �̹��� 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

private:
	//RECT _stage;		//����
	RECT _playerDoorRc;	// �÷��̾ ���� ��Ҵ��� Ȯ�����ִ� ��Ʈ
	float _enemyCenterX, _enemyCenterY;		//�簢�� �߾�
	//float _immoTime;		//�浹�� �����ð�


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
	void setSight(bool sight) { _player.sight = sight; }

	//�÷��̾��� X,Y��ǥ�� �ֱ����� get�Լ�
	float getPlayerX() { return _player.inGameX; }
	float getPlayerY() { return _player.inGameY; }
	//���� �̵����� �� �÷��̾��� ��ġ�� ��������� �ϹǷ� set���� �÷��̾��� x,y���� ��Ʈ���� �ٲ��ش�.
	void setPlayerRect(int x, int y);
	//����â�� ������ �� �̹����� ��� �����̷��� pWALK���¿��� �ϹǷ� ���¸� �ٲ���� �Ѵ�.
	void setPlayerState(tagstate state) { _player._state = state; }
	//����â�� ���� ���� ������ �� ���� ���� �ٶ󺸰� �־�� �ϴ� ������ ����������Ѵ�.
	int getDirect() { return _direct; }
	//�׸��� ���� ���� �־�� �Ѵ�.
	void setDirect(int direct) { _direct = direct; }
	//�÷��̾��� ��Ʈ�� �ֱ����� get�Լ�
	RECT getPlayerRc() { return _player.rc; }
	//�÷��̾ �� ��ó�� �ִ��� Ȯ���ϱ� ���� get�Լ�
	RECT getPlayerDoorRc() { return _playerDoorRc; }
	//���º��������� �Լ�
	tagstate getAction() { return _player._state; }
	//��Ʋ�� ������ �� _isBattle�� �ʵ�� �ǵ�����.
	bool getIsBattle() { return _isBattle; }
	//��Ʋ�� ���۵� �� �ٲ���� �Ѵ�.
	void setIsBattle(bool isBattle) { _isBattle = isBattle; }

	//���º��� 1.IDLE 2.RUN 3.HIT 4.WALK 5.JUMP 6.ATT 7.GUARD 8.DEAD 9.WIN
	void setAction(int pattern);

	// �÷��̾� ����ü�� �ʱ�ȭ �ϴ� �Լ�
	void settingTagPlayer();
	// �÷��̾� ���Ʈ �÷��̾� ��ġ�� ���� ��ġ�� �������ִ� �Լ�.
	void settingPlayerDoorRect();
	// ������Ʈ â Ʋ���� �� ĳ���Ͱ� ȸ���ϴ� �̹���
	void spinPlayer();
	//�÷��̾� ������Ʈ������ �⵹�簢�����ֱ�
	void hitPlayerAttK() { _player.attXK = _player.attYK = 0; }
	void playerWin();
	void playerHit();

	player() {}
	~player() {}
};

class subplayer : public gameNode
{
private:
	//������ �̹��� 
	int _frameIndex;
	int _frameCount;

	tagPlayer _subPlayer;	//tagPlayer ����ü�� subPlayer ����
	player _player;
	ARROW _arrow;
	image* _walkingDirect;	//4�������� �ȴ� �̹���
private:
	bool _melee;			//�������ݿ���
	bool _isLeft;
	int _direct = 0;
	float _enemyDistance;		//ai�� ���� �Ÿ�
	float _partyDistance;
	//float _distance;		//ai�� ���� �Ÿ�

	tagstate _state;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	//enum�±� ��ȭ�� ���� ���ϴ� �÷��̾� ���
	void animation();
	//����â���� �ȴ� �ִϸ��̼� ���
	void walkingInfo();

	player setPlayer(player _playerAddress) { _player = _playerAddress; }


	tagPlayer* getSubPlayer() { return &_subPlayer; }
	void setSubPlayer(tagPlayer subPlayer) { _subPlayer = subPlayer; }

	void setSubPlayerState(tagstate state) { _subPlayer._state = state; }
	int getDirect() { return _direct; }
	void setDirect(int direct) { _direct = direct; }

	void checkDistanceWithPlayer(POINT P);
	void checkDistanceWithEnemy(POINT p);
	bool checkArrowHitTheEnemy(POINT P);
	subplayer() {}
	~subplayer() {}
};

