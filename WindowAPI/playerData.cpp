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
	//플레이어가 NULL이 아닐때(set으로 받았을 때만)
	if (_player != NULL)
	{
		//리턴시켜준다.
		return _player;
	}
	else
		return NULL;
}
//타일의 RECT정보를 보내준다.(load)
RECT* playerData::getTilesRC()
{
	if(_tilesRC == NULL)
	{
		_tilesRC[0] = { 0, 0, 0, 0 };
	}
	return _tilesRC;
}
//타일의 RECT위치를 저장
void playerData::setTilesRC(tagTile tilesRC[TILEX * TILEY])
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tilesRC[i] = tilesRC[i].rc;
	}
}
