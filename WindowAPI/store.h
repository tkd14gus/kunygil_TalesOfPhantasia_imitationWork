#pragma once
#include "gameNode.h"
#include "item.h"


class store :public gameNode
{
private:
	item* _item;
	vector<tagItemInfo> _vItem;	//�κ� �� ������ ���� �ҷ�����
	
	RECT backGroundRect[4];  	//��� ��ġ�� ��Ʈ
	
	int itemType;				//������ ����(weapon/armor/ring/portion)
	RECT typeRect[4];			//������ ���� ���ÿ� ��Ʈ
	bool inStore[4];			//������ ���õ� �������� Ȯ�ο�
	bool showDetail;			//������ ������ ��������ΰ�
	
	vector<RECT> itemSelect;	//������ ���ý� �浹ó�� ���� ��Ʈ(�̰��� ������ �̸��� ��µ�)
	vector<image*> itemName;    //������ �̸�
	char sItemName[128]={ 0, };	//������ �̸� ������ ���ں���
	vector<image*> itemImage;	//������ �̹���
	char sItemImage[128] = { 0, };
	vector<int> itemPrice;      //������ ����
	vector<int> attribute;      //������ �ɷ�ġ
	vector<image*> attributeImage;
	char sAttributeImage[128] = { 0, };
	vector<int> sAttribute;		//������ ���� �ɷ�ġ
	vector<int> amount;			//������ ���� ����

	int totalMoney;				//�뵵�� ���� �ӽ÷� �־��(�ʿ������ ����)

	char num[10];				//����(��/���� ��) �����Ҷ� ����� ���ں���

	int section;				//������ ���Ľ� �ʿ��� ����
	int range;					//������ ��ȣ ����

	RECT backToGame;			//�ڷΰ���(�������� ���ư���)

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

	void frameBoxRender(int left, int top, int width, int height, float scale);			//�˾�â(�ؽ�Ʈ��)�� �����Ӿ����
	void frameBoxRender(RECT rc, float scale);											//�����Ӿ���� �簢�� �־ �����ϰ�

	store() {}
	~store() {}

};

