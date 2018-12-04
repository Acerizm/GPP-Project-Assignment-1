#include "lastManStanding.h"
#include "player.h"
#include "textDX.h"
#include <string>
#include <Mmsystem.h>
#include <mciapi.h>
#include "zombie.h"
#include <sstream>
#include <iomanip>
#pragma comment(lib, "Winmm.lib")


using namespace std;
//=============================================================================
// Constructor
//=============================================================================
LastManStanding::LastManStanding()
{
	srand(time(NULL));
	hpText = new TextDX();
	isPaused = false;
	pausedText = new TextDX();
	isDead = false;
	deadText = new TextDX();
	currentGameTime = new TextDX();
	testZombie = NULL;
	nextShootTime = 0;
	for (int i = 0; i < 10; i++) {
		float randomType = static_cast<int>(rand()) / (static_cast<int> (RAND_MAX / 2)) + 1;
		obsTypeList.push_back(randomType);
	}
	nextHitTime = 0;

}

//=============================================================================
// Destructor
//=============================================================================
LastManStanding::~LastManStanding()
{
	if (camera) {
		delete camera;
		camera = nullptr;
	}
	releaseAll();           // call onLostDevice() for every graphics item
}
//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void LastManStanding::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	//create the camera
	camera = new Camera(GAME_WIDTH,GAME_HEIGHT,0, DirectX::XMFLOAT3(1.0f, 10.f, 10.f),&mainPlayer);

	// main player textures
	if (!PLAYER_SHOOTING_TILE_TEXTURE.initialize(graphics, PLAYER_SHOOTING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
	if(!mainPlayer.initialize(this, playerNS::PLAYER_SHOOTING_WIDTH, playerNS::PLAYER_SHOOTING_HEIGHT, playerNS::PLAYER_SHOOTING_TEXTURE_COLS, &PLAYER_SHOOTING_TILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	mainPlayer.setPositionVector(GAME_WIDTH / 4, GAME_WIDTH / 4);
	mainPlayer.setSpriteDataXnY(GAME_WIDTH / 4, GAME_WIDTH / 4);

	//initialize bullet texture here
	if (!BULLET_TEXTURE.initialize(graphics, BULLET_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	if (!ZOMBIE_MOVING_TEXTURE.initialize(graphics, ZOMBIE_MOVING_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));

	//implement the LEVEl1_TILE_TEXTURE texture here
	if (!LEVEL1_TILE_TEXTURE.initialize(graphics, LEVEL1_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	//implement the LEVEL1_TILE_IMAGE image here
	if (!LEVEL1_TILE_IMAGE.initialize(graphics, LEVEL1_TILE_WIDTH, LEVEL1_TILE_HEIGHT, 0, &LEVEL1_TILE_TEXTURE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing "));
	
	if (!healthBarGreenTexture.initialize(graphics, HEALTHBARGREEN_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarGreen texture"));

	if (!healthBarGreen.initialize(graphics, 256, 32, 1, &healthBarGreenTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarGreen"));

	if (!healthBarBackGroundTexture.initialize(graphics, HEALTHBARBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround texture"));

	if (!healthBarBackGround.initialize(graphics, 256, 32, 1, &healthBarBackGroundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround"));

	if (hpText->initialize(graphics, 15, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing hpText font"));

	if (pausedText->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pausedText font"));
	if (deadText->initialize(graphics, 30, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing pausedText font"));
	if(currentGameTime->initialize(graphics,20,true,false,"Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing currentGameTime font"));


	if (!healthBarRedTexture.initialize(graphics, HEALTHBARRED_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarRed texture"));

	if (!enemyHealthBarBackGroundTexture.initialize(graphics, HEALTHBARBACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthBarBackGround texture"));


	///////////////////////////////////////////////////////////////////////////////////////////////
	// Wx Here

	if(!BARREL_TEXTURE.initialize(graphics,BARREL_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Barrel texture"));
	if(!OBS1_TEXTURE.initialize(graphics,OBS1_TILE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing OBS1 texture"));

	for (int i = 0; i < obsTypeList.size(); i++) 
	{
		//the address of tempObstacle keeps changing in lastManStanding.h fyi
		tempObstacle = new Obstacle();
		//rng here
		float randomX = static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (GAME_WIDTH - 100)));
		float randomY = static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / (GAME_HEIGHT - 100)));
		//check if the type = "1" which represent barrel
		if (obsTypeList[i] == 1) {
			//need to random the position of the barrels
			if(!tempObstacle->initialize(this,&BARREL_TEXTURE, randomX, randomY,1))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Barrel"));

			//then push it back to the obstacleList
			obstacleList.push_back(tempObstacle);

			//then gg
		}
		else if (obsTypeList[i] == 2) 
		{
			//need to random the position of the barrels
			if (!tempObstacle->initialize(this, &OBS1_TEXTURE, randomX, randomY, 2))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Barrel"));
			//then push it back to the obstacleList
			obstacleList.push_back(tempObstacle);
			//then gg
		}
	}





	///////////////////////////////////////////////////////////////////////////////////////////////


	//damn annoying when debug so many times Xddd
	mciSendString("open \"audio\\deathSong.wav\" type waveaudio alias sound", NULL, 0, NULL);
	mciSendString("open \"audio\\backGroundMusic.wav\" type waveaudio alias backGroundMusic", NULL, 0, NULL);

	//set x or set y for the initial position vector of the object
	LEVEL1_TILE_IMAGE.setScale(LEVEL1_TILE_SCALE);


	mainPlayer.playerCurrentHp = PLAYER_MAXHP;

	healthBarGreen.setX(mainPlayer.getX() - 8);
	healthBarGreen.setY(mainPlayer.getY() - 5);
	healthBarBackGround.setX(mainPlayer.getX() - 8);
	healthBarBackGround.setY(mainPlayer.getY() - 5);
	healthBarGreen.setScale(0.5f);
	healthBarBackGround.setScale(0.5f);

	return;
}

std::string to_format(const int number) {
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << number;
	return ss.str();
}

//=============================================================================
// Update all game items
//=============================================================================
void LastManStanding::update(Timer *gameTimer)
{
	
	float test = gameTimer->getCurrentElapsedTime();
	
	mciSendString("play backGroundMusic", NULL, 0, NULL);
	if (isPaused)
	{
		if (input->wasKeyPressed(VK_F2))
		{
			isPaused = !isPaused;
		}
	}
	else if (isDead)
	{
		mciSendString("stop backGroundMusic", NULL, 0, NULL);
		mciSendString("play sound", NULL, 0, NULL);
		
		//PlaySound("audio\\deathSong.wav", NULL, SND_FILENAME);
		if (input->wasKeyPressed(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
		
	}
	else
	{
		auto test = &mainPlayer;
		if (camera) 
		{
			if (input->isKeyDown(VK_F1)) {
				if (!camera->isFollowing()) {
					camera->Follow(&mainPlayer);
				}
			}

			if (input->isKeyDown(VK_F2)) {
				if (camera->isFollowing()) {
					camera->UnFollow();
				}
			}

			camera->Update();
		}
		//update the animation here
		mainPlayer.update(frameTime);
		healthBarBackGround.update(frameTime);
		//healthBarRed.update(frameTime);
		////PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(playerNS::PLAYER_SHOOTING_ANIMATION_DELAY);
		if (zombieList.size() != 0) {
			for each (Zombie *zombie in zombieList) {
				zombie->update(frameTime);
			}
		}


		////////////////////////////////////////////////////////////////////////////
		if (input->isKeyDown(VK_LEFT))  //left arrow key is pressed down
		{
			//PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() - frameTime * PLAYER_MOVEMENTSPEED);
			//PLAYER_SHOOTING_TILE_IMAGE.setDegrees(180);
			mainPlayer.setX(mainPlayer.getX() - frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setSpriteDataXnY(mainPlayer.getX() - frameTime * playerNS::PLAYER_MOVEMENTSPEED, mainPlayer.getY());
			mainPlayer.setDegrees(180);

			if (input->isKeyDown(VK_SPACE))
			{
				//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
				mainPlayer.setFrameDelay(0.05f);
				if (nextShootTime < gameTimer->getCurrentElapsedTime())
				{
					mainPlayer.shootBullet(BULLET_TEXTURE, &mainPlayer, this, mainPlayer.getDegrees());
					nextShootTime = gameTimer->getCurrentElapsedTime() + 0.5;
				}
			}

		}
		else if (input->isKeyDown(VK_RIGHT)) //right arrow key is pressed down
		{
			//PLAYER_SHOOTING_TILE_IMAGE.setX(PLAYER_SHOOTING_TILE_IMAGE.getX() + frameTime * PLAYER_MOVEMENTSPEED);
			//PLAYER_SHOOTING_TILE_IMAGE.setDegrees(0);
			mainPlayer.setX(mainPlayer.getX() + frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setSpriteDataXnY(mainPlayer.getX() + frameTime * playerNS::PLAYER_MOVEMENTSPEED, mainPlayer.getY());
			mainPlayer.setDegrees(0);
			if (input->isKeyDown(VK_SPACE))
			{
				//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
				mainPlayer.setFrameDelay(0.05f);
				if (nextShootTime < gameTimer->getCurrentElapsedTime())
				{
					mainPlayer.shootBullet(BULLET_TEXTURE, &mainPlayer, this, mainPlayer.getDegrees());
					nextShootTime = gameTimer->getCurrentElapsedTime() + 0.5;
				}
			}
		}
		else if (input->isKeyDown(VK_UP)) // up arrow key is pressed down
		{
			//PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() - frameTime * PLAYER_MOVEMENTSPEED);
			//PLAYER_SHOOTING_TILE_IMAGE.setDegrees(270);
			mainPlayer.setY(mainPlayer.getY() - frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setSpriteDataXnY(mainPlayer.getX(), mainPlayer.getY() - frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setDegrees(270);
			if (input->isKeyDown(VK_SPACE))
			{
				//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
				mainPlayer.setFrameDelay(0.05f);
				if (nextShootTime < gameTimer->getCurrentElapsedTime())
				{
					mainPlayer.shootBullet(BULLET_TEXTURE, &mainPlayer, this, mainPlayer.getDegrees());
					nextShootTime = gameTimer->getCurrentElapsedTime() + 0.5;
				}
			}
		}
		else if (input->isKeyDown(VK_DOWN))// down arrow key is pressed down
		{
			//PLAYER_SHOOTING_TILE_IMAGE.setY(PLAYER_SHOOTING_TILE_IMAGE.getY() + frameTime * PLAYER_MOVEMENTSPEED);
			//PLAYER_SHOOTING_TILE_IMAGE.setDegrees(90);
			mainPlayer.setY(mainPlayer.getY() + frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setSpriteDataXnY(mainPlayer.getX(), mainPlayer.getY() + frameTime * playerNS::PLAYER_MOVEMENTSPEED);
			mainPlayer.setDegrees(90);
			if (input->isKeyDown(VK_SPACE))
			{
				//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
				mainPlayer.setFrameDelay(0.05f);
				if (nextShootTime < gameTimer->getCurrentElapsedTime())
				{
					mainPlayer.shootBullet(BULLET_TEXTURE, &mainPlayer, this, mainPlayer.getDegrees());
					nextShootTime = gameTimer->getCurrentElapsedTime() + 0.5;
				}
			}
		}
		else if (input->wasKeyPressed(VK_SPACE))
		{
			//Shooting animation
			//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(0.05f);
			
			//To minus HP of Player by 5.
			float currentHpBarPercentage = mainPlayer.playerCurrentHp / PLAYER_MAXHP;
			healthBarGreen.setPercentage(currentHpBarPercentage);
			mainPlayer.setFrameDelay(0.05f);
			if (nextShootTime < gameTimer->getCurrentElapsedTime())
			{
				mainPlayer.shootBullet(BULLET_TEXTURE, &mainPlayer, this, mainPlayer.getDegrees());
				nextShootTime = gameTimer->getCurrentElapsedTime() + 0.5 ;//set 0.5 seconds delay per shot
			}

		}
		else if (input->wasKeyPressed(VK_F2))
		{
			//To Recover 5 health.
			mainPlayer.playerCurrentHp = mainPlayer.playerCurrentHp + 5;
			float currentHpBarPercentage = mainPlayer.playerCurrentHp / PLAYER_MAXHP;
			healthBarGreen.setPercentage(currentHpBarPercentage);
			isPaused = !isPaused;
		}
		else
		{
			//PLAYER_SHOOTING_TILE_IMAGE.setFrameDelay(999);
			mainPlayer.setFrameDelay(999);
		}


		if (mainPlayer.playerCurrentHp<= 0)
		{
			isDead = true;
		}
		else
		{
			isDead = false;
		}
		healthBarGreen.setRect();
		healthBarGreen.setX(mainPlayer.getX() - 8);
		healthBarGreen.setY(mainPlayer.getY() - 5);
		healthBarBackGround.setX(mainPlayer.getX() - 8);
		healthBarBackGround.setY(mainPlayer.getY() - 5);

		//edit here to chnage the direction of the bullet
		mainPlayer.moveBullet(frameTime);
	}

	for each (Obstacle *obs in obstacleList) 
	{
		obs->update(frameTime);
	}


	///////////////////////////////////////////////////////////////////////////////
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void LastManStanding::ai(Timer *gameTimer)
{
	//add more zombies here
	//int test = (int)(gameTimer->getCurrentElapsedTime());

	//1. every 2 seconds , spawn a zombie

	if (isPaused)
	{

	}
	else if (isDead)
	{

	}
	else
	{

		int numOfSecondsPassed = int(gameTimer->getCurrentElapsedTime());
		// check if the time passed is a multiple of 5
		if (numOfSecondsPassed % 5 == 0 && numOfSecondsPassed != 0 && numOfSecondsPassed != nextIntervalValue) {

			nextIntervalValue = numOfSecondsPassed;
			testZombie = new Zombie();
			//testZombie->initialize(graphics, ZOMBIE_MOVING_TEXTURE, testZombie->ZOMBIE_MOVING_IMAGE);
			testZombie->initialize(this, zombieNS::ZOMBIE_MOVING_WIDTH, zombieNS::ZOMBIE_MOVING_HEIGHT, zombieNS::ZOMBIE_MOVING_COLS, &ZOMBIE_MOVING_TEXTURE,&healthBarRedTexture,&enemyHealthBarBackGroundTexture, graphics);

			//have to do rng here
			int condition = 0;
			float x;
			float y;

			//redo this algo again when have time
			while (!condition) {
				float x2 = static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / GAME_WIDTH));
				float y2 = static_cast<float>(rand()) / (static_cast<float> (RAND_MAX / GAME_HEIGHT));

				//if ((x2 <= (PLAYER_SHOOTING_TILE_IMAGE.getCenterX() - (PLAYER_SHOOTING_TILE_IMAGE.getWidth() / 2) * 10)) || (x2 >= (PLAYER_SHOOTING_TILE_IMAGE.getCenterX() + (PLAYER_SHOOTING_TILE_IMAGE.getWidth() / 2) * 10)))
				if ((x2 <= (mainPlayer.getCenterX() - (mainPlayer.getWidth() / 2) * 10)) || (x2 >= (mainPlayer.getCenterX() + (mainPlayer.getWidth() / 2) * 10)))
				{
					//continue the loop xd
					int x = 2;
				}
				else
				{
					x = x2;
					y = y2;
					condition = 1;
				}
			};
			//testZombie->setPositionVector(testZombie->ZOMBIE_MOVING_IMAGE, PLAYER_SHOOTING_TILE_IMAGE.getCenterX(), PLAYER_SHOOTING_TILE_IMAGE.getCenterY(), zombieNS::ZOMBIE_MOVING_SCALE, zombieNS::ZOMBIE_MOVING_START_FRAME, zombieNS::ZOMBIE_MOVING_END_FRAME, zombieNS::ZOMBIE_MOVING_ANIMATION_DELAY);
			testZombie->setPositionVector(x, y);
			float testing1 = testZombie->getCenterX();
			float testing2 = testZombie->getCenterY();

			//add the zombie to the array
			zombieList.push_back(testZombie);
		}

		//then attack the player
		for each (Zombie * zombie in zombieList) {
			zombie->attackPlayer(&mainPlayer, frameTime);

		}

	}
}

//=============================================================================
// Handle collisions
//=============================================================================
void LastManStanding::collisions() {
	VECTOR2 collisionVector;
	VECTOR2 collisionVector2;
	//this is where the magic happens
	if (zombieList.size() != 0) {
		for (list<Zombie*>::iterator it = zombieList.begin(); it != zombieList.end(); ) {
			float testzombiecenterx = (*it)->getCenterX();
			float testzombiecentery = (*it)->getCenterY();
			if ((*it)->collidesWith(mainPlayer,collisionVector))
			{
			//the magic is here
				if (nextHitTime < currentGameTimeCpp->getCurrentElapsedTime())
				{
					mainPlayer.playerCurrentHp -= 10;
					nextHitTime = currentGameTimeCpp->getCurrentElapsedTime() + 2; //delay 2 seconds per hit by zombie
				}
				float currentHpBarPercentage = mainPlayer.playerCurrentHp / PLAYER_MAXHP;
				healthBarGreen.setPercentage(currentHpBarPercentage);
				if (false)
				{
					SAFE_DELETE(*it);
					it = zombieList.erase(it);
				}
				else
				{
					it++;
				}
			}
			else {
				it++;
			}
		}
	}
	
	 
/*	for (list<Bullet*>::iterator it = mainPlayer.BULLET_LIST.begin(); it != mainPlayer.BULLET_LIST.end(); ) 
	{
		/*float testZombieCenterX = (*it)->getCenterX();
		float testZombieCenterY = (*it)->getCenterY();
		for (list<Zombie*>::iterator z = zombieList.begin(); z != zombieList.end();) 
		{
			Bullet *tempBullet = *it;
			if ((*z)->collidesWith(*tempBullet, collisionVector))
			{
				//the magic is here
				/*SAFE_DELETE(*it);
				it = mainPlayer.BULLET_LIST.erase(it);
				
				if ((*z)->zombieCurrentHP <=0)
				{
					(*it)->setIsCollided(true);
					SAFE_DELETE(*z);
					z = zombieList.erase(z);
				}
				
				//just to check here
				//int check = zombieList.size();
			}
			else {
				z++;
				//it++;
			}
		}
		
		/*if (mainPlayer.BULLET_LIST.size() != 0 && zombieList.size()
			it++;
		else;

		if ((*it)->getIsCollided()) {
			bool test = (*it)->getIsCollided();
			SAFE_DELETE(*it);
			it = mainPlayer.BULLET_LIST.erase(it);
			//it++;
		}
		else {
			it++;
		}




	}*/
	for (list<Zombie*>::iterator z = zombieList.begin(); z != zombieList.end();)
	{
		for (list<Bullet*>::iterator it = mainPlayer.BULLET_LIST.begin(); it != mainPlayer.BULLET_LIST.end(); )
		{
			Bullet *tempBullet = *it;
			if ((*z)->collidesWith(*tempBullet, collisionVector))
			{
				(*z)->zombieCurrentHP -= 35;
				float currentHpBarPercentage = ((*z)->zombieCurrentHP) / ((*z)->zombieMaxHp);
				(*z)->setPercentage(currentHpBarPercentage);
				(*z)->setIsCollided(true);
				SAFE_DELETE(*it);
				it = mainPlayer.BULLET_LIST.erase(it);
			}
			else
			{
				it++;
			}
		}
		if ((*z)->getIsCollided())
		{
			if ((*z)->zombieCurrentHP <= 0)
			{
				
				SAFE_DELETE(*z);
				z = zombieList.erase(z);
			}
			else
			{
				z++;
			}
		}
		else
		{
			z++;
		}
	}


}

//=============================================================================
// Render game items
//=============================================================================
void LastManStanding::render()
{
	// need to de-structure the method here as the player has multiple animations
	// aka need to render again?

	graphics->spriteBegin();                // begin drawing sprites

	if (camera) 
	{
		camera->setTransform(graphics);
	}
	LEVEL1_TILE_IMAGE.draw();
	//PLAYER_SHOOTING_TILE_IMAGE.draw();
	//PLAYER_RELOADING_IMAGE.draw();
	mainPlayer.draw();
	mainPlayer.drawBullets();
	//testBullet.draw();
	healthBarBackGround.draw();
	healthBarGreen.draw();
	//mainPlayer.drawBullets();
	currentGameTime->setFontColor(graphicsNS::YELLOW);
	int totalSeconds = this->currentGameTimeCpp->getCurrentElapsedTime();
	int hours = totalSeconds / 3600;
	int minutes = (totalSeconds / 60) % 60;
	int seconds = totalSeconds % 60;
	string currentTimeString = to_format(hours) + ":" + to_format(minutes) + ":" + to_format(seconds);
	currentGameTime->print(currentTimeString, 0, 0);
	hpText->setFontColor(graphicsNS::WHITE);
	hpText->print(to_string((int)(mainPlayer.playerCurrentHp)) + "/" + to_string((int)(PLAYER_MAXHP)), mainPlayer.getX(), mainPlayer.getY() - 5);

	///////////////////////////////////////////////////////////////////////////////////////////
	//Wx Here

	//tempObstacle->draw();
	//draw each object here
	for (list<Obstacle*>::iterator it = obstacleList.begin(); it != obstacleList.end();) {
		(*it)->draw();
		it++;
	}

	///////////////////////////////////////////////////////////////////////////////////////////
	if (isPaused)
	{
		pausedText->setFontColor(graphicsNS::RED);
		pausedText->print("Game is Paused Press F2 to Resume", 0,0);
	}
	if (isDead)
	{
		deadText->setFontColor(graphicsNS::RED);
		deadText->print("YOU DIED! Press Esc to close game", 0, 0);
	}
	drawZombieAIs();
	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void LastManStanding::releaseAll()
{
	LEVEL1_TILE_TEXTURE.onLostDevice();

	Game::releaseAll();
	return;

}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void LastManStanding::resetAll()
{
	LEVEL1_TILE_TEXTURE.onResetDevice();

	Game::resetAll();
	return;

}

void LastManStanding::drawZombieAIs() {
	if (zombieList.size() != 0) {
		//for (list<Zombie*>::iterator it = zombieList.begin(); it != zombieList.end(); ) {
		//	// for testing purposes
		//	// destroy the zombie when the zombie is around the player
		//	if ()
		//	{
		//		SAFE_DELETE(*it);
		//		it = BULLET_LIST.erase(it);
		//		//just to check here
		//		int check = BULLET_LIST.size();
		//		//bool test = false;
		//	}
		//	else {
		//		it++;
		//	}
		//}

		//when all okay go and draw the bullet
		for each(Zombie* zombie in zombieList)
		{
			zombie->draw();
			zombie->enemyHealthBarBackGround->draw();
			zombie->healthBarRed->draw();
			//zombie.zombieHpText.print(to_string((int)zombie->zombieCu
			zombie->getZombieHPText()->print(to_string((int) zombie->getCurrentZombieHP())+ "/" + to_string((int)zombie->getZombieMaxHp()),zombie->getX(),zombie->getY()-5);
		}
	}
}
bool LastManStanding::checkIsDead()
{
	return isDead;
}

