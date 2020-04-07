#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL), _scaleImage(NULL), _rotateImage(NULL)
{
}
image::~image()
{
}

//�� ��Ʈ�� �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� �������ؼ� �����ϰ� �ʱ�ȭ ������
	if (_imageInfo != NULL) this->release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� ��µ� �����ϸ� �ٷ� ����
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForAlphaBlend()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ��ʱ�ȭ
	//BlendOp => ����� AC_SRC_OVER�� ��밡��
	//BlendFlags => �� 0����, ���� �߸�, ���� OS���� ����ߴٴ� ���� ����
	//AlphaFormat => 24bit���� 0, 32bit���� AC_SRC_ALPHA ����ϸ� ������ �����̰� ������ �츰 �� 0
	//SourceConstantAlpha => ��Ʈ�� ���� ����
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//_blendFunc.SourceConstantAlpha = 255; // 0 ~ 255, 255�϶� ��������

	//�̹��� ���� ����ü ���� ������ �ʱ�ȭ �ϱ�
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::initForStretchBlt()
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//��Ʈ��ġ �̹��� �ʱ�ȭ
	_scaleImage = new IMAGE_INFO;
	_scaleImage->loadType = LOAD_EMPTY;
	_scaleImage->hMemDC = CreateCompatibleDC(hdc);
	_scaleImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_scaleImage->hOBit = (HBITMAP)SelectObject(_scaleImage->hMemDC, _scaleImage->hBit);
	_scaleImage->width = WINSIZEX;
	_scaleImage->height = WINSIZEY;

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForRotateImage(bool isFrameImage)
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//������Ʈ �̹��� �ʱ�ȭ
	if (isFrameImage) //������ �̹�����?
	{
		int size;
		(_imageInfo->frameWidth > _imageInfo->frameHeight ? size = _imageInfo->frameWidth : size = _imageInfo->frameHeight);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}
	else //�Ϲ� �̹�����?
	{
		int size;
		(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);
		_rotateImage = new IMAGE_INFO;
		_rotateImage->loadType = LOAD_EMPTY;
		_rotateImage->hMemDC = CreateCompatibleDC(hdc);
		_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
		_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
		_rotateImage->width = size;
		_rotateImage->height = size;
	}

	//DC �����ϱ�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
		
		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);
		
		//���� �÷�Ű �ʱ�ȭ
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	//���ĺ��� �̹��� ������ �ִٸ�
	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//������ ����
		SAFE_DELETE(_blendImage);
	}

	//�����̼� �̹��� ������ �ִٸ�
	if (_scaleImage)
	{
		//�̹��� ����
		SelectObject(_scaleImage->hMemDC, _scaleImage->hOBit);
		DeleteObject(_scaleImage->hBit);
		DeleteDC(_scaleImage->hMemDC);

		//������ ����
		SAFE_DELETE(_scaleImage);
	}

	//�����̼� �̹��� ������ �ִٸ�
	if (_rotateImage)
	{
		//�̹��� ����
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);

		//������ ����
		SAFE_DELETE(_rotateImage);
	}
}

//����(���� ���ϴ� ��ǥ�� ����ض�, �Ϲ������� RECT�� LT��ǥ�� �̹����� ���δ�)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			_imageInfo->width,	//������ �̹��� ����ũ��
			_imageInfo->height,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			0, 0,				//����� ����� ��������
			_imageInfo->width,	//���� ���� ����ũ��
			_imageInfo->height,	//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//����(���ϴ� ��ǥ�� �̹����� �߶� ���̱�)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,				//������ ����� DC
			destX,				//������ ��ǥ ����X
			destY,				//������ ��ǥ ����Y
			sourWidth,			//������ �̹��� ����ũ��
			sourHeight,			//������ �̹��� ����ũ��
			_imageInfo->hMemDC,	//����� ��� DC
			sourX, sourY,		//����� ����� ��������
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����ũ��
			_transColor);		//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϳ�?
	//���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ�� DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ������ => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����(���ĺ���)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, 0, 0, SRCCOPY);
		
		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,					//������ ��ǥ ����X
			0,					//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��带 ó�� ����ϳ�?
		//���ĺ��带 ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) this->initForAlphaBlend();
	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;


	if (_isTrans)//���� ���ְ� ���
	{
		//1. ����ȭ�� DC�� ������ => �����̹����� ����
		//2. �̹����޸�DC�� ������ ������ => �����̹����� ����
		//3. �����̹����� ȭ��DC�� ����(���ĺ���)

		//1
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, destX, destY, SRCCOPY);

		//2
		GdiTransparentBlt(
			_blendImage->hMemDC,	//������ ����� DC
			0,					//������ ��ǥ ����X
			0,					//������ ��ǥ ����Y
			_imageInfo->width,		//������ �̹��� ����ũ��
			_imageInfo->height,		//������ �̹��� ����ũ��
			_imageInfo->hMemDC,		//����� ��� DC
			0, 0,					//����� ����� ��������
			_imageInfo->width,		//���� ���� ����ũ��
			_imageInfo->height,		//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
		//3
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//���� �̹��� �״�� ���
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		//����� ����� ��������
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	//�̹��� ����ó��
	//int hp;
	//if(hp < 0) hp = 0;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans)//���� ���ְ� ���
	{
		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//������ ��ǥ ����X
			destY,						//������ ��ǥ ����Y
			_imageInfo->frameWidth,		//������ �̹��� ����ũ��
			_imageInfo->frameHeight,	//������ �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,		//����� ����� ��������
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor);				//�����Ҷ� ������ ����(�Ϲ������� ����Ÿ)
	}
	else//���� �̹��� �״�� ���
	{
		//BitBlt : DC���� �������� ��Ӻ��� ���ִ� �Լ�
		//�޸�DC -> ȭ��DC�� �����Ѵ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//������(offset)�� �Ϲ������� ���� ������Ʈ �ȿ��� ������Ʈ ó������ �־��� ��ҳ� Ư�� ���������� ������
	//offset�� � Ư���� ������ �ణ ���̰� ���� �� �Ǵ� �� ���� ��ü�� �ǹ�(���̿� ���� ������)
	
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(�Ϲݷ���-�̹����߶󼭺��̱�)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ���� ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ���� (ȭ��ũ��)
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ��������
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ��������
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ�(ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���Ұ��� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����(���ķ���-�̹����߶󼭺��̱�)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void image::scaleRender(HDC hdc, int destX, int destY, float scale)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
		//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_scaleImage) this->initForStretchBlt();

	_scaleImage->width = _imageInfo->width * scale;
	_scaleImage->height = _imageInfo->height * scale;

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_scaleImage->hMemDC, 0, 0, _scaleImage->width, _scaleImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//������ ����� DC
			destX,					//����� ��ǥ ������ X
			destY,					//����� ��ǥ ������ Y
			_scaleImage->width,	//����� �̹��� ����ũ��
			_scaleImage->height,	//����� �̹��� ����ũ��
			_scaleImage->hMemDC,	//����� ��� DC
			0, 0,					//���� ��������
			_scaleImage->width,	//���� ���� ����ũ��
			_scaleImage->height,	//���� ���� ����ũ��
			_transColor);			//�����Ҷ� ������ ���� (����Ÿ)

	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//���� �̹����� ũ�⸦ Ȯ��/��� �ؼ� ���� ��Ų��
		StretchBlt(hdc, destX, destY, _scaleImage->width, _scaleImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::scaleFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale)
{
	//��Ʈ��ġ�̹��� ó�� ����ϳ�?
		//�̹��� �����ϸ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_scaleImage) this->initForStretchBlt();

	_scaleImage->width = _imageInfo->width * scale;
	_scaleImage->height = _imageInfo->height * scale;
	_scaleImage->frameWidth = _scaleImage->width / (_imageInfo->maxFrameX + 1);
	_scaleImage->frameHeight = _scaleImage->height / (_imageInfo->maxFrameY + 1);

	if (_isTrans) //���� ���ٲ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		SetStretchBltMode(getMemDC(), COLORONCOLOR);
		StretchBlt(_scaleImage->hMemDC, 0, 0, _scaleImage->frameWidth, _scaleImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);

		//GdiTransparentBlt : ��Ʈ���� Ư�������� �����ϰ� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,							//������ ����� DC
			destX,							//����� ��ǥ ������ X
			destY,							//����� ��ǥ ������ Y
			_scaleImage->frameWidth,		//����� �̹��� ����ũ��
			_scaleImage->frameHeight,		//����� �̹��� ����ũ��
			_scaleImage->hMemDC,			//����� ��� DC
			0, 0,							//���� ��������
			_scaleImage->frameWidth,		//���� ���� ����ũ��
			_scaleImage->frameHeight,		//���� ���� ����ũ��
			_transColor);					//�����Ҷ� ������ ���� (����Ÿ)
	}
	else //���� �̹��� �׷��� ����Ҳ���?
	{
		//�����̹����� Scale�� ��ŭ Ȯ��/��ҽ��Ѽ� �׷��ش�
		StretchBlt(hdc, destX, destY, _scaleImage->frameWidth, _scaleImage->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::rotateRender(HDC hdc, float destX, float destY, float angle)
{
	//������Ʈ�̹��� ó�� ����ϳ�?
		//�̹��� ������Ʈ ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_rotateImage) this->initForRotateImage(false);

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			destX - _rotateImage->width / 2,
			destY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::rotateFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle)
{
	//������Ʈ�̹��� ó�� ����ϳ�?
		//�������̹��� ������Ʈ ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_rotateImage) this->initForRotateImage(true);

	POINT rPoint[3];
	int dist = sqrt((_imageInfo->frameWidth / 2) * (_imageInfo->frameWidth / 2) + (_imageInfo->frameHeight / 2) * (_imageInfo->frameHeight / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[1] = atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->frameHeight / 2) / ((float)_imageInfo->frameWidth / 2));

	for (int i = 0; i < 3; ++i)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle)* dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0,
			_rotateImage->width, _rotateImage->height,
			hdc, 0, 0, BLACKNESS);

		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			//_imageInfo->currentFrameX * _imageInfo->frameWidth,
			//_imageInfo->currentFrameY * _imageInfo->frameHeight,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);

		GdiTransparentBlt(hdc,
			destX - _rotateImage->width / 2,
			destY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0,
			0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, NULL, 0, 0);
	}
}

