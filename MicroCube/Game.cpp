#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	InitWindow(this->widthScreen, this->heightScreen, this->gameName.c_str());
	SetTargetFPS(60);

	player.Start();
	kimpo_TEX = LoadTexture("srcs/CI.png");
}

void Game::Run()
{
	while (isRunning)
	{
		cameraController.UpdateCameraShake();

		BeginDrawing();

		BeginMode2D(cameraController.currentCamera());

		this->Update();
		this->Render();

		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
}

void Game::Update()
{
	if (gameManager.gameStates == gameManager.INTRO_SCREEN)
	{
		if (IsKeyPressed(KEY_X))
			gameManager.gameStates = gameManager.MAIN_MENU;

		if (IsKeyPressed(KEY_ESCAPE))
			isRunning = false;

		gimpo_Y = Lerp(gimpo_Y, 50, 0.2f);
		gimpo_T_Y = Lerp(gimpo_T_Y, 500, 0.15f);
	}
	else if (gameManager.gameStates == gameManager.MAIN_MENU)
	{
		if (IsKeyPressed(KEY_X))
			gameManager.gameStates = gameManager.IN_GAME;

		if (IsKeyPressed(KEY_ESCAPE))
		{
			gimpo_Y = -1200;
			gimpo_T_Y = 1200;

			gameManager.gameStates = gameManager.INTRO_SCREEN;
		}
	}
	else if (gameManager.gameStates == gameManager.IN_GAME)
	{
		this->InGame();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			AllClear();
			gameManager.gameStates = gameManager.MAIN_MENU;
		}
	}
	else if (gameManager.gameStates == gameManager.GAME_OVER)
	{
		if (IsKeyPressed(KEY_R))
		{
			AllClear();
			gameManager.gameStates = gameManager.IN_GAME;
		}

		if (IsKeyPressed(KEY_ESCAPE)) 
		{
			AllClear();
			gameManager.gameStates = gameManager.MAIN_MENU;
		}
	}
}

void Game::Render()
{
	ClearBackground(RAYWHITE);

	if (gameManager.gameStates == gameManager.INTRO_SCREEN)
	{
		DrawTexture(this->kimpo_TEX, 200, gimpo_Y, WHITE);
		DrawText("The Game", 350, gimpo_T_Y, 60, BROWN);

		DrawText("Press [X] to Start!", 400, 650, 30, BROWN);
	}
	else if (gameManager.gameStates == gameManager.MAIN_MENU)
	{
		DrawTexture(this->kimpo_TEX, 200, 50, WHITE);
		DrawText("The Game", 350, 500, 60, BROWN);

		DrawText("[X] : GamePlay / [ESC] : Return Screen", 300, 650, 30, BROWN);
	}
	else if (gameManager.gameStates == gameManager.IN_GAME)
	{
		this->InGameDraw();
	}
	else if (gameManager.gameStates == gameManager.GAME_OVER)
	{
		DrawText("GAME OVER", 400, 250, 80, RED);
		DrawText("Press [R] to Restart!", 470, 350, 30, BROWN);
	}
}

void Game::ToggleFullscreenController()
{
	if (!IsWindowFullscreen())
	{
		SetWindowSize(1280, 720);
		ToggleFullscreen();
	}
	else {
		ToggleFullscreen();
		SetWindowSize(1280, 720);
	}
}

void Game::InGame()
{
	if (player.CheckDead())
	{
		cameraController.StartCameraShake(0.5f, 5.5f);
		gameManager.gameStates = gameManager.GAME_OVER;
	}

	if (IsKeyPressed(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
	{
		this->ToggleFullscreenController();
	}

	player.Update();

	if (GetTime() >= nextTime)
	{
		if (!player.CheckDead())
		{
			if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
				cameraController.StartCameraShake(0.25f, 1.5f);
				SpawnBullet(true);
			}
			else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
				cameraController.StartCameraShake(0.25f, 1.5f);
				SpawnBullet(false);
			}
		}

		nextTime = GetTime() + 0.05f;
	}


	for (auto enemy = enemies.begin(); enemy != enemies.end();)
	{
		(*enemy)->Update();

		if ((*enemy)->getFireMode())
		{
			enemyBullets.push_back(std::make_shared<EnemyBullet>((*enemy)->getX() + 15.0f, (*enemy)->getY()));
			(*enemy)->TurnOff_FireMode();
		}

		std::string enemyTag = "Enemy";

		if ((*enemy)->Tag() == enemyTag)
		{
			if (player.onCollisionEnter((*enemy).get(), 300.0f))
			{
				if (!(*enemy)->CheckDead())
				{
					cameraController.StartCameraShake(0.25f, 8.0f);
					player.TakeDamage(5);
				}
				else
				{
					cameraController.StartCameraShake(0.25f, 2.0f);
					player.TakeHealth(10);
					gameManager.AddScore(1);
				}

				enemy = enemies.erase(enemy);
				continue;
			}
		}

		if ((*enemy)->IsDestroyed())
		{
			enemy = enemies.erase(enemy);
			continue;
		}

		++enemy;
	}

	for (auto enemyBullet = enemyBullets.begin(); enemyBullet != enemyBullets.end();)
	{
		(*enemyBullet)->Update();

		if (player.onCollisionDamage((*enemyBullet).get()))
		{
			cameraController.StartCameraShake(0.25f, 8.0f);
			player.TakeDamage(10);
			enemyBullet = enemyBullets.erase(enemyBullet);
			continue;
		}

		if ((*enemyBullet)->IsDestroyed())
		{
			enemyBullet = enemyBullets.erase(enemyBullet);
			continue;
		}

		++enemyBullet;
	}

	for (auto bullet = bullets.begin(); bullet != bullets.end();)
	{
		(*bullet)->Update();

		if ((*bullet)->IsDestroyed())
		{
			bullet = bullets.erase(bullet);
			continue;
		}

		bool isColl = false;

		if (!enemies.empty())
		{
			for (auto enemy = enemies.begin(); enemy != enemies.end(); ++enemy)
			{
				if ((*bullet)->onCollisionEnter((*enemy).get()))
				{
					if ((*bullet)->gisUpper())
					{
						(*enemy)->SetYDown(10);
					}
					else {
						(*enemy)->SetYUP(10);
					}

					(*enemy)->TakeDamage(10);

					bullet = bullets.erase(bullet);
					isColl = true;
					break;
				}
			}
		}

		if (!isColl)
			++bullet;
	}

	if (enemies.empty())
		SpawnEnemy(GetRandomValue(1, 5));
}

void Game::InGameDraw()
{
	DrawTexture(this->kimpo_TEX, 200, 50, WHITE);
	DrawText("The Game", 350, 500, 60, BROWN);
	DrawText(TextFormat("HP: %i", player.getHP()), 50, 50, 30, RED);
	DrawText(TextFormat("Score: %i", gameManager.getScore()), 1100, 50, 30, RED);


	player.Draw();

	for (auto& gameObject : enemies)
		gameObject->Draw();

	for (auto& bullet : bullets)
		bullet->Draw();

	for (auto& enemyBullet : enemyBullets)
		enemyBullet->Draw();
}

void Game::SpawnBullet(bool isUpper)
{
	if (isUpper)
		bullets.push_back(std::make_shared<Bullet>(player.getX() + 5.0f, player.getY(), true));
	else
		bullets.push_back(std::make_shared<Bullet>(player.getX() + 5.0f, player.getY(), false));
}

void Game::SpawnEnemy(int len)
{
	for (int i = 0; i < len; i++)
	{
		enemies.push_back(std::make_unique<Enemy>());
	}
}

void Game::AllClear()
{
	enemies.clear();
	enemyBullets.clear();
	bullets.clear();

	player.ReturnHealth();
	gameManager.ReturnScore();
}
