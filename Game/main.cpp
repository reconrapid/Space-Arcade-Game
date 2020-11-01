#include <SFML/Graphics.hpp>
#include "userInterface.h"
#include "projectile.h"
#include "enemy.h"
#include <SFML/Audio.hpp>


#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include "Menu.h"

using namespace sf;
using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 800), "SFML works!");
	window.setFramerateLimit(60);

	Menu menu(window.getSize().x, window.getSize().y);

	int count = 0;
	bool dead = false;
	bool play = false;
	bool displayMenu = true;
	int level = 0;

	//READ LEVEL
	ifstream inFile;
	inFile.open("Levels/TestLevel.txt");

	if (inFile.fail()) {
		//failed to open level
	}

	int numOfEnemies;
	int waveNumber;
	int enemySpeed;
	int enemyType;

	inFile >> numOfEnemies;
	inFile >> waveNumber;
	inFile >> enemySpeed;
	inFile >> enemyType;

	cout << numOfEnemies << "\n";
	cout << waveNumber << "\n";
	cout << enemySpeed << "\n";
	cout << enemyType << "\n";



	//Frame Rate Clock
	sf::Clock clock;

	//NEW
	Vector2f mousePosWindow;
	Vector2f fireDir;
	Vector2f fireDirNorm;

	//Background

	sf::Texture back;
	if (!back.loadFromFile("Textures/background.png"))
	{
		// error...
	}

	sf::Sprite background;
	background.setTexture(back);
	background.scale(sf::Vector2f(1.f, 1.f));

	//Interface
	userInterface control;

	//MUSIC
	sf::Music music;

	if (!music.openFromFile("OST/Album/music.wav"))
		return -1; // error
	music.setVolume(20);
	music.play();

	//Sound Effects
	//FIRE SOUND EFFECT
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("OST/Effects/fire.wav")) {
		return -1; // error
	}

	sf::Sound sound;
	sound.setVolume(20);
	sound.setBuffer(buffer);

	//Ship Texture
	sf::Texture texture;
	if (!texture.loadFromFile("Textures/Sprite2.png"))
	{
		// error...
	}

	//Pointer to new sprite
	sf::Sprite *Player = new sf::Sprite();

	Player->setTexture(texture);
	Player->setTextureRect(sf::IntRect(0, 0, 16, 16));
	Player->setPosition(800, 400);
	Player->scale(sf::Vector2f(3.f, 3.f)); // factor relative to the current scale
	Player->setOrigin(8, 8); //Sets origin to centre of sprite 

	//Boss Texture
	sf::Texture textureBoss;
	if (!textureBoss.loadFromFile("Textures/Boss.png"))
	{
		// error...
	}

	//ENEMIES
	int enemyCounter = 10;
	std::vector<enemy> enemyArray;

	


	//FIRE WEAPON
	//Projectile Array
	std::vector<projectile> projectileArray;

	//Projectile Object
	projectile projectile1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				//If escape key is pressed escape
				return 0;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				menu.MoveUp();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				menu.MoveDown();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				if (menu.getPressedKey() == 0) {
					play = true;
					displayMenu = false;
				}
				if (menu.getPressedKey() == 1) {
					return 0;
				}
			}
		}

		window.clear();
		window.draw(background);

		//Frame Rate
		sf::Time time = clock.getElapsedTime();
		std::cout << 1.0f / time.asSeconds() << std::endl;
		clock.restart().asSeconds();
		//END Frame Rate

		//Open Main Menu
		if (displayMenu == true) {
			menu.Draw(window);
		}
		enemy boss;

		if (play == true) {
			if (dead == false) {
				// Spawn enemies in a variable wave number
				if (count < numOfEnemies) {
					for (int i = 0; i < numOfEnemies; i++) {
						for (int x = 0; enemyArray.size() <= waveNumber; x++) {
							int direction = rand() % 1400;

							if (x < waveNumber / 4) {
								boss.spriteEnemy.setTexture(textureBoss);
								boss.spriteEnemy.setPosition(-200, direction);
								boss.spriteEnemy.scale(sf::Vector2f(1.f, 1.f));
								boss.movementSpeed = enemySpeed;

								enemyArray.push_back(boss);
								count++;
							}

							if (x > waveNumber / 4 + waveNumber / 2) {
								boss.spriteEnemy.setTexture(textureBoss);
								boss.spriteEnemy.setPosition(2000, direction);
								boss.spriteEnemy.scale(sf::Vector2f(1.f, 1.f));
								boss.movementSpeed = enemySpeed;

								enemyArray.push_back(boss);
								count++;
							}

							if (x > waveNumber / 2) {
								boss.spriteEnemy.setTexture(textureBoss);
								boss.spriteEnemy.setPosition(direction, -200);
								boss.spriteEnemy.scale(sf::Vector2f(1.f, 1.f));
								boss.movementSpeed = enemySpeed;

								enemyArray.push_back(boss);
								count++;
							}
							if (x < waveNumber / 2) {
								boss.spriteEnemy.setTexture(textureBoss);
								boss.spriteEnemy.setPosition(direction, 1400);
								boss.spriteEnemy.scale(sf::Vector2f(1.f, 1.f));
								boss.movementSpeed = enemySpeed;

								enemyArray.push_back(boss);
								count++;
							}
						}
					}
				}

				//Check player input
				control.position = sf::Mouse::getPosition(window);
				control.isShipMoving(*Player);


				//Fire Direction
				mousePosWindow = Vector2f(Mouse::getPosition(window));
				sf::Vector2f curPos = Player->getPosition();
				fireDir = mousePosWindow - curPos;
				fireDirNorm = fireDir / sqrt(pow(fireDir.x, 2) + pow(fireDir.y, 2));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && dead == false) {
					//Fire sound effect
					sound.play();

					//Set position equal to player
					projectile1.bullet.setPosition(Player->getPosition());
					projectile1.vol = fireDirNorm * projectile1.movementSpeed;

					//Push back & create in the world
					projectileArray.push_back(projectile1);

				}
				//iterate through each object in projectileArray
				for (size_t i = 0; i < projectileArray.size(); i++) {

					projectileArray[i].bullet.move(projectileArray[i].vol);

					//Check that bullets are still on the screen
					if (projectileArray[i].bullet.getPosition().x < 0 || projectileArray[i].bullet.getPosition().x > window.getSize().x || projectileArray[i].bullet.getPosition().y < 0 || projectileArray[i].bullet.getPosition().y > window.getSize().y) {
						projectileArray.erase(projectileArray.begin() + i);
					}
					else {
						for (size_t x = 0; x < projectileArray.size(); x++) {
							for (size_t k = 0; k < enemyArray.size(); k++) {

								//COLLISION
								// get the bounding box of bullets
								sf::FloatRect boundingBox2 = projectileArray[x].bullet.getGlobalBounds();

								// check collision with enemies
								sf::FloatRect otherBox2 = enemyArray[k].spriteEnemy.getGlobalBounds();

								if (boundingBox2.intersects(otherBox2)) {
									enemyArray[k].life = enemyArray[k].life - projectileArray[x].damage;
									if (enemyArray[k].life <= 0) {
										enemyArray.erase(enemyArray.begin() + k);
									}
								}
							}
						}
					}
				}

				//Draw bullets
				for (size_t i = 0; i < projectileArray.size(); i++) {
					window.draw(projectileArray[i].bullet);

				}
				//ENEMIES
				//iterate through each object in projectileArray
				for (size_t i = 0; i < enemyArray.size(); i++) {
					//COLLISION
					// get the bounding boxes
					sf::FloatRect boundingBox = Player->getGlobalBounds();
					sf::FloatRect otherBox = enemyArray[i].spriteEnemy.getGlobalBounds();

					if (boundingBox.intersects(otherBox)) {
						control.health = control.health - boss.damage;
					}

					if (dead == false) {
						enemyArray[i].playerPosition = Player->getPosition();
						enemyArray[i].move();
						enemyArray[i].spriteEnemy.move(enemyArray[i].vol);
					}
					window.draw(enemyArray[i].spriteEnemy);

				}
			}

			// If player runs out of health
			if (control.health <= 0) {
				dead = true;
				//Player->scale(sf::Vector2f(0.f, 0.f)); // factor relative to the current scale
				sf::Font font;
				if (!font.loadFromFile("Font/Freedom/FREEDOM.ttf"))
				{
					// error...
				}
				sf::Text text[2];
				text[0].setFont(font);
				text[0].setString("GAME OVER");
				text[0].setCharacterSize(80);
				text[0].setFillColor(sf::Color::Red);

				text[0].setPosition(sf::Vector2f(200, 200));

				text[1].setFont(font);
				text[1].setString("PRESS ENTER TO RESTART THE LEVEL");
				text[1].setCharacterSize(40);
				text[1].setFillColor(sf::Color::Red);

				text[1].setPosition(sf::Vector2f(200, 400));

				window.draw(text[0]);
				window.draw(text[1]);

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {


					for (size_t k = 0; k < enemyArray.size(); k++) {
						enemyArray.erase(enemyArray.begin() + k);
					}

					//Player->scale(sf::Vector2f(1.f, 1.f)); // factor relative to the current scale
					Player->setPosition(800, 400);
					control.health = 10;
					count = 0;
					dead = false;
					play = false;
					displayMenu = true;

				}
			}

			// If player kills all enemies
			if (enemyArray.size() == 0) {
				if (level == 6) {
					sf::Font font;
					if (!font.loadFromFile("Font/Freedom/FREEDOM.ttf"))
					{
						// error...
					}
					sf::Text text[2];
					text[0].setFont(font);
					text[0].setString("YOU BEAT THE GAME!");
					text[0].setCharacterSize(80);
					text[0].setFillColor(sf::Color::Red);

					text[0].setPosition(sf::Vector2f(200, 200));

					text[1].setFont(font);
					text[1].setString("PRESS ENTER TO GO BACK TO THE MAIN MENU");
					text[1].setCharacterSize(40);
					text[1].setFillColor(sf::Color::Red);

					text[1].setPosition(sf::Vector2f(200, 400));

					window.draw(text[0]);
					window.draw(text[1]);
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

						for (size_t k = 0; k < enemyArray.size(); k++) {
							enemyArray.erase(enemyArray.begin() + k);
						}

						Player->setPosition(800, 400);
						control.health = 10;
						count = 0;
						dead = false;
						play = false;
						displayMenu = true;
						level = 0;
					}
				}
				else {
					sf::Font font;
					if (!font.loadFromFile("Font/Freedom/FREEDOM.ttf"))
					{
						// error...
					}
					sf::Text text[2];
					text[0].setFont(font);
					text[0].setString("YOU WIN!");
					text[0].setCharacterSize(80);
					text[0].setFillColor(sf::Color::Red);

					text[0].setPosition(sf::Vector2f(200, 200));

					text[1].setFont(font);
					text[1].setString("PRESS ENTER TO GO TO NEXT LEVEL!");
					text[1].setCharacterSize(40);
					text[1].setFillColor(sf::Color::Red);

					text[1].setPosition(sf::Vector2f(200, 400));

					window.draw(text[0]);
					window.draw(text[1]);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {

						//READ LEVEL
						level = level + 1;

						std::string levelStr = std::to_string(level);
						string file = "Levels/Level" + levelStr + ".txt";

						ifstream inFile;
						inFile.open(file);

						if (inFile.fail()) {
							//failed to open level
						}

						inFile >> numOfEnemies;
						inFile >> waveNumber;
						inFile >> enemySpeed;
						inFile >> enemyType;

						if (enemyType == 0) {
							if (!textureBoss.loadFromFile("Textures/Boss.png"))
							{
								// error...
							}
						}

						if (enemyType == 1) {
							if (!textureBoss.loadFromFile("Textures/F5S4.png"))
							{
								// error...
							}
						}
						if (enemyType == 2) {
							if (!textureBoss.loadFromFile("Textures/fighter.png"))
							{
								// error...
							}
						}
						count = 0;
					}
				}
			}
			window.draw(*Player);
		}
		window.display();
	}

	return 0;
}