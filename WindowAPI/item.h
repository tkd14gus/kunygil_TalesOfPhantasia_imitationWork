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
	ITEM itemKind;      //������ ����
	image* itemName;    //������ �̸�
	image* itemImage;	//������ �̹���
	int itemPrice;      //������ ����
	int attribute;      //������ �ɷ�ġ
	int sAttribute;		//������ ���� �ɷ�ġ
	int amount;			//������ �ʱ� ����
};

class item :public gameNode
{
private:
	vector<tagItemInfo> _vItem;
	int money;			//�÷��̾� ������

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


