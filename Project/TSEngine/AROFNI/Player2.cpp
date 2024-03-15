#include "stdafx.h"
#include "Player2.h"


void Player2::Init(int x, int y, int vMoveSize, float jumpsize, float jumpTarget, int status, TSprite* sprite[], int arrsize, TSprite* sprGage)
{
	m_CurrentStatus = status;
	m_VerticalMoveSize = vMoveSize;


	m_VerticalStart = x;
	m_VeticalBoundary = x + PLAYER_X_MAX;

	m_JumpSize = jumpsize;
	m_JumpTargetTime = jumpTarget;

	//����Ÿ��
	m_JumpTime = 0.0f;
	//�������
	m_Debug_jump = 0.0f;

	//�Դ½ð�
	m_EatTime = 0.0f;
	m_EatTargetTime = 0.2f;


	POSITION tempPos;
	tempPos.x = x;
	tempPos.y = y;

	m_Pos = tempPos;

	m_Hp = 100;

	//gage ����
	m_gage = new Gage();
	m_gage->Init(1027, 25, &m_Hp, sprGage, 0);



	//�ִϸ��̼� �� �������� ��������Ʈ ����
	for (int i = 0; i < arrsize; i++)
	{
		if (i == MOVELEFT)
		{

			AABB* Collision = new AABB();
			Collision->m_BoundingVolume.left = 40;
			Collision->m_BoundingVolume.top = 80;

			Collision->m_BoundingVolume.right = (sprite[i]->m_Width / sprite[i]->m_AniInfo.m_FrmMax) - 40;
			Collision->m_BoundingVolume.bottom = sprite[i]->m_Height;
			m_PlayerAABB.push_back(Collision);

			//��������Ʈ ���
			m_SpriteAni.push_back(sprite[i]);
		}
		else
		{
			AABB* Collision = new AABB();
			Collision->m_BoundingVolume.left = 40;
			Collision->m_BoundingVolume.top = 80;

			Collision->m_BoundingVolume.right = (sprite[i]->m_Width / sprite[i]->m_AniInfo.m_FrmMax) - 40;
			Collision->m_BoundingVolume.bottom = sprite[i]->m_Height;
			m_PlayerAABB.push_back(Collision);

			//��������Ʈ ���
			m_SpriteAni.push_back(sprite[i]);
		}


	}



	m_nowPlatform = nullptr;
	m_hitObject = nullptr;

}

void Player2::Update(float dtime)
{
	//update
	m_gage->Update(dtime);

	if (m_CurrentStatus == MOVERIGHT || m_CurrentStatus == MOVELEFT)
	{

		if (dynamic_cast<Trap*>(m_hitObject) != nullptr && m_hitObject != nullptr) // Ʈ���̸�
		{
			SoundManager::GetInstance()->PlayOnce(SoundList::ICEMISS);

			m_PrevedStatus = m_CurrentStatus;

			m_EatTime += dtime;

			if (m_EatTime > m_EatTargetTime) // ��ǥ Ÿ�� ���� 
			{

				m_EatTime = 0.0f;
				m_CurrentStatus = m_PrevedStatus;
				m_hitObject = nullptr;
			}
			else
			{
				AutoVerticalMove();
				AutoVerticalMove();
			}
		}
		AutoVerticalMove();
	}
	else if (m_CurrentStatus == JUMPR || m_CurrentStatus == JUMPL)
	{

		m_JumpTime += dtime;

		if (m_JumpTime > m_JumpTargetTime) // ��ǥ Ÿ�� ���� 
		{
			//���� ���� ���
			if (m_Debug_jump <= m_JumpSize)
			{
				m_Pos.y -= m_JumpSize - m_Debug_jump;
			}

			//���� ������� �ʱ�ȭ
			m_Debug_jump = 0.0f;


			if (m_nowPlatform != nullptr)
			{
				//�÷������� �浹 ��� �� ���� ����
				CollisionManager::PpDebug(this, m_nowPlatform);
			}

			m_JumpTime = 0.0f;

			m_CurrentStatus = m_PrevedStatus;
		}
		else
		{
			Jump(dtime);
		}

	}
	else if (m_CurrentStatus == GOODEAT)
	{

		m_EatTime += dtime;

		if (m_EatTime > m_EatTargetTime) // ��ǥ Ÿ�� ���� 
		{

			m_EatTime = 0.0f;
			m_CurrentStatus = m_PrevedStatus;


			//������ ����
			if (dynamic_cast<Trap*>(m_hitObject) == nullptr) //Ʈ���̾ƴϸ�
			{
				std::vector<GameObject*>::iterator it = m_CurrentMaps->begin();
				for (it = m_CurrentMaps->begin(); it != m_CurrentMaps->end(); it++)
				{
					if ((*it) == m_hitObject)
					{
						it = m_CurrentMaps->erase(it);
					}

				}
			}

			m_hitObject = nullptr;
		}

	}
	else if (m_CurrentStatus == MISSEAT)
	{
		m_EatTime += dtime;

		if (m_EatTime > m_EatTargetTime) // ��ǥ Ÿ�� ���� 
		{

			m_EatTime = 0.0f;
			m_CurrentStatus = m_PrevedStatus;
			m_hitObject = nullptr;
		}
	}




}

void Player2::Draw(float dtime)
{
	HDC backbuffer = TSEngine::GetEngine()->GetBackBufferDC();



	//�ִϸ��̼�
	TSEngine::GetEngine()->DrawAnimation(backbuffer, m_Pos.x, m_Pos.y, m_SpriteAni[m_CurrentStatus], dtime * 3.0f);


	//debug
	//TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 1, 1800, RGB(255, 0, 255), "Player2 hp : %d", m_Hp);

	//�浹ü���� �� ����׿� 
	/*RECT worldRECT;
	worldRECT = this->GetWorldAABB();
	TSEngine::GetEngine()->DrawRectangleDebug(worldRECT.left, worldRECT.top, worldRECT.right, worldRECT.bottom, RGB(255, 0, 0));*/

}

void Player2::Release()
{
	//for (int i = 0; i < m_SpriteAni.size(); i++)
	//{
	//	//TSEngine::GetEngine()->SpriteRelease(m_SpriteAni[i]);
	//	delete m_SpriteAni[i];
	//	m_SpriteAni[i] = nullptr;
	//}

	//for (int i = 0; i < m_PlayerAABB.size(); i++)
	//{

	//	delete m_PlayerAABB[i];
	//	m_PlayerAABB[i] = nullptr;
	//}

	m_gage->Release();
	//TSEngine::GetEngine()->SpriteRelease(m_SprGage);
}

void Player2::AutoDown(int downSize, float dtime)
{
	GameObject::AutoDown(downSize, dtime);

}

int Player2::CheckOutOfBoundary(int locationY)
{
	return GameObject::CheckOutOfBoundary(locationY);
}

void Player2::KeyInput()
{
	
	if (KeyState::InputKeyDown(VK_UP))
	{
		if (m_CurrentStatus != JUMPR && m_CurrentStatus != JUMPL
			&& m_CurrentStatus != MISSEAT && m_CurrentStatus != GOODEAT
			)
		{
			m_PrevedStatus = m_CurrentStatus;

			if (m_PrevedStatus == MOVERIGHT)
			{
				m_CurrentStatus = JUMPR;
			}
			else if (m_PrevedStatus == MOVELEFT)
			{
				m_CurrentStatus = JUMPL;
			}

		}

	}

	 if (KeyState::InputKeyDown(VK_RETURN))
	{

		if (m_CurrentStatus != JUMPR && m_CurrentStatus != JUMPL
			&& m_CurrentStatus != MISSEAT && m_CurrentStatus != GOODEAT
			)
		{
			m_PrevedStatus = m_CurrentStatus;


			if (dynamic_cast<Trap*>(m_hitObject) != nullptr || m_hitObject == nullptr) //Ʈ���̸�
			{
				SoundManager::GetInstance()->PlayOnce(SoundList::ICEMISS);

				m_CurrentStatus = MISSEAT;
				//m_Hp -= 30;

				if (m_Hp >= 30)
				{
					m_Hp -= 30;
				}
				else if (m_Hp <= 30)
				{
					m_Hp = 0;
				}


			}
			else if (CollisionManager::CheckCollision_AABB(this->GetWorldAABB(), m_hitObject->GetWorldAABB())) //�浹 ��Ȯ��
			{
				SoundManager::GetInstance()->PlayOnce(SoundList::ICEEAT);

				m_CurrentStatus = GOODEAT;

				if (m_Hp <= 70)
				{
					m_Hp += 30;
				}
				else if (m_Hp >= 70)
				{
					m_Hp = 100;
				}
			}
			else
			{
				SoundManager::GetInstance()->PlayOnce(SoundList::ICEMISS);

				if (m_Hp >= 0)
				{
	
					m_CurrentStatus = MISSEAT;
					m_Hp -= 20;
				}
			}
		}

	}



}

void Player2::AutoVerticalMove()
{
	int overRight = CheckOutOfXRight();
	int overLeft = CheckOutOfXLeft();

	//����üũ
	if (overRight != -999) // ������ �Ѿ
	{
		m_CurrentStatus = MOVELEFT;
	}
	else
	{
		overRight = 0;
	}

	if (overLeft != -999)
	{
		m_CurrentStatus = MOVERIGHT;
	}
	else
	{
		overLeft = 0;
	}


	//
	if (m_CurrentStatus == MOVERIGHT)
	{
		m_Pos.x += m_VerticalMoveSize + overLeft;
	}


	if (m_CurrentStatus == MOVELEFT)
	{
		m_Pos.x -= m_VerticalMoveSize + overRight; //���������� �����Ÿ�ŭ �����ش�.
	}


}

void Player2::Jump(float dtime)
{

	float offset = 1.0 / m_JumpTargetTime;


	m_Pos.y -= (float)m_JumpSize * dtime * offset; //���οö󰡴°� -
	m_Debug_jump += (float)m_JumpSize * dtime * offset;

}

RECT Player2::GetWorldAABB()
{
	RECT _worldAABB;

	_worldAABB.left = m_PlayerAABB[m_CurrentStatus]->m_BoundingVolume.left + m_Pos.x;
	_worldAABB.right = m_PlayerAABB[m_CurrentStatus]->m_BoundingVolume.right + m_Pos.x;
	_worldAABB.top = m_PlayerAABB[m_CurrentStatus]->m_BoundingVolume.top + m_Pos.y;
	_worldAABB.bottom = m_PlayerAABB[m_CurrentStatus]->m_BoundingVolume.bottom + m_Pos.y;

	return _worldAABB;
}

int Player2::CheckOutOfXRight()
{
	if (m_Pos.x >= m_VeticalBoundary)
	{
		return (m_Pos.x - m_VeticalBoundary); //���������ش�..
	}

	return -999; //�����ѹ�
}

int Player2::CheckOutOfXLeft()
{
	if (m_Pos.x <= m_VerticalStart)
	{
		return (m_Pos.x - m_VerticalStart); //���������ش�..
	}

	return -999; //�����ѹ�
}
