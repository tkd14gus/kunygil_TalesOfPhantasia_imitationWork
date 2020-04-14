#pragma once
#include "gameNode.h"


enum tagstate
{
	pIDLE,		//대기
	pRUN,		//달리기
	pHIT,		//맞기
	pWALK,		//걷기
	pJUMP,		//점프
	pATTACK,	//공격
	pGUARD,		//방어
	pDEAD,		//사망
	pWIN		//승리
};

struct ARROW	//화살 구조체
{
	bool _bShoot;		//화살을 발사했는지 판단
	float _speed;		//화살이 날아가는 속도
	float _chargeTime;	//화살 장전 시간

	POINT _point;	//화살의 초기 (x, y) 좌표
	RECT _rc;		//화살 Rect
	image* _img;	//화살 이미지
};

struct tagPlayer
{
	bool sight;			//플레이어 시각(0 - 왼쪽, 1 - 오른쪽)
	int lv;				//플레이어 LV
	int maxHp, hp;		//플레이어 hp
	int maxTp, tp;		// 플레이어 tp
	int attXK, attYK;		//<-무슨 역할인지 확인 필요
	int viewX;				//랜더를위한값

	float x, y;				//플레이어 좌표
	float inGameX, inGameY;	//전투가 아니라 인게임 내에서 쓸 좌표
	float speed;			//플레이어 이동속도
	float gravity;			//중력값

	image* idle;	//대기 이미지
	image* walk;	//걷기 이미지
	image* run;		//달리기 이미지
	image* guard;	//방어 이미지

	image* atkSlash;	
	image* atkstab;
	image* atkshot;		//원거리 공격 이미지
	image* atkmelee;	//근접 공격 이미지
	image* jump;		//점프 이미지

	image* hit;			//히트 모션 추가 - 구민본
	image* dead;		//사망 이미지
	image* win;			//승리 이미지


	RECT cameraRc;
	RECT rc;			//플레이어 충돌 사각형
	RECT attack;		//공격 충돌 사각형
	//RECT jumpAttack;  //공격 충돌 사각형

	//태그 상태
	tagstate _state;
};
class player : public gameNode
{
private:
	//프레임 이미지 
	int _frameIndex;
	int _frameCount;

	tagPlayer _player;

private:
	//RECT _stage;		//지형
	RECT _playerDoorRc;	// 플레이어가 문에 닿았는지 확인해주는 렉트
	float _enemyCenterX, _enemyCenterY;		//사각형 중앙
	//float _immoTime;		//충돌시 무적시간


	int _direct;		// 플레이어가 왼쪽을 보고 있는지
						//0: 위, 1: 아래, 2: 좌, 3: 우

	bool _isBattle;	//플레이어가 현재 배틀씬인지 아닌지

public:

	HRESULT init();
	void release();
	void update();
	void render();



	//float getenemyCenterx() { return _enemyCenterX; }
	//float getenemyCentery() { return _enemyCenterY; }
	//RECT getenemyRect() { return _TESTenemy; }

	//enum태그 변화에 따라 변하는 플레이어 모션
	void animation();
	tagPlayer* getPlayer() { return &_player; }
	void setPlayer(tagPlayer player) { _player = player; }
	void setSight(bool sight) { _player.sight = sight; }

	//플레이어의 X,Y좌표를 주기위한 get함수
	float getPlayerX() { return _player.inGameX; }
	float getPlayerY() { return _player.inGameY; }
	//맵이 이동했을 때 플레이어의 위치를 조정해줘야 하므로 set으로 플레이어의 x,y값과 렉트값을 바꿔준다.
	void setPlayerRect(int x, int y);
	//상태창을 열었을 때 이미지가 계속 움직이려면 pWALK상태여야 하므로 상태를 바꿔줘야 한다.
	void setPlayerState(tagstate state) { _player._state = state; }
	//상태창에 들어갔을 떄와 나왔을 떄 같은 곳을 바라보고 있어야 하니 방향을 가르쳐줘야한다.
	int getDirect() { return _direct; }
	//그리고 받을 수도 있어야 한다.
	void setDirect(int direct) { _direct = direct; }
	//플레이어의 렉트를 주기위한 get함수
	RECT getPlayerRc() { return _player.rc; }
	//플레이어가 문 근처에 있는지 확인하기 위한 get함수
	RECT getPlayerDoorRc() { return _playerDoorRc; }
	//상태변경을위한 함수
	tagstate getAction() { return _player._state; }
	//배틀이 끝났을 떄 _isBattle로 필드로 되돌린다.
	bool getIsBattle() { return _isBattle; }
	//배틀이 시작될 때 바꿔줘야 한다.
	void setIsBattle(bool isBattle) { _isBattle = isBattle; }

	//상태변경 1.IDLE 2.RUN 3.HIT 4.WALK 5.JUMP 6.ATT 7.GUARD 8.DEAD 9.WIN
	void setAction(int pattern);

	// 플레이어 구조체를 초기화 하는 함수
	void settingTagPlayer();
	// 플레이어 도어렉트 플레이어 위치에 따라 위치를 조정해주는 함수.
	void settingPlayerDoorRect();
	// 스테이트 창 틀었을 때 캐릭터가 회전하는 이미지
	void spinPlayer();
	//플레이어 공격히트했을떄 출돌사각형없애기
	void hitPlayerAttK() { _player.attXK = _player.attYK = 0; }
	void playerWin();
	void playerHit();

	player() {}
	~player() {}
};

class subplayer : public gameNode
{
private:
	//프레임 이미지 
	int _frameIndex;
	int _frameCount;

	tagPlayer _subPlayer;	//tagPlayer 구조체로 subPlayer 생성
	player _player;
	ARROW _arrow;
	image* _walkingDirect;	//4방향으로 걷는 이미지
private:
	bool _melee;			//근접공격여부
	bool _isLeft;
	int _direct = 0;
	float _enemyDistance;		//ai와 적의 거리
	float _partyDistance;
	//float _distance;		//ai와 적의 거리

	tagstate _state;
public:

	HRESULT init();
	void release();
	void update();
	void render();

	//enum태그 변화에 따라 변하는 플레이어 모션
	void animation();
	//상태창에서 걷는 애니메이션 출력
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

