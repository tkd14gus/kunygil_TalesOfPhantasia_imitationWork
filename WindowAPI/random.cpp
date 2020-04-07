#include "stdafx.h"
#include "random.h"

HRESULT random::init()
{
	//랜덤시드 초기화
	srand(GetTickCount());

	return S_OK;
}

void random::release()
{
}

int random::Range(int num)
{
	return rand() % num;
}

int random::Range(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float random::Range(float num)
{
	//3 / 2 = 1
	//3.0 / 2.0 = 1.5
	//rand() => 0 ~ 32767
	//RAND_MAX => 32767
	//rand() / RAND_MAX => 값의 범위 : 0.0f ~ 1.0f
	return ((float)rand() / (float)RAND_MAX) * num;
}

float random::Range(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX); // 0.0f ~ 1.0f
	return (rnd * (max - min)) + min;
}
