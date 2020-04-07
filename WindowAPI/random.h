#pragma once
#include "singletonBase.h"

class random : public singletonBase <random>
{
public:
	HRESULT init();
	void release();

	int Range(int num);
	int Range(int min, int max);
	float Range(float num);
	float Range(float min, float max);

	random() {}
	~random() {}
};

