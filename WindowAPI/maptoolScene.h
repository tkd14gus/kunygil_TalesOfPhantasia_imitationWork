#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	bool _tileSetting;
	char _fileName[128];	//���� �̸�(��, �� ������)�� �޾ƿ� ����
	int _startFile;			/*���� ���� 0������ ����
							ex) MAP0.map	MAP0.mapdata
							*/
private:
	tagTile _tiles[TILEX * TILEY];	//�ΰ���ȭ�鿡 ���Ǵ� Ÿ�� �� 400��
	tagSampleTile _sampleTile[60]; //����Ÿ�� �� (12-2)*6 = 60��
	tagCurrentTile _currentTile;	//����Ÿ��
private:
	RECT _rcScreen;		//ȭ�� ī�޶� Rect;
						//�� Rect�� �浹�� Ÿ�ϸ� ȭ�鿡 �׷�����.
	RECT _rcArrow[2];	//����Ÿ���� ������ ȭ��ǥ�� �׷��ִ� Rect
						//0�� : LeftArrow, 1�� : RightArrow
	RECT _rcPalette;	//����Ÿ���� �׷��� Rect;
	RECT _rcSave;		//���̺�
	RECT _rcLoad;		//�ε�
	RECT _rcTerrain;	//����
	RECT _rcObject;		//������Ʈ
	RECT _rcEraser;		//���찳(������Ʈ�� �����, ������ ������)

	CTRL _ctrlSelect;	//���� � ��Ʈ�� ��������


public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��������
	void maptoolSetup();
	void setMap();
	void uiMove();
	void save();
	void load();

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objectSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

