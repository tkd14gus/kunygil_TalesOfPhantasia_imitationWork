#pragma once
#include "gameNode.h"
#include "player.h"
#include "tileNode.h"

class inGameScene : public gameNode
{
private:
	player* _player; //�÷��̾� Ŭ����
	subplayer* _subPlayer;
private:
	tagTile _tiles[TILEX * TILEY];	//�ΰ���ȭ�鿡 ���Ǵ� Ÿ�� �� 400��
	RECT _rcScreen;		//ȭ�� ī�޶� Rect;
						//�� Rect�� �浹�� Ÿ�ϸ� ȭ�鿡 �׷�����.
	RECT rc;			//IntersectRect�ϱ� ���� ����� �� ��Ʈ

	RECT _stateRC[4];	//state�� ���� �� ĳ����â �ϳ��� ����ϴ� ��Ʈ
private:

	int _mapLocation;	// ���� �����;� �ϴ� ���� ��������
						// 0�̸� ����
						// 1�̸� �ʵ�
						// 2�̸� ����

	char _fileName[128] = { 0, };	//�� ������ �̸��� �޾ƿ� ����

	char _stateWin[128];			//�������� â���� TextOut�� ���� ��� ���⿡ ��Ƶΰ� ����Ѵ�.

	bool _isStateWinOpen;			// ����â�� �״��� Ȯ���ϴ� �Լ�

	int _saveDirect;				//playerŬ������ _direct�� ������ �Լ�
									//����â�� ���� ���ö� ���� ���� �ٶ� �� �ְ� �ϱ� ���� ��ġ


public:
	HRESULT init();
	void release();
	void update();
	void render();

	inGameScene() {}
	~inGameScene() {}

	//_mapLocation�� �޾� ���� �������ִ� �Լ�.
	void mapSetting(int mapLocation);
	//�� �Ѿ�� �Լ�
	//void changeMap();

	//Ÿ���� �÷��̾� ��ġ�� �°� �������ִ� �Լ�
	void tileSetting();
	//�ʵ��� �� Ȯ�������� ��Ʋ������ �Ѿ�� �Լ�
	void changeBattleScene();
};



