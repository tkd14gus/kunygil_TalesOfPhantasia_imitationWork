#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class player;

class playerData : public singletonBase <playerData>
{
private:
	//플레이어 데이터를 저장해야 하기 때문에 변수 선언
	player* _player;
	//타일의 RECT위치를 받기위해
	RECT _tilesRC[TILEX * TILEY];
public:
	HRESULT init();
	void release();

	//플레이어 데이터를 저장한다.(save)
	void setPlayerData(player* player) { _player = player; }
	//플레이어 데이터를 보내준다.(load)
	player* getPlayerData();

	//타일의 RECT위치를 저장(save)
	void setTilesRC(tagTile tilesRC[TILEX * TILEY]);
	//타일의 RECT정보를 보내준다.(load)
	RECT* getTilesRC();


	//처음 생성자를 불러올 때 _player를 NULL로 만들어 다른곳에서
	//get할 때 만들어졌는지 아닌지를 확인시켜준다.
	playerData() : _player{ NULL }, _tilesRC{NULL} {}
	~playerData() {}
};

