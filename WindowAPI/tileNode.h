#pragma once

//게임화면 타일
#define TILESIZE 48			//타일 픽셀
#define TILEX 120			//맵 타일의 가로가 몇 칸인지
#define TILEY 150			//맵 타일의 세로가 몇 칸인지
#define TILESIZEX (TILEX * TILESIZE)		//맵 타일의 가로축 픽셀 수
#define TILESIZEY (TILEY * TILESIZE)		//맵 타일의 세로축 픽셀 수

//이미지 타일(화면 우측상단에 붙여놓을 샘플타일)
#define SAMPLETILEX 12
#define SAMPLETILEY 6

//샘플타일 개수 정의
//정확한 개수를 모르기 때문에 임의로 3이라 정의
#define SMAPLETILECOUNT 3


//레이어 개수 정의
#define LAYERCOUNT 3
//지형
struct TERRAIN
{
	int x, y;		//타일(x, y)인지 저장.
};

//타일구조체
//한 타일당 레이어 개수 3개에요
struct tagTile
{
	TERRAIN terrain;
	RECT rc;
	bool canMove[LAYERCOUNT] = { false, };	//이 타일 위를 이동할 수 있는지 확인해주는 bool 변수
											//기본값 false
											//하나라도 false면 이 타일 위로는 이동할 수 없음
	bool direct[4] = { false, };			//이동이 가능하다면 어떤 방향으로 이동할 수 있는지 정의
											//true일 경우에만 이동 가능.
											//기본값 == false
											//0: 위, 1: 아래, 2: 좌, 3: 우
	int imagePage[LAYERCOUNT] = { -1, };	//어떤 샘플맵을 그렸는지 저장하는 변수
	int tileFrameX[LAYERCOUNT];				//imagePage의 가로로 몇 번째 타일인지 저장하는 변수
	int tileFrameY[LAYERCOUNT];				//imagePage의 세로로 면 번째 타일인지 저장하는 변수
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rc;

	int imagePage;							//샘플타일 번호
	int tileFrameX;							//가로 몇 번째에 그려지는지를 저장한 변수
	int tileFrameY;							//세로 몇 번째에 그려지는지를 저장한 변수
	
	bool canMove = false;					//이 타일로 이동이 가능한가?
											//기본값 : 이동불가
	bool direct[4] = { false, };			//이 타일에서 어떤 방향으로 이동이 가능한가?
											//기본값 : 이동불가
											//0:위  1:아래  2:좌  3:우
};

//현재타일 구조체
struct tagCurrentTile
{
	int pageNumber;							//샘플타일 번호
	int x, y;								//(x, y) 타일
};