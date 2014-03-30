#pragma once

#include "../../RenderableObject.h"
#include "../../SphereClass.h"
#include "../../FloorClass.h"
#include "../../WallClass.h"
#include "../../AIClass.h"

namespace Train2Game
{
	class Scene : public RenderableObject
	{
		public:
			void Initialise(RenderClass * pRenderer) override
			{
				ai = new AIClass;
				npc1 = new SphereClass(0xFFFF1234);
				mChildren.push_back(npc1);
				npc2 = new SphereClass(0xFF1234FF);
				mChildren.push_back(npc2);
				wall[0] = new WallClass;
				mChildren.push_back(wall[0]);

				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 10; y++)
					{
						floor[x][y] = new FloorClass();
						mChildren.push_back(floor[x][y]);
					}
				}

				npc1->Move(-3,0,1);
				npc2->Move(2,0,-4);
				// wall[0]->Move(0.0f, -19.0f, 0.0f);

				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 10; y++)
					{
						double nowX, nowY, nowZ;
						double thenX, thenY, thenZ;
						double scaleX, scaleY, scaleZ;
						floor[x][y]->GetPosition(nowX, nowY, nowZ);
						floor[x][y]->GetScale(scaleX, scaleY, scaleZ);
						thenX = nowX + (nowX * x * scaleX);
						thenY = nowY;
						thenZ = nowZ + (nowZ * y * scaleZ);
						floor[x][y]->Move((float)thenX, (float)thenY, (float)thenZ);
					}
				}

				RenderableObject::Initialise(pRenderer);


			}

			void CheckCollisions(RenderableObject* player)
			{
				if(!player->collidable)
					return;

				for (std::vector<RenderableObject *>::iterator it = mChildren.begin() ; it != mChildren.end(); ++it)
				{
					if ((*it)->collidable)
					{
						double plyrX,plyrY,plyrZ;
						player->GetPosition(plyrX,plyrY,plyrZ);
						double tgrX,tgrY,tgrZ;
						(*it)->GetPosition(tgrX,tgrY,tgrZ);
						double relX,relY,relZ;

						relX = pow(plyrX + tgrX,2);
						relY = pow(plyrY + tgrY,2);
						relZ = pow(plyrZ + tgrZ,2);

						double distance = sqrt(relX + relY + relZ);

						if(distance < ((*it)->radius + player->radius))
						{
							//Collision ahoy!
							player->OnCollide((*it));
							(*it)->OnCollide(player);
						}
						
					}
				}
			}

			void Update(double deltaTime, double totalTime) override
			{
				ai->Update(npc1);
				npc2->Move(0.0f, 0.0f, 0.01f);
				RenderableObject::Update(deltaTime, totalTime);
			}

			void RaiseWalls()
			{
				double posX, posY, posZ;
				double scaleX, scaleY, scaleZ;
				wall[0]->GetPosition(posX, posY, posZ);
				wall[0]->GetScale(scaleX, scaleY, scaleZ);
				if (posY < scaleY - 2)
				{
					wall[0]->Move(0.0f, 0.03f, 0.0f);
				}
			}

			void LowerWalls()
			{
				double posX, posY, posZ;
				double scaleX, scaleY, scaleZ;
				wall[0]->GetPosition(posX, posY, posZ);
				wall[0]->GetScale(scaleX, scaleY, scaleZ);
				if (posY > 0 - scaleY)
				{
					wall[0]->Move(0.0f, -0.08f, 0.0f);
				}
			}

		private:
			SphereClass * npc1;
			SphereClass * npc2;
			FloorClass * floor[10][10];
			AIClass * ai;
			WallClass * wall[10][10][4];				// A large array so that a maze of walls can be constructed.
		
			void Block(RenderableObject *pObject)
			{
				for (int x = 1; x <= 10; x++)
				{
					for (int y = 1; y <= 10; y++)
					{
						if (floor[x - 1][y - 1]->block)
						{
							double floorPosX, floorPosY, floorPosZ;
							double floorScaleX, floorScaleY, floorScaleZ;

							floor[x - 1][y - 1]->GetPosition(floorPosX, floorPosY, floorPosZ);
							floor[x - 1][y - 1]->GetScale(floorScaleX, floorScaleX, floorScaleZ);

							floor[x * y] = 
						}
					}
				}
			}
	};
}