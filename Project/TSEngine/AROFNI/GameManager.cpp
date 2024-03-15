#include "stdafx.h"
#include "GameManager.h"

void GameManager::Init(MAPINFO info, PLAYERINFO Player)
{
	m_Info = info;
	m_Player = Player;
	m_Mode = MODE::EASY;
}

void GameManager::SetOutObjects() 
{
	bool checkIteratorPlus = false;
	float offset = 0.0f;
	float platformtempY = 0.0f;


	//1080 �Ʒ��� ������ �� �� �� ����
	std::vector<GameObject*>::iterator it = m_Maps.begin();

	while (it != m_Maps.end())
	{
		//ȭ�� ������ ���� ������Ʈ ��ġ ���� �� ������ �����
		int overDist = (*it)->CheckOutOfBoundary(1080.0f);

		if (overDist != -999) // �����ѹ�...
		{
			if (dynamic_cast<Item*>((*it)) != nullptr) // �������϶�
			{
				it = m_Maps.erase(it);
				checkIteratorPlus = true;
			}
			else if (dynamic_cast<Trap*>((*it)) != nullptr) //Ʈ���϶�
			{
				it = m_Maps.erase(it);
				checkIteratorPlus = true;
			}
			else if (dynamic_cast<PlatForm*>((*it)) != nullptr)  //Platform �϶� //if (dynamic_cast<PlatForm*>((*it)) != nullptr) 
			{

				//patform ��ġ�� �ٲ��ش�.
				POSITION tempPlatformPos;
				tempPlatformPos.x = (float)DEFALT_X;

				tempPlatformPos.y = (float)(*it)->m_Pos.y - 1440.0f - (float)overDist;

				m_testDebug = tempPlatformPos.y;

				(*it)->m_Pos = tempPlatformPos;

				//������ �����
				std::vector<ITEMPROPERTY> currentPattern;

				if (m_Mode == MODE::EASY)
				{
					currentPattern = m_Info.EASYPattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::NORMAL)

				{
					currentPattern = m_Info.NORMALPattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HARD0)

				{
					currentPattern = m_Info.HARD00Pattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HARD1)

				{
					currentPattern = m_Info.HARD01Pattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HARD2)

				{
					currentPattern = m_Info.HARD02Pattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HARD3)

				{
					currentPattern = m_Info.HARD03Pattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HARD4)

				{
					currentPattern = m_Info.HARD04Pattern->GetRandomPattern();
				}
				else if (m_Mode == MODE::HELL)

				{
					currentPattern = m_Info.HELLPattern->GetRandomPattern();
				}


				for (int j = 0; j < currentPattern.size(); j++)
				{
					//GameObject* temp;

					if (currentPattern[j].sprNum == ICETRAP || currentPattern[j].sprNum == FIRETRAP)
					{

						//������ ��İ����� ���ϴ�����!
						int index = 0;

						if (currentPattern[j].sprNum == ICETRAP)
						{
							index = 0;
						}
						else if (currentPattern[j].sprNum == FIRETRAP) 
						{
							index = 1;
						}


						Trap* tempTrap = new Trap();

						POSITION tempTrapPos;
						tempTrapPos.x = (float)currentPattern[j].locationX;
						tempTrapPos.y = (float)tempPlatformPos.y - (float)m_Info.SprTrap[index]->m_Height;
						tempTrap->Init(tempTrapPos.x, tempTrapPos.y + (float)TRAP_OFFSET, m_Info.SprTrap[index]);

						//temp = tempTrap;
						m_Maps.push_back(tempTrap);

						//iterator ����
						it = m_Maps.begin();

					}
					else//������
					{
						Item* tempItem = new Item();

						POSITION tempItemPos;
						tempItemPos.x = (float)currentPattern[j].locationX;
						tempItemPos.y = (float)tempPlatformPos.y - (float)m_Info.SprItems[currentPattern[j].sprNum]->m_Height;
						tempItem->Init(tempItemPos.x, tempItemPos.y - (float)ITEM_OFFSET, m_Info.SprItems[currentPattern[j].sprNum]);

						//temp = tempItem;
						m_Maps.push_back(tempItem);

						//iterator ����

						it = m_Maps.begin();
					}
					
					//it = m_Maps.begin();

				}

			}

		}

		if (checkIteratorPlus == true)
		{
			checkIteratorPlus = false;
			//it++; // �н��ؾ���. erase �� it++ �ȴ�.
		}
		else // false ��
		{
			if (it != m_Maps.end())
			{
				it++;
			}
		}

		/// ��ġ �������� ������ ����� ��

	}

}


void GameManager::Update(float dtime)
{


	Scrolling(dtime);


	//���⼭ �浹üũ�� ĳ���Ϳ� ���������� �־��ش�
	//���� ������������ �־��൵�ɵ�?

	//���� ���մ� ������ ���ؼ� ������ �����ϴ� ����
	for (int i = 0; i < m_Maps.size(); i++)
	{
		//�÷��̾� 1 ���� ���� ����
		if ((m_Player.Player1->m_CurrentStatus == JUMPL|| m_Player.Player1->m_CurrentStatus == JUMPR) // ĳ���Ͱ� ���������̰�
			&& dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr) // �÷����϶�
		{
			if (CollisionManager::CheckYBeteenCollision(m_Player.Player1, m_Maps[i]))
			{
				//���⼭ ĳ���Ϳ� �浹�� �÷����� �÷��̾� ����  �־��ش�
				m_Player.Player1->m_nowPlatform = dynamic_cast<PlatForm*>(m_Maps[i]);
			}
		}

		//�÷��̾� 2 ���� ���� ����
		if ((m_Player.Player2->m_CurrentStatus == JUMPL || m_Player.Player2->m_CurrentStatus == JUMPR) // ĳ���Ͱ� ���������̰�
			&& dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr) // �÷����϶�
		{
			if (CollisionManager::CheckYBeteenCollision(m_Player.Player2, m_Maps[i]))
			{
				//���⼭ ĳ���Ϳ� �浹�� �÷����� �÷��̾� ����  �־��ش�
				m_Player.Player2->m_nowPlatform = dynamic_cast<PlatForm*>(m_Maps[i]);
			}
		}


	}


	//�÷��̾�1
	for (int i = 0; i < m_Maps.size(); i++)
	{

		//������Ȥ�� Ʈ���� �浹��

		if (dynamic_cast<Item*>(m_Maps[i]) != nullptr) //�浹���ΰ� �������϶�
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player1->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{
				//���⼭ ĳ���Ϳ� �浹�� �÷����� �÷��̾� ����  �־��ش�
				m_Player.Player1->m_hitObject = m_Maps[i];

				m_Player.Player1->m_CurrentMaps = &m_Maps;
			}
		}
		else if (dynamic_cast<Trap*>(m_Maps[i]) != nullptr) //�浹���ΰ� Ʈ���϶�
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player1->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{

				if (m_Player.Player1->m_Hp >= 1)
				{
					m_Player.Player1->m_Hp -= 2;
				}
				//m_Player.Player1->m_CurrentStatus = MISSEAT;
				m_Player.Player1->m_hitObject = dynamic_cast<Trap*>(m_Maps[i]);

			}
		}


		//������Ȥ�� Ʈ���� �浹��
		if (dynamic_cast<Item*>(m_Maps[i]) != nullptr ) //�浹���ΰ� �������϶�
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player2->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{
				//���⼭ ĳ���Ϳ� �浹�� �÷����� �÷��̾� ����  �־��ش�
				m_Player.Player2->m_hitObject = m_Maps[i];

				m_Player.Player2->m_CurrentMaps = &m_Maps;
			}
		}
		else if(dynamic_cast<Trap*>(m_Maps[i]) != nullptr)  //�浹���ΰ� Ʈ���϶�
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player2->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{
				if (m_Player.Player1->m_Hp >= 1)
				{
					m_Player.Player2->m_Hp -= 2;
				}
				//m_Player.Player2->m_CurrentStatus = MISSEAT;
				m_Player.Player2->m_hitObject = dynamic_cast<Trap*>(m_Maps[i]);
			}
		}

	}

	

	m_Player.Player1->Update(dtime);
	m_Player.Player2->Update(dtime);

	//1080 �Ʒ��� ������ �� �� �� ����
	SetOutObjects();
	



}

void GameManager::Draw(float dtime)
{
	//debug
	//TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 30, 100, RGB(255, 0, 0), "PlatForm ����:%f", m_testDebug);
	
	for (int i = 0; i < m_Maps.size(); i++)
	{
		if (dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr || dynamic_cast<Trap*>(m_Maps[i]) != nullptr) // �÷����϶�
		{
			m_Maps[i]->Draw();
		}
	}


	m_Player.Player1->Draw(dtime);
	m_Player.Player2->Draw(dtime);
	
	for (int i = 0; i < m_Maps.size(); i++)
	{
		if (dynamic_cast<PlatForm*>(m_Maps[i]) == nullptr && dynamic_cast<Trap*>(m_Maps[i]) == nullptr) // �÷����϶�
		{
			m_Maps[i]->Draw();
		}
	}

	//m_Player.Player1->m_gage->Draw();
	//m_Player.Player2->m_gage->Draw();
}

void GameManager::Release()
{

	//m_Info.SprItems

	m_Player.Player1->Release();
	m_Player.Player2->Release();

	for (int i = 0; i < m_Maps.size(); i++)
	{
		m_Maps[i]->Release();
	}

	for (int i = 0; i < 2; i++)
	{

		TSEngine::GetEngine()->SpriteRelease(m_Info.SprItems[i]);
	}

	/*for (int i = 0; i < 2; i++)
	{

		TSEngine::GetEngine()->SpriteRelease(m_Info.SprItems[i]);
	}*/

}

void GameManager::GenerateMap()
{
	for (int i = 0; i < PLATFORM_MAX; i++)
	{
		PlatForm* tempPlatform = new PlatForm();


		POSITION tempPlatformPos;
		tempPlatformPos.x = (float)DEFALT_X;
		tempPlatformPos.y = (float)DEFALT_Y - (((float)m_Info.FInterval + (float)m_Info.SprPlatForm->m_Height) * (float)i);
		tempPlatform->Init(tempPlatformPos.x, tempPlatformPos.y, m_Info.SprPlatForm);


		m_Maps.push_back(tempPlatform);
		//m_Maps[i] =tempPlatform;
		//0~5

		//���ϰ���
		std::vector<ITEMPROPERTY> currentPattern;

		if (m_Mode == MODE::EASY)
		{
			currentPattern = m_Info.EASYPattern->GetRandomPattern();
		}
		else if (m_Mode == MODE::NORMAL)
		{ //������ ������  easy���ͽ���
			currentPattern = m_Info.NORMALPattern->GetRandomPattern();
		}
		//�ٸ����鵵 �߰�
		
		for (int j = 0; j < currentPattern.size(); j++)
		{
			if (currentPattern[j].sprNum == ICETRAP || currentPattern[j].sprNum == FIRETRAP)
			{
				Trap* tempTrap = new Trap();

				POSITION tempItemPos;
				tempItemPos.x = (float)currentPattern[j].locationX;
				tempItemPos.y = tempPlatformPos.y - m_Info.SprItems[currentPattern[j].sprNum]->m_Height;

				tempTrap->Init(tempItemPos.x, tempItemPos.y + TRAP_OFFSET, m_Info.SprItems[currentPattern[j].sprNum]);

				m_Maps.push_back(tempTrap);

			}
			else  //������
			{
				Item* tempItem = new Item();

				POSITION tempItemPos;
				tempItemPos.x = (float)currentPattern[j].locationX;
				tempItemPos.y = tempPlatformPos.y - m_Info.SprItems[currentPattern[j].sprNum]->m_Height;

				tempItem->Init(tempItemPos.x, tempItemPos.y-ITEM_OFFSET, m_Info.SprItems[currentPattern[j].sprNum]);

				m_Maps.push_back(tempItem);
			}

		}
	}
	
}

void GameManager::Scrolling(float dtime)
{
	
	m_Player.Player1->AutoDown(m_Info.ScrollDownSize, dtime);
	m_Player.Player2->AutoDown(m_Info.ScrollDownSize, dtime);

	for (int i = 0; i < m_Maps.size(); i++)
	{
		m_Maps[i]->AutoDown(m_Info.ScrollDownSize,dtime);

		/*TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 
			m_Maps[i]->m_Pos.x, m_Maps[i]->m_Pos.y - 15, RGB(255, 0, 255), "POS: %d : %02d", m_Maps[i]->m_Pos.x, m_Maps[i]->m_Pos.y);*/

	}

}

void GameManager::SetScrollSpeed(float ScrollDownSize)
{
	m_Info.ScrollDownSize = ScrollDownSize;
}

void GameManager::SetPlusScrollSpeed(float ScrollDownSize)
{
	m_Info.ScrollDownSize += ScrollDownSize;

}
