#pragma once
#include "gameNode.h"

class imageTest : public gameNode
{
private:
	image* _img;		//일반 이미지
	image* _frameImg;	//프레임 이미지
	int _index, _count; //프레임 이미지용 애니메이션변수
	float _angle;		//회전 각도


public:
	HRESULT init();
	void release();
	void update();
	void render();

	imageTest() {}
	~imageTest() {}
};

