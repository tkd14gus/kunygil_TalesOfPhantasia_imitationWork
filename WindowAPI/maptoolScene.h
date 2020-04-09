#pragma once
#include "gameNode.h"
#include "tileNode.h"

class maptoolScene : public gameNode
{
private:
	bool _editMode;			//������ �Ӽ� �Է� ���.
	bool _eitCanMove;
	bool _editMoveDirect;
	bool _canMove;
	bool _setSaveLoad;		//���̺�/�ε�â ������ִ°� ���°� �Ǵ�
	bool _slideTool;		//����â�� �ִ�ȭ�Ǿ��ִ��� �ּ�ȭ�Ǿ��ִ��� �Ǵ�
	char _editModechar[128] = { 0, };
	char _fileName[128] = { 0, };	//�� ������ �̸��� �޾ƿ� ����
	char _imageName[128] = { 0, };	//�� �̹��� ������ �̸��� �޾ƿ� ����
	char _dataName[128] = { 0, };	//�� ������ ������ �̸��� �޾ƿ� ����
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



	RECT _rcDummy1;			//2��°ĭ	��������	���� 
	RECT _rcDummy2;			//3��°ĭ	������Ʈ
	RECT _rcDummy3;			//4��°ĭ	���찳(������Ʈ�� �����, ������ ������)
	RECT _rcslide;			//5��°ĭ	�ִ�ȭ / �ּ�ȭ��Ű��

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
	void saveMapData(char *str);
	void loadMapData(char *str);
	void editCanMove();


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

