#pragma once
#include "gameNode.h"

class imageTest : public gameNode
{
private:
	image* _img;		//�Ϲ� �̹���
	image* _frameImg;	//������ �̹���
	int _index, _count; //������ �̹����� �ִϸ��̼Ǻ���
	float _angle;		//ȸ�� ����


public:
	HRESULT init();
	void release();
	void update();
	void render();

	imageTest() {}
	~imageTest() {}
};

