#pragma warning( disable : 4996 ) 


#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include "G2D.h"


using namespace std;

// touche P   : mets en pause
// touche ESC : ferme la fenêtre et quitte le jeu


///////////////////////////////////////////////////////////////////////////////
//
//    Données du jeu - structure instanciée dans le main

struct _Spaceship
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int bulletCount;
	float fireCooldown;
	float fireRate;
	int speed = 3;

	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//spaceship.ppm", true);
		int zoom = 6;
		Size = Size * zoom;
	}
};

struct _Target
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int IdSpriteTouched;
	bool isTouched = false;
	bool move = true;  
	int level;

	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//target_normal.ppm", true);
		IdSpriteTouched = G2D::extractTextureFromPPM(".//assets//touched_target_normal.ppm", true);
		int zoom = 4;
		Size = Size * zoom;
	}
};

struct _smallTarget
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int IdSpriteTouched;
	bool isTouched = false;
	bool move = true;
	int level;


	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//target_small.ppm", true);
		IdSpriteTouched = G2D::extractTextureFromPPM(".//assets//touched_target_small.ppm", true);
		int zoom = 4;
		Size = Size * zoom;
	}
};

struct _bigTarget
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int IdSpriteTouched;
	bool isTouched = false;
	bool move = true;
	int level;


	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//target_big.ppm", true);
		IdSpriteTouched = G2D::extractTextureFromPPM(".//assets//touched_target_big.ppm", true);
		int zoom = 4;
		Size = Size * zoom;
	}
};

struct _doubleTarget
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int IdSpriteTouched;
	int IdSpriteTouched2;
	int hitCount;
	bool isTouched = false;
	bool move = true;
	int level;


	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//target_double.ppm", true);
		IdSpriteTouched = G2D::extractTextureFromPPM(".//assets//target_normal.ppm", true);
		IdSpriteTouched2 = G2D::extractTextureFromPPM(".//assets//touched_target_normal.ppm", true);
		int zoom = 4;
		Size = Size * zoom;
		hitCount = 0;
	}
};

struct _Bullets
{
	V2 Size;
	V2 Pos;
	int IdSprite;

	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//bullet.ppm", true);
		int zoom = 2.5;
		Size = Size * zoom;
	}
	void MoveUp()
	{
		int speed = 20;
		Pos.y += speed;
	}
};

struct _Obstacle
{
	V2 Size;
	V2 Pos;
	int IdSprite;
	int level;

	void InitTextures()
	{
		IdSprite = G2D::extractTextureFromPPM(".//assets//obstacle.ppm", true);
		int zoom = 6;
		Size = Size * zoom;
	}
};

struct GameData
{
	int HeighPix = 800;   // hauteur de la fenêtre d'application
	int WidthPix = 600;   // largeur de la fenêtre d'application

	_Spaceship Spaceship;
	std::vector<_Bullets> Bullets;
	std::vector<_Bullets> BulletSprites;
	_Obstacle Obstacles[5];
	_Target Targets[9];
	_smallTarget smallTargets[3];
	_bigTarget bigTargets[2];
	_doubleTarget doubleTargets[2];

	int currentLevel = 1;


	GameData() {}

};

// Ecrans
enum class Screen { Home, Tutorial, Level1, Level2, Level3, Level4, Level5, Win, GameOver };
Screen currentScreen = Screen::Home;


int IdTextureWin;
int IdTextureHome;
int IdTextureGameOver;

// Initialisation Level 1
void InitAssetsDataLevel1(GameData& G) {

	G.Targets[0].Pos = V2(50, 400);
	G.Targets[0].Size = V2(12, 12);
	G.Targets[0].level = 1;
	G.Targets[0].InitTextures();

	G.Targets[1].Pos = V2(100, 500);
	G.Targets[1].Size = V2(12, 12);
	G.Targets[1].level = 1;
	G.Targets[1].InitTextures();

	G.Targets[2].Pos = V2(150, 600);
	G.Targets[2].Size = V2(12, 12);
	G.Targets[2].level = 1;
	G.Targets[2].InitTextures();

	G.Targets[3].Pos = V2(200, 700);
	G.Targets[3].Size = V2(12, 12);
	G.Targets[3].level = 1;
	G.Targets[3].InitTextures();

}

// Initialisation Level 2
void InitAssetsDataLevel2(GameData& G) {

	G.smallTargets[0].Pos = V2(300, 300);
	G.smallTargets[0].Size = V2(8, 8);
	G.smallTargets[0].level = 2;
	G.smallTargets[0].InitTextures();

	G.bigTargets[0].Pos = V2(400, 700);
	G.bigTargets[0].Size = V2(21, 12);
	G.bigTargets[0].level = 2;
	G.bigTargets[0].InitTextures();

	G.Targets[4].Pos = V2(200, 400);
	G.Targets[4].Size = V2(12, 12);
	G.Targets[4].level = 2;
	G.Targets[4].InitTextures();
}

// Initialisation Level 3
void InitAssetsDataLevel3(GameData& G) {

	G.doubleTargets[0].Pos = V2(400, 500);
	G.doubleTargets[0].Size = V2(12, 12);
	G.doubleTargets[0].level = 3;
	G.doubleTargets[0].InitTextures();

	G.Targets[5].Pos = V2(200, 400);
	G.Targets[5].Size = V2(12, 12);
	G.Targets[5].level = 3;
	G.Targets[5].InitTextures();

	G.Targets[6].Pos = V2(200, 600);
	G.Targets[6].Size = V2(12, 12);
	G.Targets[6].level = 3;
	G.Targets[6].InitTextures();

	G.Obstacles[0].Pos = V2(250, 200);
	G.Obstacles[0].Size = V2(17, 17);
	G.Obstacles[0].level = 3;
	G.Obstacles[0].InitTextures();
}

// Initialisation Level 4
void InitAssetsDataLevel4(GameData& G) {

	G.Targets[7].Pos = V2(400, 150);
	G.Targets[7].Size = V2(12, 12);
	G.Targets[7].level = 4;
	G.Targets[7].InitTextures();

	G.Obstacles[1].Pos = V2(330, 250);
	G.Obstacles[1].Size = V2(17, 17);
	G.Obstacles[1].level = 4;
	G.Obstacles[1].InitTextures();

	G.Obstacles[2].Pos = V2(270, 600);
	G.Obstacles[2].Size = V2(17, 17);
	G.Obstacles[2].level = 4;
	G.Obstacles[2].InitTextures();

	G.smallTargets[1].Pos = V2(500, 636);
	G.smallTargets[1].Size = V2(8, 8);
	G.smallTargets[1].level = 4;
	G.smallTargets[1].InitTextures();

	G.doubleTargets[1].Pos = V2(200, 275);
	G.doubleTargets[1].Size = V2(12, 12);
	G.doubleTargets[1].level = 4;
	G.doubleTargets[1].InitTextures();

}

// Initialisation Level 5
void InitAssetsDataLevel5(GameData& G) {

	G.Obstacles[3].Pos = V2(300, 600);
	G.Obstacles[3].Size = V2(17, 17);
	G.Obstacles[3].level = 5;
	G.Obstacles[3].InitTextures();

	G.Obstacles[4].Pos = V2(175, 250);
	G.Obstacles[4].Size = V2(17, 17);
	G.Obstacles[4].level = 5;
	G.Obstacles[4].InitTextures();


	G.smallTargets[2].Pos = V2(100, 286);
	G.smallTargets[2].Size = V2(8, 8);
	G.smallTargets[2].level = 5;
	G.smallTargets[2].InitTextures();

	G.bigTargets[1].Pos = V2(500, 278);
	G.bigTargets[1].Size = V2(21, 12);
	G.bigTargets[1].level = 5;
	G.bigTargets[1].InitTextures();

	G.Targets[8].Pos = V2(400, 625);
	G.Targets[8].Size = V2(12, 12);
	G.Targets[8].level = 5;
	G.Targets[8].InitTextures();

}

// Initialisation
void InitAssetsData(GameData& G) {

	G.Spaceship.Pos = V2(250, 45);
	G.Spaceship.bulletCount = 25;
	G.Spaceship.Size = V2(14, 6);
	G.Spaceship.fireRate = 1.5f;

	float fireCooldown = 0.0f;

	for (int i = 0; i < G.Spaceship.bulletCount; i++) {
		_Bullets bulletSprite;
		bulletSprite.Pos = V2(10 + i * 20, G.HeighPix - 20);  
		bulletSprite.Size = V2(3, 6);  
		bulletSprite.InitTextures();
		G.BulletSprites.push_back(bulletSprite);
	}

}

///////////////////////////////////////////////////////////////////////////////
//
// 
//     fonction de rendu - reçoit en paramètre les données du jeu par référence

void DessineScoreBar(const GameData& G) {
	std::string scoreText = "Level : " + std::to_string(G.currentLevel) + "/5";
	G2D::drawStringFontRoman(V2(450, 15), scoreText, 24, 3, Color::White);
}

void Render(const GameData& G)
{
	G2D::clearScreen(ColorFrom255(36, 92, 6));

	switch (currentScreen) {

	case Screen::Home:
		IdTextureHome = G2D::extractTextureFromPPM(".//assets//home.ppm", true);
		G2D::drawRectWithTexture(IdTextureHome, V2(50, 100), V2(500, 600));
		break;
	case Screen::Level1:

		DessineScoreBar(G);

		G2D::drawRectangle(V2(0, 420), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 520), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 620), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 720), V2(600, 8), Color::Blue, true);

		G2D::drawRectWithTexture(G.Spaceship.IdSprite, G.Spaceship.Pos, G.Spaceship.Size);

		for (int i = 0; i < 9; i++) {
			if (G.Targets[i].level == 1) {
				G2D::drawRectWithTexture(G.Targets[i].IdSprite, G.Targets[i].Pos, G.Targets[i].Size);
			}

		}
		for (const _Bullets& bulletSprite : G.BulletSprites)
		{
			G2D::drawRectWithTexture(bulletSprite.IdSprite, bulletSprite.Pos, bulletSprite.Size);
		}

		for (const _Bullets& bullet : G.Bullets)
		{
			G2D::drawRectWithTexture(bullet.IdSprite, bullet.Pos, bullet.Size);
		}
		break;

	case Screen::Level2:

		DessineScoreBar(G);

		G2D::drawRectangle(V2(0, 312), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 420), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 720), V2(600, 8), Color::Blue, true);

		G2D::drawRectWithTexture(G.Spaceship.IdSprite, G.Spaceship.Pos, G.Spaceship.Size);

		for (int i = 0; i < 9; i++) {
			if (G.Targets[i].level == 2) {
				G2D::drawRectWithTexture(G.Targets[i].IdSprite, G.Targets[i].Pos, G.Targets[i].Size);
			}

		}
		for (int i = 0; i < 3; i++) {
			if (G.smallTargets[i].level == 2) {
				G2D::drawRectWithTexture(G.smallTargets[i].IdSprite, G.smallTargets[i].Pos, G.smallTargets[i].Size);
			}

		}
		for (int i = 0; i < 2; i++) {
			if (G.bigTargets[i].level == 2) {
				G2D::drawRectWithTexture(G.bigTargets[i].IdSprite, G.bigTargets[i].Pos, G.bigTargets[i].Size);
			}

		}
		for (const _Bullets& bulletSprite : G.BulletSprites)
		{
			G2D::drawRectWithTexture(bulletSprite.IdSprite, bulletSprite.Pos, bulletSprite.Size);
		}

		for (const _Bullets& bullet : G.Bullets)
		{
			G2D::drawRectWithTexture(bullet.IdSprite, bullet.Pos, bullet.Size);
		}
		break;

	case Screen::Level3:

		DessineScoreBar(G);

		G2D::drawRectangle(V2(0, 420), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 520), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 620), V2(600, 8), Color::Blue, true);

		G2D::drawRectWithTexture(G.Spaceship.IdSprite, G.Spaceship.Pos, G.Spaceship.Size);

		for (int i = 0; i < 9; i++) {
			if (G.Targets[i].level == 3) {
				G2D::drawRectWithTexture(G.Targets[i].IdSprite, G.Targets[i].Pos, G.Targets[i].Size);
			}

		}
		for (int i = 0; i < 2; i++) {
			if (G.doubleTargets[i].level == 3) {
				G2D::drawRectWithTexture(G.doubleTargets[i].IdSprite, G.doubleTargets[i].Pos, G.doubleTargets[i].Size);
			}

		}
		for (int i = 0; i < 5; i++) {
			if (G.Obstacles[i].level == 3) {
				G2D::drawRectWithTexture(G.Obstacles[i].IdSprite, G.Obstacles[i].Pos, G.Obstacles[i].Size);
			}

		}
		for (const _Bullets& bulletSprite : G.BulletSprites)
		{
			G2D::drawRectWithTexture(bulletSprite.IdSprite, bulletSprite.Pos, bulletSprite.Size);
		}

		for (const _Bullets& bullet : G.Bullets)
		{
			G2D::drawRectWithTexture(bullet.IdSprite, bullet.Pos, bullet.Size);
		}
		break;

	case Screen::Level4:

		DessineScoreBar(G);

		G2D::drawRectangle(V2(0, 170), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(0, 295), V2(350, 8), Color::Blue, true);

		G2D::drawRectangle(V2(290, 648), V2(600, 8), Color::Blue, true);

		G2D::drawRectWithTexture(G.Spaceship.IdSprite, G.Spaceship.Pos, G.Spaceship.Size);

		for (int i = 0; i < 9; i++) {
			if (G.Targets[i].level == 4) {
				G2D::drawRectWithTexture(G.Targets[i].IdSprite, G.Targets[i].Pos, G.Targets[i].Size);
			}

		}
		for (int i = 0; i < 5; i++) {
			if (G.Obstacles[i].level == 4) {
				G2D::drawRectWithTexture(G.Obstacles[i].IdSprite, G.Obstacles[i].Pos, G.Obstacles[i].Size);
			}

		}
		for (int i = 0; i < 2; i++) {
			if (G.doubleTargets[i].level == 4) {
				G2D::drawRectWithTexture(G.doubleTargets[i].IdSprite, G.doubleTargets[i].Pos, G.doubleTargets[i].Size);
			}

		}
		for (int i = 0; i < 3; i++) {
			if (G.smallTargets[i].level == 4) {
				G2D::drawRectWithTexture(G.smallTargets[i].IdSprite, G.smallTargets[i].Pos, G.smallTargets[i].Size);
			}

		}
		for (const _Bullets& bulletSprite : G.BulletSprites)
		{
			G2D::drawRectWithTexture(bulletSprite.IdSprite, bulletSprite.Pos, bulletSprite.Size);
		}

		for (const _Bullets& bullet : G.Bullets)
		{
			G2D::drawRectWithTexture(bullet.IdSprite, bullet.Pos, bullet.Size);
		}
		break;

	case Screen::Level5:

		DessineScoreBar(G);

		G2D::drawRectangle(V2(0, 298), V2(600, 8), Color::Blue, true);

		G2D::drawRectangle(V2(400, 645), V2(600, 8), Color::Blue, true);


		G2D::drawRectWithTexture(G.Spaceship.IdSprite, G.Spaceship.Pos, G.Spaceship.Size);

		for (int i = 0; i < 9; i++) {
			if (G.Targets[i].level == 5) {
				G2D::drawRectWithTexture(G.Targets[i].IdSprite, G.Targets[i].Pos, G.Targets[i].Size);
			}

		}
		for (int i = 0; i < 3; i++) {
			if (G.smallTargets[i].level == 5) {
				G2D::drawRectWithTexture(G.smallTargets[i].IdSprite, G.smallTargets[i].Pos, G.smallTargets[i].Size);
			}

		}
		for (int i = 0; i < 2; i++) {
			if (G.bigTargets[i].level == 5) {
				G2D::drawRectWithTexture(G.bigTargets[i].IdSprite, G.bigTargets[i].Pos, G.bigTargets[i].Size);
			}

		}
		for (int i = 0; i < 5; i++) {
			if (G.Obstacles[i].level == 5) {
				G2D::drawRectWithTexture(G.Obstacles[i].IdSprite, G.Obstacles[i].Pos, G.Obstacles[i].Size);
			}

		}
		for (const _Bullets& bulletSprite : G.BulletSprites)
		{
			G2D::drawRectWithTexture(bulletSprite.IdSprite, bulletSprite.Pos, bulletSprite.Size);
		}

		for (const _Bullets& bullet : G.Bullets)
		{
			G2D::drawRectWithTexture(bullet.IdSprite, bullet.Pos, bullet.Size);
		}
		break;

	case Screen::Win:
		IdTextureWin = G2D::extractTextureFromPPM(".//assets//win.ppm", true);
		G2D::drawRectWithTexture(IdTextureWin, V2(150, 400), V2(338, 45));
		break;

	case Screen::GameOver:
		IdTextureGameOver = G2D::extractTextureFromPPM(".//assets//gameover.ppm", true);
		G2D::drawRectWithTexture(IdTextureGameOver, V2(150, 400), V2(300, 30));
		break;

	}

	G2D::Show();
}


// Deplacement gauche/droite Vaisseau
void GestionDeplacementSpaceship(GameData& G) {
	int newX = G.Spaceship.Pos.x;
	int newY = G.Spaceship.Pos.y;

	if (G2D::isKeyPressed(Key::LEFT)) {
		newX = newX - G.Spaceship.speed;
	}
	if (G2D::isKeyPressed(Key::RIGHT)) {
		newX = newX + G.Spaceship.speed;
	}

	if (newX >= 0 && newX <= G.WidthPix - 84) {
		G.Spaceship.Pos.x = newX;
		G.Spaceship.Pos.y = newY;
	}
}




///////////////////////////////////////////////////////////////////////////////
//
//
//      Gestion de la logique du jeu - reçoit en paramètre les données du jeu par référence

// Tirer une balle
void FireBullet(GameData& G)
{
	if (G.Spaceship.fireCooldown <= 0.0f && G.Spaceship.bulletCount > 0 && !G.BulletSprites.empty())  // Si le vaisseau peut tirer
	{
		_Bullets bullet;
		G.BulletSprites.pop_back();
		bullet.Pos = V2(G.Spaceship.Pos.x + 35, G.Spaceship.Pos.y + 30);
		bullet.Size = V2(3, 6);  
		bullet.Size = bullet.Size * 1.5;
		bullet.InitTextures();
		G.Bullets.push_back(bullet);
		G.Spaceship.bulletCount--;
		G.Spaceship.fireCooldown = G.Spaceship.fireRate;  // Reset du cooldown
	}
}

// Detecte les collisions
bool DetectCollision(const V2& pos1, const V2& size1, const V2& pos2, const V2& size2, float threshold) {
	// Calcul du centre de l'objet
	V2 center1 = V2(pos1.x + size1.x / 2, pos1.y + size1.y / 2);
	V2 center2 = V2(pos2.x + size2.x / 2, pos2.y + size2.y / 2);

	float distance = sqrt(pow(center1.x - center2.x, 2) + pow(center1.y - center2.y, 2));
	// Retourne true si la distance est inferieur au treshold , cela indique une collision
	if (distance < threshold) {
		return true;
	}
	return false;
}
// Bouge la cible 
void MoveTargetNormal(_Target& target, int leftBound, int rightBound, int speed) {
	if (!target.isTouched) {  
		if (target.move) {
			target.Pos.x += speed;
			if (target.Pos.x >= rightBound) {
				target.move = false;
			}
		}
		else {
			target.Pos.x -= speed;
			if (target.Pos.x <= leftBound) {
				target.move = true;
			}
		}
	}
}
void MoveTargetSmall(_smallTarget& target, int leftBound, int rightBound, int speed) {
	if (!target.isTouched) {  
		if (target.move) {
			target.Pos.x += speed;
			if (target.Pos.x >= rightBound) {
				target.move = false;
			}
		}
		else {
			target.Pos.x -= speed;
			if (target.Pos.x <= leftBound) {
				target.move = true;
			}
		}
	}
}
void MoveTargetBig(_bigTarget& target, int leftBound, int rightBound, int speed) {
	if (!target.isTouched) {  
		if (target.move) {
			target.Pos.x += speed;
			if (target.Pos.x >= rightBound) {
				target.move = false;
			}
		}
		else {
			target.Pos.x -= speed;
			if (target.Pos.x <= leftBound) {
				target.move = true;
			}
		}
	}
}
void MoveTargetDouble(_doubleTarget& target, int leftBound, int rightBound, int speed) {
	if (!target.isTouched) {  
		if (target.move) {
			target.Pos.x += speed;
			if (target.Pos.x >= rightBound) {
				target.move = false;
			}
		}
		else {
			target.Pos.x -= speed;
			if (target.Pos.x <= leftBound) {
				target.move = true;
			}
		}
	}
}

void Logic(GameData& G) 
{
	GestionDeplacementSpaceship(G);

	
	G.Spaceship.fireCooldown -= 1.0f / 20.0f;  

	if (currentScreen == Screen::Level1 || currentScreen == Screen::Level2 || currentScreen == Screen::Level3) {
		for (int i = 0; i < 9; i++) {
			MoveTargetNormal(G.Targets[i], 0, G.WidthPix - 50, 2);
		}
		MoveTargetBig(G.bigTargets[0], 0, G.WidthPix - 85, 2);
		MoveTargetSmall(G.smallTargets[0], 0, G.WidthPix - 30, 2);
		MoveTargetDouble(G.doubleTargets[0], 0, G.WidthPix - 50, 2);
	}
	if (currentScreen == Screen::Level4) {
		for (int i = 0; i < 9; i++) {
			MoveTargetNormal(G.Targets[i], 0, G.WidthPix - 50, 2);
		}
		MoveTargetSmall(G.smallTargets[1], 375, G.WidthPix - 30, 2);
		MoveTargetDouble(G.doubleTargets[1], 0, 280, 2);
	}
	if (currentScreen == Screen::Level5) {
		for (int i = 0; i < 9; i++) {
			MoveTargetNormal(G.Targets[i], 400, G.WidthPix - 50, 2);
		}
		MoveTargetSmall(G.smallTargets[2], 0, 140, 4);
		MoveTargetBig(G.bigTargets[1], 280, G.WidthPix - 85, 1);
	}

	if (G.Spaceship.fireCooldown < 0.0f)
	{
		G.Spaceship.fireCooldown = 0.0f;  // Le cooldown ne doit pas etre inferieur a 0
	}

	if (G2D::isKeyPressed(Key::ENTER))
	{
		FireBullet(G);
	}

	// Fait monter les balles
	for (int i = 0; i < G.Bullets.size(); i++)
	{
		G.Bullets[i].MoveUp();
	}

	for (int i = 0; i < G.Bullets.size(); i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (DetectCollision(G.Bullets[i].Pos, G.Bullets[i].Size, G.Obstacles[j].Pos, G.Obstacles[j].Size, 60))  // Verifie les collisions des balles avec tous les obstacles
			{
				// Supprime la balle du vecteur
				G.Bullets.erase(G.Bullets.begin() + i);
				i--; 
				break;  
			}
		}
	}

	// Verifie les collisions balles-cibles 
	for (int i = 0; i < G.Bullets.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (DetectCollision(G.Bullets[i].Pos, G.Bullets[i].Size, G.Targets[j].Pos, G.Targets[j].Size, 30))
			{
				// Change la texture de la cible à la texture lorsque elle est touchee.
				G.Targets[j].IdSprite = G.Targets[j].IdSpriteTouched;
				G.Targets[j].isTouched = true;  // Modifie la valeur du boolean lorsque une cible est touchee.

				G.Bullets.erase(G.Bullets.begin() + i);
				i--;  
				break; 
			}
		}
	}

	// Verifie les collisions balles-grandes_cibles 
	for (int i = 0; i < G.Bullets.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (DetectCollision(G.Bullets[i].Pos, G.Bullets[i].Size, G.bigTargets[j].Pos, G.bigTargets[j].Size, 40))
			{
				G.bigTargets[j].IdSprite = G.bigTargets[j].IdSpriteTouched;
				G.bigTargets[j].isTouched = true;

				G.Bullets.erase(G.Bullets.begin() + i);
				i--;  
				break;  
			}
		}
	}

	// Verifie les collisions balles-petites_cibles 
	for (int i = 0; i < G.Bullets.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (DetectCollision(G.Bullets[i].Pos, G.Bullets[i].Size, G.smallTargets[j].Pos, G.smallTargets[j].Size, 20))
			{
				G.smallTargets[j].IdSprite = G.smallTargets[j].IdSpriteTouched;
				G.smallTargets[j].isTouched = true;

				G.Bullets.erase(G.Bullets.begin() + i);
				i--;  
				break; 
			}
		}
	}

	// Verifie les collisions balles-doubles_cibles 
	for (int i = 0; i < G.Bullets.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (DetectCollision(G.Bullets[i].Pos, G.Bullets[i].Size, G.doubleTargets[j].Pos, G.doubleTargets[j].Size, 30))
			{
				// On incremente le nombre de fois ou l'on a touche la cible
				G.doubleTargets[j].hitCount++;

				G.Bullets.erase(G.Bullets.begin() + i);
				i--;  
				break;  
			}
		}
	}

	// On change la texture de la double cible
	for (int i = 0; i < 3; i++) {

		//Si la double cible a ete touche 1 fois
		if (G.doubleTargets[i].hitCount == 1)
		{
			
			G.doubleTargets[i].IdSprite = G.doubleTargets[i].IdSpriteTouched;
		}
		//Si la double cible a ete touche 2 fois ou plus
		if (G.doubleTargets[i].hitCount >= 2)
		{
			G.doubleTargets[i].IdSprite = G.doubleTargets[i].IdSpriteTouched2;
			G.doubleTargets[i].isTouched = true;
		}
	}
	//Transition home -> level1
	if (currentScreen == Screen::Home && G2D::isKeyPressed(Key::S)) {
		currentScreen = Screen::Level1;
	}
	//Transition level1 -> level2
	if (currentScreen == Screen::Level1 && G.Targets[0].isTouched && G.Targets[1].isTouched && G.Targets[2].isTouched && G.Targets[3].isTouched) {
		currentScreen = Screen::Level2;
		G.currentLevel++;
		InitAssetsDataLevel2(G);
		G.Targets[0].Pos = V2(0, 0);
		G.Targets[1].Pos = V2(0, 0);
		G.Targets[2].Pos = V2(0, 0);
		G.Targets[3].Pos = V2(0, 0);
	}

	//Transition level2 -> level3
	if (currentScreen == Screen::Level2 && G.Targets[4].isTouched && G.smallTargets[0].isTouched && G.bigTargets[0].isTouched) {
		currentScreen = Screen::Level3;
		G.currentLevel++;
		InitAssetsDataLevel3(G);
		G.Targets[4].Pos = V2(0, 0);
		G.smallTargets[0].Pos = V2(0, 0);
		G.bigTargets[0].Pos = V2(0, 0);
	}
	//Transition level3 -> level4
	if (currentScreen == Screen::Level3 && G.Targets[5].isTouched && G.Targets[6].isTouched && G.doubleTargets[0].isTouched) {
		currentScreen = Screen::Level4;
		G.currentLevel++;
		InitAssetsDataLevel4(G);
		G.Targets[5].Pos = V2(0, 0);
		G.doubleTargets[0].Pos = V2(0, 0);
		G.Targets[6].Pos = V2(0, 0);
		G.Obstacles[0].Pos = V2(0, 0);
	}
	//Transition level4 -> level5
	if (currentScreen == Screen::Level4 && G.Targets[7].isTouched && G.smallTargets[1].isTouched && G.doubleTargets[1].isTouched) {
		currentScreen = Screen::Level5;
		G.currentLevel++;
		InitAssetsDataLevel5(G);
		G.Targets[7].Pos = V2(0, 0);
		G.doubleTargets[1].Pos = V2(0, 0);
		G.smallTargets[1].Pos = V2(0, 0);
		G.Obstacles[1].Pos = V2(0, 0);
		G.Obstacles[2].Pos = V2(0, 0);
	}
	//Transition level5 -> win
	if (currentScreen == Screen::Level5 && G.Targets[8].isTouched && G.smallTargets[2].isTouched && G.bigTargets[1].isTouched) {
		currentScreen = Screen::Win;
	}
	//Transition gameover
	if (G.Spaceship.bulletCount == 0) {
		currentScreen = Screen::GameOver;
	}
}


///////////////////////////////////////////////////////////////////////////////
//
//
//        Démarrage de l'application

void AssetsInit(GameData& G)
{
	G.Spaceship.InitTextures();
}

int main(int argc, char* argv[])
{
	GameData G;

	G2D::initWindow(V2(G.WidthPix, G.HeighPix), V2(20, 20), string("Astro Barrier"));

	InitAssetsData(G);
	InitAssetsDataLevel1(G);
	AssetsInit(G);

	int callToLogicPerSec = 50;

	G2D::Run(Logic, Render, G, callToLogicPerSec, true);

}