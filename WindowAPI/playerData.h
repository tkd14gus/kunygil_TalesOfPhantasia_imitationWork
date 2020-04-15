#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class player;
class subplayer;

class playerData : public singletonBase <playerData>
{
private:
	//플레이어 데이터를 저장해야 하기 때문에 변수 선언
	player* _player;
	subplayer* _subPlayer;
	//타일의 RECT위치를 받기위해
	RECT _tilesRC[TILEX * TILEY];

	//맵의 현재 위치를 저장
	int _mapLocation;
public:
	HRESULT init();
	void release();

	//플레이어 데이터를 저장한다.(save)
	void setPlayerData(player* player) { _player = player; }
	void setSubPlayerData(subplayer* subPlayer) { _subPlayer = subPlayer; }
	//플레이어 데이터를 보내준다.(load)
	player* getPlayerData();
	subplayer* getSubPlayerData();



	//타일의 RECT위치를 저장(save)
	void setTilesRC(tagTile tilesRC[TILEX * TILEY]);
	//타일의 RECT정보를 보내준다.(load)
	RECT* getTilesRC();

	void setMapLocation(int mapLocation) { _mapLocation = mapLocation; }
	//어차피 0로 초기화 해서 그냥 보내줘도 상관 없다.
	int getMapLocation() { return _mapLocation; }

	//처음 생성자를 불러올 때 _player를 NULL로 만들어 다른곳에서
	//get할 때 만들어졌는지 아닌지를 확인시켜준다.
	playerData() : _player{ NULL }, _mapLocation{ 0 } {}
	~playerData() {}
};

