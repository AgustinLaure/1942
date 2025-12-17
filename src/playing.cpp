#include "playing.h"

#include "player.h"
#include "button.h"
#include "enemy_spawner.h"
#include "screen.h"

namespace playing
{
	static const label::FontName scoreHUDFont = label::FontName::Militar;
	static const Color scoreHUDColor = WHITE;

	static const Vector2 scoreHUDPos = { screen::width - 200, screen::height - 100 };
	static const std::string scoreHUDText = "Score: ";
	static const int scoreHUDFontSize = 30;
	static const int scoreHUDSpacing = 2;

	static const label::FontName hpHUDFont = label::FontName::Militar;
	static const Color hpHUDColor = WHITE;

	static const Vector2 hpHUDPos = { 100, screen::height - 100 };
	static const std::string hpHUDText = "HP: ";
	static const int hpHUDFontSize = 30;
	static const int hpHUDSpacing = 2;

	const static KeyboardKey pauseKey = KEY_ESCAPE;

	static Color backgroundColor = BLACK;

	static bool isPaused = false;
	static bool hasLost = false;

	static const int enemyNormalPlanePoolSize = 30;

	namespace objects
	{
		static player::Player player;
		static enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[enemyNormalPlanePoolSize];

		static label::Label scoreHUD;
		static label::Label hpHUD;

		static Music playingMusic;
	}

	namespace pause
	{
		//Title
		static const label::FontName titleFont = label::FontName::Militar;
		static const Color titleColor = WHITE;

		static const Vector2 titlePos = { screen::width / 2 - 100, 150 };
		static const std::string titleText = "Pause";
		static const int titleFontSize = 100;
		static const int titleSpacing = 2;

		//AllButtons
		static const label::FontName buttonFont = label::FontName::Militar;
		static const Color buttonTextColor = WHITE;
		static const Color buttonBoxColor = RED;

		//ResumeButton
		static const Vector2 resumePos = { 300, screen::height - 200 };
		static const float resumeWidth = 197.f;
		static const float resumeHeight = 50.f;
		static const std::string resumeText = "Resume";
		static const int resumeFontSize = 60;
		static const int resumeSpacing = 2;

		//ExitButton
		static const Vector2 menuPos = { 650, screen::height - 200 };
		static const float menuWidth = 140.f;
		static const float menuHeight = 50.f;
		static const std::string menuText = "Menu";
		static const int menuFontSize = 60;
		static const int menuSpacing = 2;

		namespace objects
		{
			label::Label title;

			button::Button resume;
			button::Button menu;
		}

		static void init();
		static void update(gameScene::Scenes& currentGameScene);
		static void draw();
	}

	namespace lost
	{
		//Title
		static const label::FontName titleFont = label::FontName::Militar;
		static const Color titleColor = WHITE;

		static const Vector2 titlePos = { screen::width / 2 - 175, 100 };
		static const std::string titleText = "You lost!";
		static const int titleFontSize = 100;
		static const int titleSpacing = 2;

		static const label::FontName scoreFont = label::FontName::Militar;
		static const Color scoreColor = WHITE;

		static const Vector2 scorePos = { screen::width / 2 - 60, 325 };
		static const std::string scoreText = "Score: ";
		static const int scoreFontSize = 40;
		static const int scoreSpacing = 2;

		//AllButtons
		static const label::FontName buttonFont = label::FontName::Militar;
		static const Color buttonTextColor = WHITE;
		static const Color buttonBoxColor = RED;

		//ExitButton
		static const Vector2 retryPos = { 300, screen::height - 200 };
		static const float retryWidth = 158.f;
		static const float retryHeight = 50.f;
		static const std::string retryText = "Retry";
		static const int retryFontSize = 60;
		static const int retrySpacing = 2;

		//ExitButton
		static const Vector2 menuPos = { 650, screen::height - 200 };
		static const float menuWidth = 140.f;
		static const float menuHeight = 50.f;
		static const std::string menuText = "Menu";
		static const int menuFontSize = 60;
		static const int menuSpacing = 2;

		static const float lostMusicVolumeScale = 0.1f;
		static const float lostMusicStart = 0.3f;

		namespace objects
		{
			label::Label title;
			label::Label score;

			button::Button retry;
			button::Button menu;

			static Music lostMusic;
		}

		static void init();
		static void update(gameScene::Scenes& currentGameScene);
		static void draw(const float score);
		static void deinit();
	}

	static void update(gameScene::Scenes& currentGameScene, const float deltaTime);
	static void draw();
	static void updateEnemies(const player::Player player, const float deltaTime);
	static void drawEnemies();
	static void handleCollisions();
	static void updateState();
	static void reset();
	static void backToMenu(gameScene::Scenes& currentGameScene);
	static void drawHud();

	namespace pause
	{
		static void init()
		{
			objects::title = label::init(titlePos, titleText, titleFont, titleFontSize, titleSpacing, titleColor);

			objects::resume = button::init(resumeWidth, resumeHeight, resumePos, resumeText, buttonFont, resumeFontSize, resumeSpacing, buttonTextColor, buttonBoxColor);
			objects::menu = button::init(menuWidth, menuHeight, menuPos, menuText, buttonFont, menuFontSize, menuSpacing, buttonTextColor, buttonBoxColor);
		}

		static void update(gameScene::Scenes& currentGameScene)
		{
			button::update(objects::resume);
			button::update(objects::menu);

			if (objects::resume.isPressed)
			{
				isPaused = false;
			}

			if (objects::menu.isPressed)
			{
				backToMenu(currentGameScene);
			}
		}

		static void draw()
		{
			label::draw(objects::title);

			button::draw(objects::resume);
			button::draw(objects::menu);
		}
	}

	namespace lost
	{
		static void init()
		{
			objects::title = label::init(titlePos, titleText, titleFont, titleFontSize, titleSpacing, titleColor);
			objects::score = label::init(scorePos, scoreText, scoreFont, scoreFontSize, scoreSpacing, scoreColor);

			objects::retry = button::init(retryWidth, retryHeight, retryPos, retryText, buttonFont, retryFontSize, retrySpacing, buttonTextColor, buttonBoxColor);
			objects::menu = button::init(menuWidth, menuHeight, menuPos, menuText, buttonFont, menuFontSize, menuSpacing, buttonTextColor, buttonBoxColor);

			objects::lostMusic = LoadMusicStream("res/sounds/music/lost.ogg");
			SetMusicVolume(objects::lostMusic, lostMusicVolumeScale);
			objects::lostMusic.looping = true;
		}

		static void update(gameScene::Scenes& currentGameScene)
		{
			if (!IsMusicStreamPlaying(objects::lostMusic))
			{
				PlayMusicStream(objects::lostMusic);
				SeekMusicStream(objects::lostMusic, lostMusicStart);
			}

			button::update(objects::retry);
			button::update(objects::menu);

			if (objects::retry.isPressed)
			{
				reset();
			}
			if (objects::menu.isPressed)
			{
				backToMenu(currentGameScene);
			}
		}

		static void draw(const float score)
		{
			label::draw(objects::title);

			objects::score.text = scoreText + std::to_string(static_cast<int>(score));
			label::draw(objects::score);

			button::draw(objects::retry);
			button::draw(objects::menu);
		}

		static void deinit()
		{
			UnloadMusicStream(objects::lostMusic);
		}
	}

	void playing(gameScene::Scenes& currentGameScene, const float deltaTime)
	{
		update(currentGameScene, deltaTime);
		draw();
	}

	void init()
	{
		objects::player = player::init();

		objects::hpHUD = label::init(hpHUDPos, hpHUDText, hpHUDFont, hpHUDFontSize, hpHUDSpacing, hpHUDColor);
		objects::scoreHUD = label::init(scoreHUDPos, scoreHUDText, scoreHUDFont, scoreHUDFontSize, scoreHUDSpacing, scoreHUDColor);

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}

		objects::playingMusic = LoadMusicStream("res/sounds/music/playing.ogg");
		SetMusicVolume(objects::playingMusic, 0.1f);
		objects::playingMusic.looping = true;

		pause::init();
		lost::init();
	}

	void deinit()
	{
		UnloadMusicStream(objects::playingMusic);

		lost::deinit();
		player::deinit();
		enemyNormalPlane::deinit();
		bullet::deinit();
		label::deinit();
		button::deinit();
	}

	static void update(gameScene::Scenes& currentGameScene, const float deltaTime)
	{
		if (!IsMusicStreamPlaying(objects::playingMusic))
		{
			PlayMusicStream(objects::playingMusic);
		}

		updateState();

		if (!isPaused && !hasLost)
		{
			player::update(objects::player, deltaTime);
			enemySpawner::update(objects::enemyNormalPlanes, enemyNormalPlanePoolSize, deltaTime);
			updateEnemies(objects::player, deltaTime);
			handleCollisions();
		}
		else if (hasLost)
		{
			lost::update(currentGameScene);
			UpdateMusicStream(lost::objects::lostMusic);
		}
		else if (isPaused)
		{
			pause::update(currentGameScene);
		}

		UpdateMusicStream(objects::playingMusic);
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		player::draw(objects::player);
		drawEnemies();

		if (hasLost)
		{
			lost::draw(objects::player.score);
		}
		else
		{
			drawHud();
		}

		if (isPaused)
		{
			pause::draw();
		}

		EndDrawing();
	}

	static void updateEnemies(const player::Player player, const float deltaTime)
	{
		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::update(objects::enemyNormalPlanes[i], player, deltaTime);
		}
	}

	static void drawEnemies()
	{
		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::draw(objects::enemyNormalPlanes[i]);
		}
	}

	static void handleCollisions()
	{
		//Player bullets to enemy

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::EnemyNormalPlane* currentEnemyNormalPlane = &objects::enemyNormalPlanes[i];

			//Self bullets to player
			for (int j = 0; j < enemyNormalPlane::maxBulletsPool; j++)
			{
				bullet::Bullet* currentBullet = &currentEnemyNormalPlane->bullets[j];

				if (currentBullet->isAlive)
				{
					if (shape::isRectOnRect(objects::player.hitBox, currentBullet->hitBox))
					{
						player::onHit(objects::player, currentBullet->damage);
						bullet::onCollision(*currentBullet);
					}
				}
			}

			if (currentEnemyNormalPlane->isAlive)
			{
				//Self to player bullets

				for (int j = 0; j < player::maxBulletsPool; j++)
				{
					bullet::Bullet* currentBullet = &objects::player.bullets[j];

					if (currentBullet->isAlive)
					{
						if (shape::isRectOnRect(currentEnemyNormalPlane->hitBox, currentBullet->hitBox))
						{
							enemyNormalPlane::onHit(*currentEnemyNormalPlane, currentBullet->damage);
							bullet::onCollision(*currentBullet);

							player::scoreAddHit(objects::player);

							if (!currentEnemyNormalPlane->isAlive)
							{
								player::scoreAddKill(objects::player);
							}
						}
					}
				}

				//Self to player

				if (shape::isRectOnRect(currentEnemyNormalPlane->hitBox, objects::player.hitBox))
				{
					player::onCrash(objects::player);
					enemyNormalPlane::onCrash(*currentEnemyNormalPlane);

					if (!currentEnemyNormalPlane->isAlive)
					{
						player::scoreAddKill(objects::player);
					}
				}
			}
		}
	}

	static void updateState()
	{
		if (IsKeyPressed(pauseKey) && !hasLost)
		{
			isPaused = !isPaused;
		}

		if (!objects::player.isAlive)
		{
			hasLost = true;
			PauseMusicStream(objects::playingMusic);
		}
	}

	static void reset()
	{
		isPaused = false;
		hasLost = false;

		objects::player = player::init();

		StopMusicStream(objects::playingMusic);
		StopMusicStream(lost::objects::lostMusic);

		enemySpawner::reset();

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}
	}

	static void backToMenu(gameScene::Scenes& currentGameScene)
	{
		currentGameScene = gameScene::Scenes::MainMenu;
		reset();
	}

	static void drawHud()
	{
		objects::hpHUD.text = hpHUDText + std::to_string(static_cast<int>(objects::player.hp));
		objects::scoreHUD.text = scoreHUDText + std::to_string(static_cast<int>(objects::player.score));

		label::draw(objects::hpHUD);
		label::draw(objects::scoreHUD);
	}
}
