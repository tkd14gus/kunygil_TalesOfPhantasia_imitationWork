#include "stdafx.h"
#include "imageTest.h"

HRESULT imageTest::init()
{
	//일반이미지 및 프레임 이미지 초기화
	_img = IMAGEMANAGER->addImage("미사일", "Images/missile.bmp", 26, 124);
	_frameImg = IMAGEMANAGER->addFrameImage("미사일1", "Images/missile1.bmp", 416, 64, 13, 1);
	_index = _count = 0;
	_angle = 0.0f;
	
	return S_OK;
}

void imageTest::release()
{
}

void imageTest::update()
{
	//프레임 이미지 애니메이션
	_count++;
	if (_count % 5 == 0)
	{
		_index++;
		if (_index > 13)
		{
			_index = 0;
		}
	}

	if (INPUT->GetKey(VK_UP))
	{
		_angle += 0.05f;
	}
}

void imageTest::render()
{
	//스케일렌더(이미지 크기변환)
	_img->render(getMemDC(), 100, 100);
	_img->scaleRender(getMemDC(), 300, 100, 2.0f);
	//프레임 이미지
	_frameImg->frameRender(getMemDC(), 100, 400, _index, 0);
	_frameImg->scaleFrameRender(getMemDC(), 300, 400, _index, 0, 2.0f);

	//로테이트렌더 (이미지 회전변환)
	_img->rotateRender(getMemDC(), 500, 100, _angle);
	_frameImg->rotateFrameRender(getMemDC(), 500, 400, _index, 0, _angle);
}
