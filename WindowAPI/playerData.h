#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class player;
class subplayer;

class playerData : public singletonBase <playerData>
{
private:
	//�÷��̾� �����͸� �����ؾ� �ϱ� ������ ���� ����
	player* _player;
	subplayer* _subPlayer;
	//Ÿ���� RECT��ġ�� �ޱ�����
	RECT _tilesRC[TILEX * TILEY];

	//���� ���� ��ġ�� ����
	int _mapLocation;
public:
	HRESULT init();
	void release();

	//�÷��̾� �����͸� �����Ѵ�.(save)
	void setPlayerData(player* player) { _player = player; }
	void setSubPlayerData(subplayer* subPlayer) { _subPlayer = subPlayer; }
	//�÷��̾� �����͸� �����ش�.(load)
	player* getPlayerData();
	subplayer* getSubPlayerData();



	//Ÿ���� RECT��ġ�� ����(save)
	void setTilesRC(tagTile tilesRC[TILEX * TILEY]);
	//Ÿ���� RECT������ �����ش�.(load)
	RECT* getTilesRC();

	void setMapLocation(int mapLocation) { _mapLocation = mapLocation; }
	//������ 0�� �ʱ�ȭ �ؼ� �׳� �����൵ ��� ����.
	int getMapLocation() { return _mapLocation; }

	//ó�� �����ڸ� �ҷ��� �� _player�� NULL�� ����� �ٸ�������
	//get�� �� ����������� �ƴ����� Ȯ�ν����ش�.
	playerData() : _player{ NULL }, _mapLocation{ 0 } {}
	~playerData() {}
};

