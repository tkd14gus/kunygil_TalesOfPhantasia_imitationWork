#include "stdafx.h"
#include "item.h"


HRESULT item::init()
{
	money = 20000;

	tagItemInfo _itemInfoWeapon1;
	_itemInfoWeapon1.itemKind = ITEM_WEAPON;
	//_itemInfoWeapon1.itemName = "Saber";
	_itemInfoWeapon1.itemPrice = 1000;
	_itemInfoWeapon1.amount = 10;
	_itemInfoWeapon1.attribute = 8;
	_itemInfoWeapon1.sAttribute = 5;
	_vItem.push_back(_itemInfoWeapon1);

	tagItemInfo _itemInfoArmor1;
	_itemInfoArmor1.itemKind = ITEM_ARMOR;
	//_itemInfoArmor1.itemName = "Leather Armor";
	_itemInfoArmor1.itemPrice = 500;
	_itemInfoArmor1.amount = 5;
	_itemInfoArmor1.attribute = 2;
	_itemInfoArmor1.sAttribute = 0;
	_vItem.push_back(_itemInfoArmor1);

	tagItemInfo _itemInfoRing1;
	_itemInfoRing1.itemKind = ITEM_RING;
	//_itemInfoRing1.itemName = "Ribbon";
	_itemInfoRing1.itemPrice = 800;
	_itemInfoRing1.amount = 15;
	_itemInfoRing1.attribute = 5;
	_itemInfoRing1.sAttribute = 0;
	_vItem.push_back(_itemInfoRing1);

	tagItemInfo _itemInfoProtion1;
	_itemInfoProtion1.itemKind = ITEM_POTION;
	//_itemInfoProtion1.itemName = "Apple Gummy";
	_itemInfoProtion1.itemPrice = 750;
	_itemInfoProtion1.amount = 20;
	_itemInfoProtion1.attribute = 30;
	_itemInfoProtion1.sAttribute = 0;
	_vItem.push_back(_itemInfoProtion1);


	return S_OK;
}

void item::release()
{
}

void item::update()
{

}

void item::render()
{

}
