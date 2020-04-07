#pragma once
//=============================================================
//	## image ## (앞으로 계속 업데이트 된다)
//=============================================================

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,  //리소스로 로딩(사용안함)
		LOAD_FILE,			//파일로 로딩
		LOAD_EMPTY,			//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		HDC hMemDC;			//메모리 DC
		HBITMAP hBit;		//비트맵
		HBITMAP hOBit;		//올드비트맵
		float x;				//이미지 x좌표
		float y;				//이미지 y좌표
		int width;			//이미지 가로길이
		int height;			//이미지 세로길이
		int currentFrameX;	//현재프레임X
		int currentFrameY;  //현재프레임Y
		int maxFrameX;		//최대 X프레임 갯수
		int maxFrameY;		//최대 Y프레임 갯수
		int frameWidth;		//1프레임 가로길이
		int frameHeight;	//1프레임 세로길이
		BYTE loadType;		//이미지 로드타입
		tagImage()			//생성자 = 초기화
		{
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_EMPTY;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	char*			_fileName;		//이미지 이름
	bool			_isTrans;		//배경색 없앨거냐?
	COLORREF		_transColor;	//배경색 없앨 RGB색상 (마젠타 = RGB(255, 0, 255))	
	
	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능

	LPIMAGE_INFO	_scaleImage;	//스케일이미지
	LPIMAGE_INFO	_rotateImage;	//로테이트이미지

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화 => 사용안해서 안만듬
	//이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	
	//알파블렌드 초기화
	HRESULT initForAlphaBlend();
	//스트레치렌더 초기화
	HRESULT initForStretchBlt();
	//로테이트렌더 초기화
	HRESULT initForRotateImage(bool isFrameImage);

	//해제
	void release();

	//렌더(내가 원하는 좌표에 출력해라, 일반적으로 RECT의 LT좌표에 이미지를 붙인다)
	void render(HDC hdc, int destX = 0, int destY = 0);
	//렌더(원하는 좌표에 이미지를 잘라서 붙이기)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	
	//알파렌더(이미지를 알파값만큼 투명화 시켜준다)
	//0(min) ~ 255(max)
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//루프렌더
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//스케일렌더 (이미지 크기)
	void scaleRender(HDC hdc, int destX, int destY, float scale = 1.0f);
	void scaleFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scale = 1.0f);

	//로테이트렌더 (이미지 회전)
	void rotateRender(HDC hdc, float destX, float destY, float angle);
	void rotateFrameRender(HDC hdc, float destX, float destY, int currentFrameX, int currentFrameY, float angle);


	//DC 얻기
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 x좌표
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//이미지 y좌표
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }
	//이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x + (_imageInfo->width / 2);
		_imageInfo->y = y + (_imageInfo->height / 2);
	}
	//이미지 가로, 세로크기
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//바운딩박스(충돌용 렉트)
	inline RECT boudingBox()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };
		return rc;
	}
	inline RECT boudingBoxWithFrame()
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };
		return rc;
	}
	//프레임X
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임Y
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}
	//이미지 1프레임 가로, 세로길이
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }
	//맥스 프레임
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }
};

