#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//Ŭ���� �ʱ�ȭ�� �̰����� �Ѵ�
	
	/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
	//������ ������ ���ΰ��� ������ �Ѵ�

	/*���߰�*/
	SCENEMANAGER->addScene("����ȭ��", new startScene);
	SCENEMANAGER->addScene("����ȭ��", new inGameScene);
	SCENEMANAGER->addScene("INI�׽�Ʈ", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("�ȼ��浹", new pixelCollisionScene);
	SCENEMANAGER->addScene("����", new soundTestScene);
	SCENEMANAGER->addScene("��������", new maptoolScene);
	

	/*����� ����*/
	SCENEMANAGER->loadScene("�ε�ȭ��");


	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();

}

//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

//=============================================================
//	## ���� ## render()
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
//=============================================================	
	
	//���ڻ� ��� ���ֱ�
	SetBkMode(getMemDC(), TRANSPARENT);
	//���Ŵ��� ����
	SCENEMANAGER->render();

//=============================================================
	//������� ������ ȭ��DC�� �׸���
	this->getBackBuffer()->render(getHDC());
}
