#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init()
{
	return S_OK;
}

void iniTestScene::release()
{
}

void iniTestScene::update()
{
	//���̺�
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		//����, Ű, ���
		INIDATA->addData("�ù�19��", "�κ�", "100.99");
		INIDATA->addData("�ù�19��", "����", "1");
		INIDATA->addData("�ù�19��", "����", "10");

		//�̿� ���� ����� ����
		//�ٸ� ���ڷ� char*�� �ް� �ֱ⶧���� string�� char*���·� ��������� ��
		vector<string> vStr;
		vStr.push_back("50.5");
		vStr.push_back("111");
		vStr.push_back("7");

		INIDATA->addData("�÷��̾�", "���ݷ�", vStr[0].c_str());
		INIDATA->addData("�÷��̾�", "����", vStr[1].c_str());

		//���� �̸����� ���̺�
		INIDATA->saveINI("�ù��ù�");
	}
	//�ε�
	if (INPUT->GetKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("�ù��ù�", "�ù�19��", "�κ�");
		cout << num << endl;
	}
}

void iniTestScene::render()
{
}
