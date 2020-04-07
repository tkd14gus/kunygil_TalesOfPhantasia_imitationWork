#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//상호참조용 클래스 전방선언
class enemyManager;

class player : public gameNode
{
private:
	enemyManager* _em;  //절대로 동적할당 놉!!
	//메인게임에서 생성한 EM과 플레이어에서 생성한 EM은
	//전혀 다른 메모리 주소라서 서로 참조할 수 없다!!!

private:
	image* _rocket;		//로켓(플레이어) 이미지
	//RECT _rcPlayer;		//플레이어 움직일 렉트
	missile* _missile;	//미사일 클래스
	bomb* _bomb;		//폭탄 클래스

	progressBar* _hpBar;	 //체력바
	float _maxHp, _currentHp; //최대체력, 현재체력

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//폭탄클래스 가져오기
	bomb* getBomb() { return _bomb; }

	//폭탄삭제
	void removeBomb(int index);

	//충돌함수(플레이어총알, 미니언충돌)
	void collision();

	//피통깍기
	void hitDamage(float damage);

	//세이브로드
	void save();
	void load();

	//플레이어 이미지 가져오기
	image* getPlayerImg() { return _rocket; }

	//상호참조시 적매니져 포인터를 넘겨받을 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

