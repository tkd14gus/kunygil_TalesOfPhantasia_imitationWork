#include "stdafx.h"
#include "store.h"

HRESULT store::init()
{
	_item = new item;
	_item->init();

	for (int i = 0; i < _item->getItem().size(); i++)
	{
		_vItem.push_back(_item->getItem()[i]);
	}//아이템 정보 불러오기

	this->storesetting();	//레이아웃 세팅

	inStore[0] = true;
	itemType = ITEM_WEAPON;
	this->itemSet(itemType);
	this->itemShow();

	inStore[1] = false;
	inStore[2] = false;
	inStore[3] = false;

	totalMoney = 0;

	showDetail = false;

	section = 0;

	return S_OK;
}

void store::release()
{
}

void store::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		for (int i = 0; i < 4; i++) {
			if (PtInRect(&typeRect[i], _ptMouse)) {
				switch (i)
				{
				case 0:
					inStore[0] = true;
					inStore[1] = false;
					inStore[2] = false;
					inStore[3] = false;
					itemType = ITEM_WEAPON;
					break;
				case 1:
					inStore[0] = false;
					inStore[1] = true;
					inStore[2] = false;
					inStore[3] = false;
					itemType = ITEM_ARMOR;
					break;
				case 2:
					inStore[0] = false;
					inStore[1] = false;
					inStore[2] = true;
					inStore[3] = false;
					itemType = ITEM_RING;
					break;
				case 3:
					inStore[0] = false;
					inStore[1] = false;
					inStore[2] = false;
					inStore[3] = true;
					itemType = ITEM_POTION;
					break;
				}

				this->itemSet(itemType);
			}

			if (PtInRect(&backToGame, _ptMouse)) {
				SCENEMANAGER->loadScene("게임화면");//상점을 끄면 게임화면으로
			}

			for (int i = 0; i < itemSelect.size(); i++) {
				if (PtInRect(&itemSelect[i], _ptMouse)) {
					range = i;
					showDetail = true;
				}
				else if (!PtInRect(&itemSelect[i], _ptMouse)) {
					showDetail = false;
				}
			}
		}
	}

}

void store::render()
{

	for (int i = 0; i < 4; i++) {
		Rectangle(getMemDC(), backGroundRect[i]);
		Rectangle(getMemDC(), typeRect[i]);
	}


	IMAGEMANAGER->findImage("box")->render(getMemDC(), backGroundRect[0].left, backGroundRect[0].top, 0, 0, WINSIZEX - 20, 50);
	IMAGEMANAGER->findImage("box")->render(getMemDC(), backGroundRect[1].left, backGroundRect[1].top);
	IMAGEMANAGER->findImage("box")->render(getMemDC(), backGroundRect[2].left, backGroundRect[2].top, 0, 0, WINSIZEX - 20, 50);
	IMAGEMANAGER->findImage("box")->render(getMemDC(), backGroundRect[3].left, backGroundRect[3].top, 0, 0, WINSIZEX - 20, 200);

	frameBoxRender(0, 0, WINSIZEX, WINSIZEY - 270, 1.0f);
	frameBoxRender(backGroundRect[2].left - 10, backGroundRect[2].top - 10, WINSIZEX, 270, 1.0f);

	IMAGEMANAGER->findImage("weapon_off")->render(getMemDC(), typeRect[0].left, typeRect[0].top);
	IMAGEMANAGER->findImage("armor_off")->render(getMemDC(), typeRect[1].left, typeRect[1].top);
	IMAGEMANAGER->findImage("ring_off")->render(getMemDC(), typeRect[2].left, typeRect[2].top);
	IMAGEMANAGER->findImage("portion_off")->render(getMemDC(), typeRect[3].left, typeRect[3].top);

	IMAGEMANAGER->findImage("leftArrow")->scaleRender(getMemDC(), backToGame.left, backToGame.top, 0.95F);

	for (int i = 0; i < 4; i++) {
		if (PtInRect(&typeRect[i], _ptMouse) || inStore[i]) {
			switch (i)
			{
			case 0:
				IMAGEMANAGER->findImage("weapon")->render(getMemDC(), typeRect[0].left, typeRect[0].top);
				break;
			case 1:
				IMAGEMANAGER->findImage("armor")->render(getMemDC(), typeRect[1].left, typeRect[1].top);
				break;
			case 2:
				IMAGEMANAGER->findImage("ring")->render(getMemDC(), typeRect[2].left, typeRect[2].top);
				break;
			case 3:
				IMAGEMANAGER->findImage("portion")->render(getMemDC(), typeRect[3].left, typeRect[3].top);
				break;
			}
		}
	}

	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < _vItem.size(); i++)
		{
			cout << _vItem[i].itemKind << endl;
		}
	}

	this->itemShow();

	//소지금 표시
	IMAGEMANAGER->findImage("gold")->render(getMemDC(), backGroundRect[2].left + 50, backGroundRect[2].top + 20);
	this->showNumber(_item->getMoney(), backGroundRect[2].left + 220, backGroundRect[2].top + 20);
	IMAGEMANAGER->findImage("total")->render(getMemDC(), backGroundRect[2].right - 250, backGroundRect[2].top + 20);
	this->showNumber(totalMoney, backGroundRect[2].right - 70, backGroundRect[2].top + 20);

	if (showDetail) {
		this->itemDetail();			//아이템 세부정보 보기
	}
}

void store::storesetting() {
	//백그라운드 창
	backGroundRect[0] = RectMake(10, 10, WINSIZEX - 20, 50);
	backGroundRect[1] = RectMake(10, backGroundRect[0].bottom, WINSIZEX - 20, WINSIZEY / 2 + 80);
	backGroundRect[2] = RectMake(10, backGroundRect[1].bottom, WINSIZEX - 20, 50);
	backGroundRect[3] = RectMake(10, backGroundRect[2].bottom, WINSIZEX - 20, 200);

	//상점 선택키
	for (int i = 0; i < 4; i++) {
		typeRect[i] = RectMake(10 + 133 * i, 15, 133, 45);
	}


	//뒤로가기 키
	backToGame = RectMake(typeRect[3].right, typeRect[3].top, 45, 45);
}

//아이템 정보 집어넣기
void store::itemSet(int itemType) {
	section = 0;

	//이전에 삽입되어 있었던 값 다 지워주기
	itemSelect.clear();
	itemImage.clear();
	itemName.clear();
	itemPrice.clear();
	attribute.clear();
	attributeImage.clear();
	sAttribute.clear();
	amount.clear();


	for (int i = 0; i < _vItem.size(); i++) {
		if (_vItem[i].itemKind == itemType) {

			switch (itemType)
			{
			case ITEM_WEAPON:
				sprintf_s(sItemName, "weaponName (%d)", section);
				sprintf_s(sItemImage, "weaponImage (%d)", section);
				sprintf_s(sAttributeImage, "weaponAttribute (%d)", section);
				break;
			case ITEM_ARMOR:
				sprintf_s(sItemName, "armorName (%d)", section);
				sprintf_s(sItemImage, "armorImage (%d)", section);
				sprintf_s(sAttributeImage, "armorAttribute (%d)", section);
				break;
			case ITEM_RING:
				sprintf_s(sItemName, "ringName (%d)", section);
				sprintf_s(sItemImage, "ringImage (%d)", section);
				sprintf_s(sAttributeImage, "ringAttribute (%d)", section);
				break;
			case ITEM_POTION:
				sprintf_s(sItemName, "portionName (%d)", section);
				sprintf_s(sItemImage, "portionImage (%d)", section);
				sprintf_s(sAttributeImage, "portionAttribute (%d)", section);
				break;
			}

			section++;

			itemSelect.push_back(RectMake(50, 100 + 40 * (section - 1), 200, 20));
			itemName.push_back(IMAGEMANAGER->findImage(sItemName));
			itemImage.push_back(IMAGEMANAGER->findImage(sItemImage));
			itemPrice.push_back(_vItem[i].itemPrice);
			attribute.push_back(_vItem[i].attribute);
			attributeImage.push_back(IMAGEMANAGER->findImage(sAttributeImage));
			sAttribute.push_back(_vItem[i].sAttribute);
			amount.push_back(_vItem[i].amount);
		}
	}
}

//아이템 정보 출력하기
void store::itemShow() {
	for (int i = 0; i < itemSelect.size(); i++) {
		itemName[i]->render(getMemDC(), itemSelect[i].left, itemSelect[i].top);
		this->showNumber(itemPrice[i], itemSelect[i].right + 120, itemSelect[i].top);
		IMAGEMANAGER->findImage("x")->render(getMemDC(), itemSelect[i].right + 175, itemSelect[i].top);
		this->showNumber(amount[i], itemSelect[i].right + 250, itemSelect[i].top);
	}
}

void store::itemDetail() {
	itemImage[range]->render(getMemDC(), backGroundRect[3].left + 35, backGroundRect[3].top + 30);
	itemName[range]->render(getMemDC(), backGroundRect[3].left + 200, backGroundRect[3].top + 30);
	attributeImage[range]->render(getMemDC(), backGroundRect[3].left + 190, backGroundRect[3].top + 100);

	switch (itemType)
	{
	case ITEM_WEAPON:
		IMAGEMANAGER->findImage("weaponG")->scaleRender(getMemDC(), backGroundRect[3].left + 198, backGroundRect[3].top + 53, 0.8f);
		break;
	case ITEM_ARMOR:
		IMAGEMANAGER->findImage("armorG")->scaleRender(getMemDC(), backGroundRect[3].left + 198, backGroundRect[3].top + 53, 0.8f);
		break;
	case ITEM_RING:
		IMAGEMANAGER->findImage("ringG")->scaleRender(getMemDC(), backGroundRect[3].left + 198, backGroundRect[3].top + 53, 0.8f);
		break;
	case ITEM_POTION:
		IMAGEMANAGER->findImage("portionG")->scaleRender(getMemDC(), backGroundRect[3].left + 198, backGroundRect[3].top + 53, 0.8f);
		break;
	}
}


void store::showNumber(int number, int xPos, int yPos) //돈 정보 출력하기 y좌표는 오른쪽 끝 정렬 위치를 나타냅니다
{
	//6번째 자리까지 출력할 수 있습니다
	//숫자가 1의 자리일 경우 출력되지 않는 현상이 생김
	for (int i = 0; i < number; i++) {
		sprintf_s(num, "%d", i);
		if (number % 1000000 / 100000 == i && number > 99999) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos - 100, yPos); }
		if (number % 100000 / 10000 == i && number > 9999) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos - 80, yPos); }
		if (number % 10000 / 1000 == i && number > 999) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos - 60, yPos); }
		if (number % 1000 / 100 == i && number > 99) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos - 40, yPos); }
		if (number % 100 / 10 == i && number > 9) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos - 20, yPos); }
		if (number % 10 == i) { IMAGEMANAGER->findImage(num)->render(getMemDC(), xPos, yPos); }
	}
}


void store::frameBoxRender(int left, int top, int width, int height, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), left, top, 0, 0, 17 * scale, height, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), left + width - (17 * scale), top, 0, 0, 17 * scale, height, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), left, top, 0, 0, width, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), left, top + height - (17 * scale), 0, 0, width, 17 * scale, scale);


	//프레임바디
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), left, top, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), left + width - (17 * scale), top, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), left, top + height - (17 * scale), scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), left + width - (17 * scale), top + height - (17 * scale), scale);
	//모서리

}
void store::frameBoxRender(RECT rc, float scale)
{
	IMAGEMANAGER->findImage("FrameL")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.top - 1, 0, 0, 17 * scale, rc.bottom + 1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameR")->scaleRender(getMemDC(), rc.right, rc.top - 1, 0, 0, 17 * scale, rc.bottom + 1 - rc.top, scale);
	IMAGEMANAGER->findImage("FrameT")->scaleRender(getMemDC(), rc.left - 1, rc.top - 17 * scale, 0, 0, rc.right + 1 - rc.left, 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameB")->scaleRender(getMemDC(), rc.left - 1, rc.bottom, 0, 0, rc.right + 1 - rc.left, 17 * scale, scale);


	//프레임바디
	IMAGEMANAGER->findImage("FrameLT")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.top - 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameRT")->scaleRender(getMemDC(), rc.right, rc.top - 17 * scale, scale);
	IMAGEMANAGER->findImage("FrameLB")->scaleRender(getMemDC(), rc.left - 17 * scale, rc.bottom, scale);
	IMAGEMANAGER->findImage("FrameRB")->scaleRender(getMemDC(), rc.right, rc.bottom, scale);

	//모서리

}
