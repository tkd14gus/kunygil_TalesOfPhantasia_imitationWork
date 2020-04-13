#pragma once
#include "gameNode.h"
#include "minion.h"  //�̴Ͼ� Ŭ���� ����ϱ� ����
#include "bullet.h"	 //�����Ѿ� Ŭ���� ����ϱ� ����
#include "enemy.h"

#define ENEMYAMOUNT 1 //�� ��(�ӽ�����)

//��ȣ������ Ŭ���� ���漱��
class player;

class enemyManager : public gameNode
{
private:
	player* _player;
	enemy* _enemy;

private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	vector<int> minionXPos;
	//vector<enemy*> _vBoss;
	bullet* _bullet; //�����Ѿ� Ŭ����
	int _count;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�̴Ͼ� ���� => �ʱ�ȭ�� �ִ´�
	void setMinion();
	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();
	//�̴Ͼ� ����
	void removeMinion(int index);

	//�̴Ͼ� ���� ��������
	vector<enemy*> getMinion() { return _vMinion; }
	void setMinion(vector<enemy*> vMinion) { _vMinion = vMinion; }


	void setBoss();

	//�浹�Լ� (�̴Ͼ���� �Ѿ˵�, �÷��̾�)
	void collision();

	//��ȣ������ �÷��̾� �����͸� ���� �����Լ�
	void setPlayerLink(player* player) { _player = player; }
	enemyManager() {}
	~enemyManager() {}
};

