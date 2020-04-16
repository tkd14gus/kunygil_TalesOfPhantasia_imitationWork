#pragma once
#include "gameNode.h"
#include "tileNode.h"
#define VK_D	0x44
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33

class maptoolScene : public gameNode
{
private:
	bool _editMode;					//������ �Ӽ� �Է� ���.
	bool _editCanMove;				//�ش� Ÿ�Ϸ� �̵��� ������ �� �ִ��� �Ǵ����ִ� bool ����
	bool _editMoveDirect;			//�ش� Ÿ�Ͽ��� �̵� ������ ������ �� �ִ��� �Ǵ����ִ� bool ����
	bool _canMove;					//���� ������ Ÿ���� �̵� ������ Ÿ���ΰ�?
	bool _direct[4] = { false, };	//���� ������ Ÿ�Ͽ��� � �������� �̵��� �� �ִ°�?
									//0:��	1:��	  2:��  3:��
	bool _setSaveLoad;				//���̺�/�ε�â ������ִ°� ���°� �Ǵ�
	bool _slideTool;				//����â�� �ִ�ȭ�Ǿ��ִ��� �ּ�ȭ�Ǿ��ִ��� �Ǵ�

	int _setSaveSlot;				//���̺� ���� Ȱ��ȭ
	char _palettePageNum[128];

	char _canMoveChar[8] = { 0, };		//����Ʈ ��忡�� ���
										//�� ���� Ÿ�Ϸ� �̵��� �� �ִ��� ǥ��.
										//0 : �̵� �Ұ�		1 : �̵� ����
	char _moveDirectChar[5] = { 0, };	//����Ʈ ��忡�� ���
										//�� ����Ÿ�Ͽ��� � �������� �̵��� �� �ִ����� ǥ��.
										//0:��  1:��  2:��  3:��


	char _fileName[128] = { 0, };	//�� ������ �̸��� �޾ƿ� ���� 
	char _mapName[128] = { 0, };
									//���� �̸�(��, �� ������)�� �޾ƿ� ����
	char _imageName[128] = { 0, };	//�� �̹��� ������ �̸��� �޾ƿ� ����
	char _dataName[128] = { 0, };	//�� ������ ������ �̸��� �޾ƿ� ����

	int _startFile;			/*���� ���� 0������ ����
							ex) MAP0.map	MAP0.mapdata
							*/



/////////////////////////////////////////////////////////////////////////////////////////-YSH- unsigned ������
	int _palettePage;		//���� ���� Ÿ�Ͽ� ���° ���� �̹����� �׷��������� ������ ����.
	bool _layer[LAYERCOUNT];		//�� ��° ���̾� ������ ǥ��.

private:
	tagTile _tiles[TILEX * TILEY];	//�ΰ���ȭ�鿡 ���Ǵ� Ÿ�� �� 400��
	tagTile _saveTile[TILEX * TILEY];
	tagSampleTile _sampleTile[60]; //����Ÿ�� �� (12-2)*6 = 60��
	tagCurrentTile _currentTile;	//����Ÿ��


private:
	RECT _rcScreen;		//ȭ�� ī�޶� Rect;
						//�� Rect�� �浹�� Ÿ�ϸ� ȭ�鿡 �׷�����.
	RECT _rcArrow[2];	//����Ÿ���� ������ ȭ��ǥ�� �׷��ִ� Rect
						//0�� : LeftArrow, 1�� : RightArrow
	RECT _rcArrow5[2];
	RECT _rcPalette;	//����Ÿ���� �׷��� Rect;

	RECT _rcMouse;		//���콺 �����͸� ����ٴϴ� Rect
						//�߽����� ���콺 �������� ��ǥ�̸�
						//�� Rect�� ȭ�� ���� ������ Ÿ���� �����δ�.

	RECT _rcSaveLoad;		//���̺�/�ε��ư
	RECT _rcSaveWindow;		//���̺� â
	RECT _rcSaveSlot[3];		//���̺꽽��3��
	
	RECT _rcSave;			//���̺�ε� UI�ȿ����� ���̺�
	RECT _rcLoad;			//���̺�ε� UI�ȿ����� �ε�



	RECT _rcEraser;			//2��°ĭ	��������	���� 
	RECT _rcDummy2;			//3��°ĭ	������Ʈ
	RECT _rcDummy3;			//4��°ĭ	���찳(������Ʈ�� �����, ������ ������)
	RECT _rcslide;			//5��°ĭ	�ִ�ȭ / �ּ�ȭ��Ű��

	dragRect _dragRect;		//�ȷ�Ʈ �巡�� ���ÿ��� ����
	drawField _drawField;	//Ÿ�� �� �巡�� ���ÿ�����
	RECT selectRect;		//�׸��� �׷��� ��ġ �̸�����


	char _pageNum[100];
	char _pageName[100];

	char drag[1024];	//�巡�� ��ǥ �̸������
	char count[1042];

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��������
	void maptoolSetup();
	void setSample();
	void setMap();						//�Ϲ� ä���
	void setAllMap();					//��ü ä���	
	void setFieldMap();					//������ �����Ͽ� ���� Ÿ�Ϸ� ä���
	void uiMove();
	void save(char* str);				//������ ���� �����ϴ� �Լ�
	void load(char* str);				//���۵� ���� �ҷ����� �Լ�
	void saveMapData(char *str);		//����Ÿ���� �Ӽ��� ������Ʈ ������ ���� ������ MapData��
										//.mapdata Ȯ���ڷ� ����ȴ�.
										//���� ���׷� �̵���.
	void loadMapData(char *str);		//����Ÿ���� �Ӽ��� ������Ʈ ������ ���� ������ MapData����
										//.mapdata Ȯ���ڸ� �ҷ��´�.


	void frameBoxRender(int left, int top, int width, int height, float scale);			//�˾�â(�ؽ�Ʈ��)�� �����Ӿ����
																						
	void frameBoxRender(RECT rc, float scale);											//�����Ӿ���� �簢�� �־ �����ϰ�
																						


	void selectLayer1();	//1�� ���̾� ����
	void selectLayer2();	//2�� ���̾� ����
	void selectLayer3();	//3�� ���̾� ����

	//����, ������Ʈ ����
	TERRAIN terrainSelect(int frameX, int frameY);

	maptoolScene() {}
	~maptoolScene() {}
};

