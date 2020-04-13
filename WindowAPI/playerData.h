#pragma once
#include "singletonBase.h"
#include "tileNode.h"

class player;

class playerData : public singletonBase <playerData>
{
private:
	//�÷��̾� �����͸� �����ؾ� �ϱ� ������ ���� ����
	player* _player;
	//Ÿ���� RECT��ġ�� �ޱ�����
	RECT _tilesRC[TILEX * TILEY];
public:
	HRESULT init();
	void release();

	//�÷��̾� �����͸� �����Ѵ�.(save)
	void setPlayerData(player* player) { _player = player; }
	//�÷��̾� �����͸� �����ش�.(load)
	player* getPlayerData();

	//Ÿ���� RECT��ġ�� ����(save)
	void setTilesRC(tagTile tilesRC[TILEX * TILEY]);
	//Ÿ���� RECT������ �����ش�.(load)
	RECT* getTilesRC();


	//ó�� �����ڸ� �ҷ��� �� _player�� NULL�� ����� �ٸ�������
	//get�� �� ����������� �ƴ����� Ȯ�ν����ش�.
	playerData() : _player{ NULL }, _tilesRC{NULL} {}
	~playerData() {}
};

