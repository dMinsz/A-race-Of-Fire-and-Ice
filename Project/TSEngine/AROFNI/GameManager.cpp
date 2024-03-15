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


	//1080 아래로 내려간 맵 들 재 세팅
	std::vector<GameObject*>::iterator it = m_Maps.begin();

	while (it != m_Maps.end())
	{
		//화면 밖으로 나간 오브젝트 위치 조정 및 아이템 재생성
		int overDist = (*it)->CheckOutOfBoundary(1080.0f);

		if (overDist != -999) // 매직넘버...
		{
			if (dynamic_cast<Item*>((*it)) != nullptr) // 아이템일때
			{
				it = m_Maps.erase(it);
				checkIteratorPlus = true;
			}
			else if (dynamic_cast<Trap*>((*it)) != nullptr) //트랩일때
			{
				it = m_Maps.erase(it);
				checkIteratorPlus = true;
			}
			else if (dynamic_cast<PlatForm*>((*it)) != nullptr)  //Platform 일때 //if (dynamic_cast<PlatForm*>((*it)) != nullptr) 
			{

				//patform 위치를 바꿔준다.
				POSITION tempPlatformPos;
				tempPlatformPos.x = (float)DEFALT_X;

				tempPlatformPos.y = (float)(*it)->m_Pos.y - 1440.0f - (float)overDist;

				m_testDebug = tempPlatformPos.y;

				(*it)->m_Pos = tempPlatformPos;

				//아이템 재생성
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

						//안좋은 방식같지만 급하다지금!
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

						//iterator 갱신
						it = m_Maps.begin();

					}
					else//아이템
					{
						Item* tempItem = new Item();

						POSITION tempItemPos;
						tempItemPos.x = (float)currentPattern[j].locationX;
						tempItemPos.y = (float)tempPlatformPos.y - (float)m_Info.SprItems[currentPattern[j].sprNum]->m_Height;
						tempItem->Init(tempItemPos.x, tempItemPos.y - (float)ITEM_OFFSET, m_Info.SprItems[currentPattern[j].sprNum]);

						//temp = tempItem;
						m_Maps.push_back(tempItem);

						//iterator 갱신

						it = m_Maps.begin();
					}
					
					//it = m_Maps.begin();

				}

			}

		}

		if (checkIteratorPlus == true)
		{
			checkIteratorPlus = false;
			//it++; // 패스해야함. erase 시 it++ 된다.
		}
		else // false 면
		{
			if (it != m_Maps.end())
			{
				it++;
			}
		}

		/// 위치 재조정및 아이템 재생성 끝

	}

}


void GameManager::Update(float dtime)
{


	Scrolling(dtime);


	//여기서 충돌체크한 캐릭터에 발판정보를 넣어준다
	//또한 아이템정보도 넣어줘도될듯?

	//현재 서잇는 발판을 구해서 오차를 수정하는 내용
	for (int i = 0; i < m_Maps.size(); i++)
	{
		//플레이어 1 발판 오차 수정
		if ((m_Player.Player1->m_CurrentStatus == JUMPL|| m_Player.Player1->m_CurrentStatus == JUMPR) // 캐릭터가 점프상태이고
			&& dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr) // 플랫폼일때
		{
			if (CollisionManager::CheckYBeteenCollision(m_Player.Player1, m_Maps[i]))
			{
				//여기서 캐릭터와 충돌된 플랫폼을 플레이어 에게  넣어준다
				m_Player.Player1->m_nowPlatform = dynamic_cast<PlatForm*>(m_Maps[i]);
			}
		}

		//플레이어 2 발판 오차 수정
		if ((m_Player.Player2->m_CurrentStatus == JUMPL || m_Player.Player2->m_CurrentStatus == JUMPR) // 캐릭터가 점프상태이고
			&& dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr) // 플랫폼일때
		{
			if (CollisionManager::CheckYBeteenCollision(m_Player.Player2, m_Maps[i]))
			{
				//여기서 캐릭터와 충돌된 플랫폼을 플레이어 에게  넣어준다
				m_Player.Player2->m_nowPlatform = dynamic_cast<PlatForm*>(m_Maps[i]);
			}
		}


	}


	//플레이어1
	for (int i = 0; i < m_Maps.size(); i++)
	{

		//아이템혹은 트랩과 충돌시

		if (dynamic_cast<Item*>(m_Maps[i]) != nullptr) //충돌중인게 아이템일때
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player1->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{
				//여기서 캐릭터와 충돌된 플랫폼을 플레이어 에게  넣어준다
				m_Player.Player1->m_hitObject = m_Maps[i];

				m_Player.Player1->m_CurrentMaps = &m_Maps;
			}
		}
		else if (dynamic_cast<Trap*>(m_Maps[i]) != nullptr) //충돌중인게 트랩일때
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


		//아이템혹은 트랩과 충돌시
		if (dynamic_cast<Item*>(m_Maps[i]) != nullptr ) //충돌중인게 아이템일때
		{
			if (CollisionManager::CheckCollision_AABB(m_Player.Player2->GetWorldAABB(), m_Maps[i]->GetWorldAABB()))
			{
				//여기서 캐릭터와 충돌된 플랫폼을 플레이어 에게  넣어준다
				m_Player.Player2->m_hitObject = m_Maps[i];

				m_Player.Player2->m_CurrentMaps = &m_Maps;
			}
		}
		else if(dynamic_cast<Trap*>(m_Maps[i]) != nullptr)  //충돌중인게 트랩일때
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

	//1080 아래로 내려간 맵 들 재 세팅
	SetOutObjects();
	



}

void GameManager::Draw(float dtime)
{
	//debug
	//TSEngine::GetEngine()->DrawTextT(TSEngine::GetEngine()->GetBackBufferDC(), 30, 100, RGB(255, 0, 0), "PlatForm 간격:%f", m_testDebug);
	
	for (int i = 0; i < m_Maps.size(); i++)
	{
		if (dynamic_cast<PlatForm*>(m_Maps[i]) != nullptr || dynamic_cast<Trap*>(m_Maps[i]) != nullptr) // 플랫폼일때
		{
			m_Maps[i]->Draw();
		}
	}


	m_Player.Player1->Draw(dtime);
	m_Player.Player2->Draw(dtime);
	
	for (int i = 0; i < m_Maps.size(); i++)
	{
		if (dynamic_cast<PlatForm*>(m_Maps[i]) == nullptr && dynamic_cast<Trap*>(m_Maps[i]) == nullptr) // 플랫폼일때
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

		//패턴관리
		std::vector<ITEMPROPERTY> currentPattern;

		if (m_Mode == MODE::EASY)
		{
			currentPattern = m_Info.EASYPattern->GetRandomPattern();
		}
		else if (m_Mode == MODE::NORMAL)
		{ //어차피 무조건  easy부터시작
			currentPattern = m_Info.NORMALPattern->GetRandomPattern();
		}
		//다른모드들도 추가
		
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
			else  //아이템
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
