#include "stdafx.h"
#include "ItemPatern.h"

std::vector<ITEMPROPERTY> ItemPatern::MakeOnePattern(ITEMPROPERTY* arr, int size)
{
	std::vector<ITEMPROPERTY>Result;

	for (int i = 0; i < size; i++)
	{
		Result.push_back(arr[i]);
	}


	return Result;
}

void ItemPatern::MakePattern(std::vector<ITEMPROPERTY> onePattern)
{
	m_PatternArray.push_back(onePattern);
}

std::vector<ITEMPROPERTY> ItemPatern::GetRandomPattern()
{
	int randomSize = m_PatternArray.size();

	int index = rand() % randomSize;

	return m_PatternArray[index];

}

std::vector<ITEMPROPERTY> ItemPatern::GetIndexPattern(int index)
{
	return m_PatternArray[index];
}

int ItemPatern::GetArraySize()
{
	return m_PatternArray.size();
}

std::vector<std::vector<ITEMPROPERTY>> ItemPatern::MakeOnePattern3(ITEMPROPERTY arr[][3], int platformSize, int ItemMaxCount)
{

	
	std::vector<std::vector<ITEMPROPERTY>> ResultArr;
	
	
	for (int i = 0; i < platformSize; i++)
	{
		std::vector<ITEMPROPERTY>arr2;

		for (int j = 0; j < ItemMaxCount; j++)
		{

			arr2.push_back(arr[i][j]);
		}


		ResultArr.push_back(arr2);
	}

	return ResultArr;
}

void ItemPatern::MakePattern3(std::vector<std::vector<ITEMPROPERTY>> onePattern)
{

	m_Pattern3Array.push_back(onePattern);
}

std::vector<std::vector<ITEMPROPERTY>> ItemPatern::GetRandomPattern3()
{


	int randomSize = m_Pattern3Array.size();

	int index = rand() % randomSize;

	return m_Pattern3Array[index];

}
