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

	// ToggleFullscreenController();

	player.Start();
	kimpo_TEX = LoadTexture("srcs/CI.png");
	introScreen.Start();
	gimpoAnim.Start();
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

	player.UnLoad();
	introScreen.UnLoad();
	gimpoAnim.UnLoad();
	CloseWindow();
}

void Game::Update()
{
	if (IsKeyPressed(KEY_ENTER))
	{
		this->ToggleFullscreenController();
	}

	if (gameManager.gameStates == gameManager.SKAGO_GAMES_INTRO)
	{
		introScreen.Update(&cameraController, &gameManager);
	}
	else if (gameManager.gameStates == gameManager.INTRO_SCREEN)
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
			gameManager.gameStates = gameManager.TUTORAL;

		if (IsKeyPressed(KEY_ESCAPE))
		{
			gimpo_Y = -1200;
			gimpo_T_Y = 1200;

			gameManager.gameStates = gameManager.INTRO_SCREEN;

			this->commandTEXT = 1200;
		}

		commandTEXT = Lerp(commandTEXT, 630, 0.15f);
	}
	else if (gameManager.gameStates == gameManager.TUTORAL)
	{
		if (IsKeyPressed(KEY_SPACE))
			gameManager.gameStates = gameManager.READY;
	}
	else if (gameManager.gameStates == gameManager.READY)
	{
		gameManager.ReadyTime();
		gimpoAnim.Update();
	}
	else if (gameManager.gameStates == gameManager.IN_GAME)
	{
		this->InGame();
		gameManager.Update(&cameraController);

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
			gameManager.gameStates = gameManager.READY;
		}

		if (IsKeyPressed(KEY_ESCAPE)) 
		{
			AllClear();
			gameManager.gameStates = gameManager.MAIN_MENU;
		}
	}
	else if (gameManager.gameStates == gameManager.GAME_CLEAR)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			NextClear();
		}
	}
}

void Game::Render()
{
	ClearBackground(RAYWHITE);

	if (gameManager.gameStates == gameManager.SKAGO_GAMES_INTRO)
	{
		introScreen.Draw();
	}
	else if (gameManager.gameStates == gameManager.INTRO_SCREEN)
	{
		DrawTexture(this->kimpo_TEX, 200, gimpo_Y, WHITE);
		DrawText("The Game", 350, gimpo_T_Y, 60, BROWN);

		DrawText("Press [X] to Start!", 800, 630, 30, BROWN);
		DrawText("SkagoGames 2023. made in Skago.", 100, 650, 20, BROWN);
	}
	else if (gameManager.gameStates == gameManager.MAIN_MENU)
	{
		DrawTexture(this->kimpo_TEX, 200, 50, WHITE);
		DrawText("The Game", 350, 500, 60, BROWN);

		DrawText("[X] : GamePlay / [ESC] : Return Screen", 600, commandTEXT, 30, BROWN);
		DrawText("SkagoGames 2023. made in Skago.", 100, (commandTEXT+20), 20, BROWN);
	}
	else if (gameManager.gameStates == gameManager.TUTORAL)
	{
		DrawText("How To Play?", 380, 150, 80, GREEN);

		int textWidth1 = MeasureText("[A][D] : Movement", 30);
		int textX1 = (1280 - textWidth1) / 2;
		DrawText("[A][D] : Movement", textX1, 300, 30, GRAY);

		int textWidth2 = MeasureText("[W][S] : Shoot Bullet", 30);
		int textX2 = (1280 - textWidth2) / 2;
		DrawText("[W][S] : Shoot Bullet", textX2, 350, 30, GRAY);

		int textWidth3 = MeasureText("[SPACE] : Jump", 30);
		int textX3 = (1280 - textWidth3) / 2;
		DrawText("[SPACE] : Jump", textX3, 400, 30, GRAY);

		int textWidth4 = MeasureText("The player's goal is to paralyze the gold cloud in 60 seconds, \nstepping on the cloud and moving up. PRESS [SPACE] TO START!", 20);
		int textX4 = (1280 - textWidth4) / 2;
		DrawText("The player's goal is to paralyze the gold cloud in 60 seconds, \nstepping on the cloud and moving up. PRESS [SPACE] TO START!", textX4, 450, 20, GRAY);
	}
	else if (gameManager.gameStates == gameManager.READY)
	{
		if (gameManager.getLevelIDX() == 1)
			DrawText("Let's Escape!", 380, 150, 80, BROWN);
		else if (gameManager.getLevelIDX() >= 2)
			DrawText("Let's Escape again!", 270, 150, 80, BROWN);

		int textWidth1 = MeasureText("275, Gimpo Hangang 11-ro, Gimpo-si, Gyeonggi-do, Republic of Korea", 25);
		int textX1 = (1280 - textWidth1) / 2;
		DrawText("275, Gimpo Hangang 11-ro, Gimpo-si, Gyeonggi-do, Republic of Korea", textX1, 300, 25, GRAY);

		gimpoAnim.Draw();
	}
	else if (gameManager.gameStates == gameManager.IN_GAME)
	{
		this->InGameDraw();

		DrawText(TextFormat("Level  %i\t\tTime : %i", gameManager.getLevelIDX(), gameManager.getLimitTime()), 350, 30, 40, BLACK);
	}
	else if (gameManager.gameStates == gameManager.GAME_OVER)
	{
		DrawText("GAME OVER", 400, 250, 80, RED);
		DrawText("Press [R] to Restart!", 470, 350, 30, BROWN);
	}
	else if (gameManager.gameStates == gameManager.GAME_CLEAR)
	{
		DrawText("GAME CLEAR!", 380, 250, 80, GREEN);
		DrawText("Press [SPACE] Next Level!", 460, 350, 30, BROWN);
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

	player.Update(&gameManager);

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
			if ((*enemy)->getY() > player.getY())
				enemyBullets.push_back(std::make_shared<EnemyBullet>((*enemy)->getX() + 15.0f, (*enemy)->getY(), false));
			else if ((*enemy)->getY() < player.getY())
				enemyBullets.push_back(std::make_shared<EnemyBullet>((*enemy)->getX() + 15.0f, (*enemy)->getY(), true));

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
			player.TakeDamage(100);
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
	{
		nextSpawnCount++;
		SpawnEnemy(nextSpawnCount);
	}
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

	this->commandTEXT = 1200;

	this->gimpo_Y = -1200;
	this->gimpo_T_Y = 1200;

	nextSpawnCount = 1;
}

void Game::NextClear()
{
	enemyBullets.clear();
	bullets.clear();

	player.ReturnHealth();
	gameManager.NextLevel();

	nextSpawnCount++;

	gameManager.gameStates = gameManager.READY;
}
