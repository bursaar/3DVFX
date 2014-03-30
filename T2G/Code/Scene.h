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
				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 10; y++)
					{
						floor[x][y] = new FloorClass();
						mChildren.push_back(floor[x][y]);
					}
				}

				npc1->Move(-3,0,0);
				npc2->Move(2,0,0);

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
						floor[x][y]->Move(thenX, thenY, thenZ);
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

		private:
			SphereClass * npc1;
			SphereClass * npc2;
			FloorClass * floor[10][10];
			WallClass * wall;
			AIClass * ai;
		
	};
}