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

//����
struct TERRAIN
{
	int x, y;
};

//Ÿ�ϱ���ü
//�� Ÿ�ϴ� ���̾� ���� 3������
struct tagTile
{
	TERRAIN terrain;
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
	int pageNumber;
	int x, y;
};