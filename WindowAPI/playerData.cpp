#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init()
{
	return S_OK;
}

void playerData::release()
{
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
//Ÿ���� RECT������ �����ش�.(load)
RECT* playerData::getTilesRC()
{
	if(_tilesRC == NULL)
	{
		_tilesRC[0] = { 0, 0, 0, 0 };
	}
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
