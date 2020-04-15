#pragma once
#include "gameNode.h"
#include <string>
#include <vector>

enum ITEM
{
	ITEM_WEAPON=1,
	ITEM_ARMOR,
	ITEM_RING,
	ITEM_POTION
};

struct tagItemInfo
{
	ITEM itemKind;      //아이템 종류
	image* itemName;    //아이템 이름
	image* itemImage;	//아이템 이미지
	int itemPrice;      //아이템 가격
	int attribute;      //아이템 능력치
	int sAttribute;		//아이템 서브 능력치
	int amount;			//아이템 초기 수량
};

class item :public gameNode
{
private:
	vector<tagItemInfo> _vItem;
	int money;			//플레이어 소지금

public:
	HRESULT init();
	void release();
	void update();
	void render();

	vector<tagItemInfo> getItem() { return  _vItem;}
	int getMoney() { return money; }

	item() {}
	~item() {}

};


