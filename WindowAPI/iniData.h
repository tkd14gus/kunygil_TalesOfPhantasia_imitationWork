#pragma once
#include "singletonBase.h"
//=============================================================
//	## iniData ## (INI데이터 키=밸류)
//=============================================================

//INI데이터 구조체
struct tagIniData
{
	char* section;		//[Player]  => 섹션
	char* key;			//HP=100	=> HP가 키값
	char* value;		//MP=100	=> 100이 해당 값
};

class iniData : public singletonBase <iniData>
{
private:
	vector<tagIniData> _vIniData;

public:
	HRESULT init();
	void release();

	//데이터 추가하기
	void addData(const char* section, const char* key, const char* value);
	//세이브 파일이름
	void saveINI(const char* fileName);

	//문자로 값을 로드하기(파일이름, 섹션, 키)
	char* loadDataString(const char* fileName, const char* section, const char* key);
	//정수로 값을 로드하기(파일이름, 섹션, 키)
	int loadDataInteger(const char* fileName, const char* section, const char* key);
	//실수로 값을 로드하기(파일이름, 섹션, 키)
	float loadDataFloat(const char* fileName, const char* section, const char* key);

	iniData() {}
	~iniData() {}
};

