#pragma once

//아이템을 생성할 패턴을 만들어주는 클래스

// 스프라이트 배열에 인덱스를 아래의 enum으로 맞춰주자
enum 
{
	FIREITEM,
	ICEITEM,
	ICETRAP,
	FIRETRAP

};

struct ITEMPROPERTY
{
	int sprNum;
	int locationX;
};

struct ITEMPROPERTY3
{
	int platformNum;
	int sprNum;
	int locationX;
};



class ItemPatern
{

public:

	std::vector<std::vector<ITEMPROPERTY>>m_PatternArray;


	std::vector<std::vector<std::vector<ITEMPROPERTY>>>m_Pattern3Array;
	//ITEMPROPERTY m_Property;
public:

	//배열을 이용하여  pattern 생성 // 결과값 vector<int>
	std::vector<ITEMPROPERTY> MakeOnePattern(ITEMPROPERTY* arr, int size);



	//ItemPatern 에 패턴을 추가합니다.
	void MakePattern(std::vector<ITEMPROPERTY>onePattern);
	
	//가지고있는 패턴중 랜덤으로 하나의 패턴을 뽑아옵니다.
	std::vector<ITEMPROPERTY>  GetRandomPattern();
	
	//해당하는 인덱스에 패턴을 뽑아옵니다.
	std::vector<ITEMPROPERTY>  GetIndexPattern(int index);


	// 패턴 array 의 크기 구하기
	int GetArraySize();
	
	
	//3중 배열 스타일
	std::vector<std::vector<ITEMPROPERTY>> MakeOnePattern3(ITEMPROPERTY arr[][3], int platformSize , int ItemMaxCount);

	void MakePattern3(std::vector<std::vector<ITEMPROPERTY>>onePattern);

	std::vector<std::vector<ITEMPROPERTY>>  GetRandomPattern3();
};
