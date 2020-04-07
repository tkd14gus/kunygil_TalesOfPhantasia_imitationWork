#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//��ȣ������ Ŭ���� ���漱��
class enemyManager;

class player : public gameNode
{
private:
	enemyManager* _em;  //����� �����Ҵ� ��!!
	//���ΰ��ӿ��� ������ EM�� �÷��̾�� ������ EM��
	//���� �ٸ� �޸� �ּҶ� ���� ������ �� ����!!!

private:
	image* _rocket;		//����(�÷��̾�) �̹���
	//RECT _rcPlayer;		//�÷��̾� ������ ��Ʈ
	missile* _missile;	//�̻��� Ŭ����
	bomb* _bomb;		//��ź Ŭ����

	progressBar* _hpBar;	 //ü�¹�
	float _maxHp, _currentHp; //�ִ�ü��, ����ü��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//��źŬ���� ��������
	bomb* getBomb() { return _bomb; }

	//��ź����
	void removeBomb(int index);

	//�浹�Լ�(�÷��̾��Ѿ�, �̴Ͼ��浹)
	void collision();

	//������
	void hitDamage(float damage);

	//���̺�ε�
	void save();
	void load();

	//�÷��̾� �̹��� ��������
	image* getPlayerImg() { return _rocket; }

	//��ȣ������ ���Ŵ��� �����͸� �Ѱܹ��� �����Լ�
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

