#pragma once

class AABB
{
public:
	AABB();
	~AABB();

	// 2���� ���� ������ ���
	RECT m_BoundingVolume;


	// �߽�, ��/����
	int m_CenterPosX;	//
	int m_CenterPosY;

	int m_Width;		// ��
	int m_Height;		// ����


};

