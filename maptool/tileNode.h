#pragma once

//����ȭ�� Ÿ��
#define TILESIZE 48			//Ÿ�� �ȼ�
#define TILEX 120			//�� Ÿ���� ���ΰ� �� ĭ����
#define TILEY 150			//�� Ÿ���� ���ΰ� �� ĭ����
#define TILESIZEX (TILEX * TILESIZE)		//�� Ÿ���� ������ �ȼ� ��
#define TILESIZEY (TILEY * TILESIZE)		//�� Ÿ���� ������ �ȼ� ��

//�̹��� Ÿ��(ȭ�� ������ܿ� �ٿ����� ����Ÿ��)
#define SAMPLETILEX 12
#define SAMPLETILEY 6

//����Ÿ�� ���� ����
//���� Ÿ���� �� 69������ �ֽ��ϴ�
#define SMAPLETILECOUNT 69


//���̾� ���� ����
#define LAYERCOUNT 3
//����
struct TERRAIN
{
	int x, y;		//Ÿ��(x, y)���� ����.
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
	bool direct[4] = { false, };			//�̵��� �����ϴٸ� � �������� �̵��� �� �ִ��� ����
											//true�� ��쿡�� �̵� ����.
											//�⺻�� == false
											//0: ��, 1: �Ʒ�, 2: ��, 3: ��
	int imagePage[LAYERCOUNT] = { -1, };	//� ���ø��� �׷ȴ��� �����ϴ� ����
	int tileFrameX[LAYERCOUNT];				//imagePage�� ���η� �� ��° Ÿ������ �����ϴ� ����
	int tileFrameY[LAYERCOUNT];				//imagePage�� ���η� �� ��° Ÿ������ �����ϴ� ����
};

//�̹��� Ÿ�� ����ü
struct tagSampleTile
{
	RECT rc;

	int imagePage;							//����Ÿ�� ��ȣ
	int tileFrameX;							//���� �� ��°�� �׷��������� ������ ����
	int tileFrameY;							//���� �� ��°�� �׷��������� ������ ����
	
	bool canMove = false;					//�� Ÿ�Ϸ� �̵��� �����Ѱ�?
											//�⺻�� : �̵��Ұ�
	bool direct[4] = { false, };			//�� Ÿ�Ͽ��� � �������� �̵��� �����Ѱ�?
											//�⺻�� : �̵��Ұ�
											//0:��  1:�Ʒ�  2:��  3:��
};

//����Ÿ�� ����ü
struct tagCurrentTile
{
	int pageNumber;							//����Ÿ�� ��ȣ
	int sampleSizeX;						//����Ÿ�� x������
	int sampleSizeY;						//����Ÿ�� y������
	int sampleStartX;						//�巡�׽� ����Ÿ�� �����ϴ� X��ġ
	int sampleStartY;						//�巡�׽� ����Ÿ�� �����ϴ� Y��ġ
	int sampleStartPointX;
	int samplSetartPointY;
	int sampleEndX;							//�巡�׽� ����Ÿ�� ������ X��ġ
	int sampleEndY;							//�巡�׽� ����Ÿ�� ������ Y��ġ
	int sampleEndPointX;
	int sampleEndPointY;
	int x, y;						//Ÿ�� ��ǥ�� ����� (x, y�迭)
};