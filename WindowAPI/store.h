#pragma once
#include "gameNode.h"
#include "item.h"


class store :public gameNode
{
private:
	item* _item;
	vector<tagItemInfo> _vItem;	//인벤 내 아이템 정보 불러오기
	
	RECT backGroundRect[4];  	//배경 배치용 렉트
	
	int itemType;				//아이템 종류(weapon/armor/ring/portion)
	RECT typeRect[4];			//아이템 종류 선택용 렉트
	bool inStore[4];			//상점이 선택된 상태인지 확인용
	bool showDetail;			//아이템 디테일 보기상태인가
	
	vector<RECT> itemSelect;	//아이템 선택시 충돌처리 해줄 렉트(이곳에 아이템 이름이 출력됨)
	vector<image*> itemName;    //아이템 이름
	char sItemName[128]={ 0, };	//아이템 이름 가져올 문자변수
	vector<image*> itemImage;	//아이템 이미지
	char sItemImage[128] = { 0, };
	vector<int> itemPrice;      //아이템 가격
	vector<int> attribute;      //아이템 능력치
	vector<image*> attributeImage;
	char sAttributeImage[128] = { 0, };
	vector<int> sAttribute;		//아이템 서브 능력치
	vector<int> amount;			//아이템 남은 수량

	int totalMoney;				//용도를 몰라서 임시로 넣어둠(필요없을시 지움)

	char num[10];				//숫자(돈/수량 등) 추적할때 사용할 문자변수

	int section;				//아이템 정렬시 필요한 변수
	int range;					//아이템 번호 지정

	RECT backToGame;			//뒤로가기(게임으로 돌아가기)

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void storesetting();
	void itemSet(int itemTpye);
	void itemShow();
	void itemDetail();
	void showNumber(int number,int xPos,int yPos);

	void frameBoxRender(int left, int top, int width, int height, float scale);			//팝업창(텍스트등)에 프레임씌우기
	void frameBoxRender(RECT rc, float scale);											//프레임씌우기 사각형 넣어서 간편하게

	store() {}
	~store() {}

};

