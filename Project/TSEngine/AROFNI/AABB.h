#pragma once

class AABB
{
public:
	AABB();
	~AABB();

	// 2개의 점의 정보로 충분
	RECT m_BoundingVolume;


	// 중심, 폭/높이
	int m_CenterPosX;	//
	int m_CenterPosY;

	int m_Width;		// 폭
	int m_Height;		// 높이


};

