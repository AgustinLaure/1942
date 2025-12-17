#include "playing.h"

#include "player.h"
#include "button.h"
#include "enemy_spawner.h"
#include "screen.h"

namespace playing
{ 
	const static KeyboardKey pauseKey = KEY_ESCAPE;

	static Color backgroundColor = BLACK;

	static bool isPaused = false;
	static bool hasLost = false;

	static const int enemyNormalPlanePoolSize = 30;

	namespace objects
	{
		static player::Player player;
		static enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[enemyNormalPlanePoolSize];
	}

	namespace pause
	{
		//Title
		static const std::string titleFontRoute = "res/fonts/militar_font.otf";
		static const Color titleColor = WHITE;

		static const Vector2 titlePos = { screen::width/2 - 100, 150 };
		static const std::string titleText = "Pause";
		static const int titleFontSize = 100;
		static const int titleSpacing = 2;

		//AllButtons
		static const std::string buttonFontRoute = "res/fonts/militar_font.otf";
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
		static void deinit();
	}

	namespace lost
	{
		//Title
		static const std::string titleFontRoute = "res/fonts/militar_font.otf";
		static const Color titleColor = WHITE;

		static const Vector2 titlePos = { screen::width / 2 - 185, 100 };
		static const std::string titleText = "You lost!";
		static const int titleFontSize = 100;
		static const int titleSpacing = 2;

		//AllButtons
		static const std::string buttonFontRoute = "res/fonts/militar_font.otf";
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

		namespace objects
		{
			label::Label title;

			button::Button retry;
			button::Button menu;
		}

		static void init();
		static void update(gameScene::Scenes& currentGameScene);
		static void draw();
		static void deinit();
	}

	static void update(gameScene::Scenes& currentGameScene, const float deltaTime);
	static void draw();
	static void updateEnemies(const player::Player player, const float deltaTime);
	static void drawEnemies();
	static void handleCollisions();
	static void updateState();
	static void reset();

	namespace pause
	{
		static void init()
		{
			objects::title = label::init(titlePos,titleText,titleFontRoute,titleFontSize,titleSpacing,titleColor);

			objects::resume = button::init(resumeWidth, resumeHeight, resumePos,resumeText,buttonFontRoute,resumeFontSize,resumeSpacing,buttonTextColor,buttonBoxColor);
			objects::menu = button::init(menuWidth, menuHeight, menuPos, menuText,buttonFontRoute, menuFontSize, menuSpacing,buttonTextColor,buttonBoxColor);
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
				currentGameScene = gameScene::Scenes::MainMenu;
				
				reset();
			}
		}

		static void draw()
		{
			label::draw(objects::title);

			button::draw(objects::resume);
			button::draw(objects::menu);
		}

		static void deinit()
		{
			label::deinit(objects::title);

			button::deinit(objects::resume);
			button::deinit(objects::menu);
		}
	}

	namespace lost
	{
		static void init()
		{
			objects::title = label::init(titlePos,titleText,titleFontRoute,titleFontSize,titleSpacing,titleColor);

			objects::retry = button::init(retryWidth, retryHeight, retryPos, retryText,buttonFontRoute, retryFontSize, retrySpacing,buttonTextColor,buttonBoxColor);
			objects::menu = button::init(menuWidth, menuHeight, menuPos, menuText,buttonFontRoute, menuFontSize, menuSpacing,buttonTextColor,buttonBoxColor);
		}

		static void update(gameScene::Scenes& currentGameScene)
		{
			button::update(objects::retry);
			button::update(objects::menu);

			if (objects::retry.isPressed)
			{
				reset();
			}
			if (objects::menu.isPressed)
			{
				reset();
				currentGameScene = gameScene::Scenes::MainMenu;
			}
		}

		static void draw()
		{
			label::draw(objects::title);

			button::draw(objects::retry);
			button::draw(objects::menu);
		}

		static void deinit()
		{
			label::deinit(objects::title);

			button::deinit(objects::retry);
			button::deinit(objects::menu);
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

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}

		pause::init();
		lost::init();
	}

	void deinit()
	{
		pause::deinit();
		lost::deinit();
	}

	static void update(gameScene::Scenes& currentGameScene, const float deltaTime)
	{
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
		}
		else if (isPaused)
		{
			pause::update(currentGameScene);
		}

		currentGameScene;
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		player::draw(objects::player);
		drawEnemies();

		if (hasLost)
		{
			lost::draw();
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
						}
					}
				}

				//Self to player

				if (shape::isRectOnRect(currentEnemyNormalPlane->hitBox, objects::player.hitBox))
				{
					player::onCrash(objects::player);
					enemyNormalPlane::onCrash(*currentEnemyNormalPlane);
				}
			}
		}
	}

	static void updateState()
	{
		if (IsKeyPressed(pauseKey))
		{
			isPaused = !isPaused;
		}

		if (!objects::player.isAlive)
		{
			hasLost = true;
		}
	}

	static void reset()
	{
		isPaused = false;
		hasLost = false;
		
		objects::player = player::init();

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}
	}
}
