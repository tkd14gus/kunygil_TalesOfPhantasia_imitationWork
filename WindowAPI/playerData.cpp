#include "stdafx.h"
#include "playerData.h"
#include "player.h"

HRESULT playerData::init()
{
	_subPlayer = new subplayer;
	_subPlayer->init();
	return S_OK;
}

void playerData::release()
{
	_subPlayer->release();
	SAFE_DELETE(_subPlayer);
}

player * playerData::getPlayerData()
{
	//�÷��̾ NULL�� �ƴҶ�(set���� �޾��� ����)
	if (_player != NULL)
	{
		//���Ͻ����ش�.
		return _player;
	}
	else
		return NULL;
}
subplayer* playerData::getSubPlayerData()
{
	if (_subPlayer != NULL)
	{
		return _subPlayer;
	}
	else
		return NULL;
}
//Ÿ���� RECT������ �����ش�.(load)
RECT* playerData::getTilesRC()
{
	return _tilesRC;
}
//Ÿ���� RECT��ġ�� ����
void playerData::setTilesRC(tagTile tilesRC[TILEX * TILEY])
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tilesRC[i] = tilesRC[i].rc;
	}
}
