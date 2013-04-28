;//==============================================================================
#include "CApp.h"
#include "CEntity.h"
#include "CExplode.h"
#include "CInsect.h"
#include "CWhip.h"
#include <vector>
#include <iostream>
//==============================================================================
void CApp::OnLoop() {
    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnLoop();//call the loop function of each entity
    }

	//loop through all collision incidents
    for(int i = 0;i < CEntityCol::EntityColList.size();i++) {
       CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;//load first entity
       CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;//load second entity
 
       if(EntityA == NULL || EntityB == NULL) continue;//if there were no entitys colided with then keep going
 
       if(EntityA->OnCollision(EntityB)) {//load oncollision for entity A with b
           EntityB->OnCollision(EntityA);//load onCollision for entity b with a
       }
    }
 
    CEntityCol::EntityColList.clear();//clear the collision list

    CFPS::FPSControl.OnLoop();//loop to check the frames per second

    char Buffer[255];
    sprintf(Buffer, "%d", CFPS::FPSControl.GetFPS());
    SDL_WM_SetCaption(Buffer, Buffer);// set the caption of game


	if(metroid) {//if we are playing samus update the appropriate enemys on her current position
		Enemy3.playerPos = Samus.X;
		Enemy3.yPlayerPos= Samus.Y;
		Enemy4.playerPos = Samus.X;
		Enemy4.yPlayerPos = Samus.Y;
		if(Samus.Dead==true) {//if she is dead
			OnGameOver();//run onGameOver
		}
	}	
		
	if(castlevania) {//if we are playing simon update the appropriate enemys on his current position
		Enemy3.playerPos = Simon.X;
		Enemy3.yPlayerPos = Simon.Y;
		Enemy4.playerPos = Simon.X;
		Enemy4.yPlayerPos = Simon.Y;
		if(Simon.Dead==true) {//if he is dead
			OnGameOver();//run onGameOver
		}
		if(Simon.Attack && Simon.AttackTimer > 30 && Simon.AttackTimer <= 90 && Simon.PointUp) {//if simon has been attacking for 30 cycles already and is pointing up
			CWhip* VerticalWhip = new CWhip;//declare a new verticalwhip entity
			VerticalWhip->OnLoad("./images/VerticalWhip.png", 6, 52, 2);//load its image
			if(Simon.faceRight) {//if hes facing to the right make the whip appear in the appropriate spot in relation to simon
				VerticalWhip->X = Simon.X + 19;
				VerticalWhip->Y = Simon.Y - 52;
				VerticalWhip->CurrentFrameCol = 0;
			}
			if(Simon.faceLeft) {//if hes facing left find the right spot
				VerticalWhip->X = Simon.X + 6;
				VerticalWhip->Y = Simon.Y - 52;
				VerticalWhip->CurrentFrameCol = 1;
			}
			CEntity::EntityList.push_back(VerticalWhip);//push the whip into the entity list
		}
		else if(Simon.Attack && Simon.AttackTimer > 60 && Simon.AttackTimer <= 90 && !Simon.PointUp) {//if simon has been attacking for 60 cycles already and is not pointin up
			CWhip* HorizontalWhip = new CWhip;//declare a new horizontalwhip entity
			HorizontalWhip->OnLoad("./images/HorizontalWhip.png", 50, 5, 2);//load the image
			if(Simon.faceRight) {//if simon is facing to the right make it appear in the correct spot
				HorizontalWhip->X = Simon.X + 30;
				HorizontalWhip->Y = Simon.Y + 15;
				HorizontalWhip->CurrentFrameCol = 0;
			}
			if(Simon.faceLeft) {//if simon is facing to the left make it appear in the correct spot
				HorizontalWhip->X = Simon.X - 50;
				HorizontalWhip->Y = Simon.Y + 15;
				HorizontalWhip->CurrentFrameCol = 1;
			}
			CEntity::EntityList.push_back(HorizontalWhip);//push the entity into the list
		}
			
	}

	std::vector<CEntity*>::iterator i;//declare an iterator of type centity pointer
	enemyCounter = 0;//reset the counter so that we can count the number of enemys again
	for(i = CEntity::EntityList.begin(); i != CEntity::EntityList.end(); i++){
		if(((*i)->Type == ENTITY_TYPE_DOG) || ((*i)->Type == ENTITY_TYPE_INSECT) || ((*i)->Type == ENTITY_TYPE_SKELETON)){//if the entity is a killable enemy, increment the counter
			enemyCounter++;
		}
		if(((*i)->Type == ENTITY_TYPE_BULLET) && ((*i)->Dead == true)){//if the entity is of type bullet and its "dead"
			CExplode* expl = new CExplode;//declare a new entity of type explode
			expl->OnLoad("images/ShotDeath.png",34,34,0);//load the image of a shot "dieing"
			expl->X = (*i)->X-12;//find the proper coordinants of the explosion
			expl->Y = (*i)->Y-12;
			expl->fm = 7;
			expl->cyclelimit = 160;
			delete(*i);//delete the bullet
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);//remove it from the list
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(expl); //pushes back the explosion after deleting the bullet
		}

		if(((*i)->Type == ENTITY_TYPE_INSECT) && ((*i)->Dead == true)){//if the entity is of type insect and its dead
			(*i)->OnCleanup();//clean it up
			CExplode* bug = new CExplode;//declare a new entity of type explode (its our death class)
			bug->OnLoad("images/InsectDeath.png",60,50,0);//load the image of insect death
			bug->X = (*i)->X;//find the proper coordinants of the insect
			bug->Y = (*i)->Y;
			bug->fm = 4;
			bug->cyclelimit = 160;
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);//pop the insect out
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(bug); //push back the bug
		}
		if(((*i)->Type == ENTITY_TYPE_SKELETON) && ((*i)->Dead == true)){//if the entity is of type skeleton and its dead
			CExplode* bones = new CExplode;//declare its death entity
			bones->OnLoad("images/SkeletonDeath.png",30,52,0);//load its death image
			bones->X = (*i)->X;//update location
			bones->Y = (*i)->Y;
			bones->fm = 7;
			bones->cyclelimit = 200;
			(*i)->OnCleanup();//clean up skeleton
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);//pop skeleton out of list
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(bones); //push back the skeleton death
		}
		
		if (((*i)->Type == ENTITY_TYPE_DOG) && ((*i)->Dead == true)) {//if entity is of type dog and its dead
			CExplode* mutt = new CExplode;//declare its death entity
			mutt->OnLoad("images/DogDeath.png",35,25,0);//load its death image
			mutt->X = (*i)->X;//update its position
			mutt->Y = (*i)->Y;
			mutt->fm = 7;
			mutt->cyclelimit = 200;
			(*i)->OnCleanup();//clean it up
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);//pop the dog out
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
			CEntity::EntityList.push_back(mutt);//push back dog death
		}
		if(((*i)->Type == ENTITY_TYPE_WHIP) && ((Simon.AttackTimer <= 60 && !Simon.PointUp) || (Simon.AttackTimer <= 30 && Simon.PointUp))){//if simon is not facing up and has been attacking less then 60 cycles or if he is facing up and has been attacking for less then 30 cycles
			delete(*i);//delete it
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--);//pop it out
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
		
		
		if(((*i)->Type == ENTITY_TYPE_BOMB) && ((*i)->Dead == true)){ //delete the bomb pointers
			delete(*i);//delete it
			if(i != CEntity::EntityList.end()) CEntity::EntityList.erase(i--); //pop it out of list
			if(i == CEntity::EntityList.end()) CEntity::EntityList.pop_back();
		}
	}
	if (enemyCounter == 0) {//if all enemys are death go to the victory screen after a short delay
		waitingCounter++;
		if (waitingCounter > 500) OnVictory();
	}	
}

//==============================================================================
