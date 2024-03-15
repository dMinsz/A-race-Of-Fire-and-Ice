#pragma once

//�������� ������ ������ ������ִ� Ŭ����

// ��������Ʈ �迭�� �ε����� �Ʒ��� enum���� ��������
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

	//�迭�� �̿��Ͽ�  pattern ���� // ����� vector<int>
	std::vector<ITEMPROPERTY> MakeOnePattern(ITEMPROPERTY* arr, int size);



	//ItemPatern �� ������ �߰��մϴ�.
	void MakePattern(std::vector<ITEMPROPERTY>onePattern);
	
	//�������ִ� ������ �������� �ϳ��� ������ �̾ƿɴϴ�.
	std::vector<ITEMPROPERTY>  GetRandomPattern();
	
	//�ش��ϴ� �ε����� ������ �̾ƿɴϴ�.
	std::vector<ITEMPROPERTY>  GetIndexPattern(int index);


	// ���� array �� ũ�� ���ϱ�
	int GetArraySize();
	
	
	//3�� �迭 ��Ÿ��
	std::vector<std::vector<ITEMPROPERTY>> MakeOnePattern3(ITEMPROPERTY arr[][3], int platformSize , int ItemMaxCount);

	void MakePattern3(std::vector<std::vector<ITEMPROPERTY>>onePattern);

	std::vector<std::vector<ITEMPROPERTY>>  GetRandomPattern3();
};
