#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	bool _tileSetting;
	bool _canMove;
	bool _setSaveLoad;		//���̺�/�ε�â ������ִ°� ���°� �Ǵ�
	char _fileName[128];	//���� �̸�(��, �� ������)�� �޾ƿ� ����
	int _startFile;			/*���� ���� 0������ ����
							ex) MAP0.map	MAP0.mapdata
							*/
	unsigned int _palettePage;
	bool _layer[3];

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

	RECT _rcSaveLoad;		//���̺�/�ε��ư
	RECT _rcSaveWindow;		//���̺� â
	RECT _rcSaveSlot[3];		//���̺꽽��3��
	
	RECT _rcSave;			//���̺�ε� UI�ȿ����� ���̺�
	RECT _rcLoad;			//���̺�ε� UI�ȿ����� �ε�



	RECT _rcDummy1;			//2��°ĭ	��������	
	RECT _rcDummy2;			//3��°ĭ	���� 
	RECT _rcDummy3;			//4��°ĭ	������Ʈ
	RECT _rcDummy4;			//5��°ĭ	���찳(������Ʈ�� �����, ������ ������)

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��������
	void maptoolSetup();
	void setMap();
	void uiMove();
	void save(char* str);
	void load(char* str);

	void frameBoxRender(int left, int top, int width, int height, float scale);			//������ ������Ű�� ���ڴ� RectMake������ �ؽ����ϰ��� �����ϸ� ������
																						//�簢���� ������ ����� ���ڴ� �簢��	��scale���� �����ϸ� ������
	void frameBoxRender(RECT rc, float scale);											//������ ������Ű�� ���ڴ� RectMake������ �ؽ����ϰ��� �����ϸ� ������
																						//�����ε�-> ��Ʈ�־ �����ϰ�		��scale < 1 => ����� �ȱ׷���

	void selectLayer1();
	void selectLayer2();
	void selectLayer3();

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

