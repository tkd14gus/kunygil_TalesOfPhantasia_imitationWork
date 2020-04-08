#pragma once

//����ȭ�� Ÿ��
#define TILESIZE 48
#define TILEX 120
#define TILEY 150
#define TILESIZEX (TILEX * TILESIZE)
#define TILESIZEY (TILEY * TILESIZE)
#define LAYERCOUNT 3

//�̹��� Ÿ��(ȭ�� ������ܿ� �ٿ����� ����Ÿ��)
#define SAMPLETILEX 12
#define SAMPLETILEY 6

//�������� ����� ��Ʈ�ѵ�
enum CTRL
{
	CTRL_SAVE, CTRL_LOAD,
	CTRL_TERRAIN, CTRL_OBJECT, CTRL_ERASER,
	CTRL_MAP1, CTRL_MAP2, CTRL_MAP3, CTRL_END
};

//����
enum TERRAIN
{
	TR_CEMENT, TR_GROUND, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1, OBJ_BLOCK3, OBJ_BLOCKS,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_NONE
};

//Ÿ�ϱ���ü
//�� Ÿ�ϴ� ���̾� ���� 3������
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	bool canMove[LAYERCOUNT] = { false, };	//�� Ÿ�� ���� �̵��� �� �ִ��� Ȯ�����ִ� bool ����
											//�⺻�� false
											//�ϳ��� false�� �� Ÿ�� ���δ� �̵��� �� ����
	bool direct[4] = { false, };		//�̵��� �����ϴٸ� � �������� �̵��� �� �ִ��� ����
										//true�� ��쿡�� �̵� ����.
										//�⺻�� == false
										//0: ��, 1: �Ʒ�, 2: ��, 3: ��
	int imagePage[LAYERCOUNT] = { -1, };
	int tileFrameX[LAYERCOUNT];
	int tileFrameY[LAYERCOUNT];
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;

	int imagePage;
	int tileFrameX;
	int tileFrameY;
	
	bool canMove;
	bool direct[4];
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int x, y;
};