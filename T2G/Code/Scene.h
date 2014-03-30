#pragma once

#include "../../RenderableObject.h"
#include "../../SphereClass.h"
#include "../../FloorClass.h"

namespace Train2Game
{
	class Scene : public RenderableObject
	{
		public:
			void Initialise(RenderClass * pRenderer) override
			{
				npc1 = new SphereClass(0xFFFF0000);
				mChildren.push_back(npc1);
				npc2 = new SphereClass(0xFF00FFFF);
				mChildren.push_back(npc2);
				floor = new FloorClass();
				mChildren.push_back(floor);

				npc1->Move(-1,0,0);
				npc2->Move(1,0,0);
				
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


		private:
			SphereClass * npc1;
			SphereClass * npc2;
			FloorClass * floor;
		
	};
}