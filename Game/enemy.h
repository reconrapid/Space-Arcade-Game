#pragma once
#ifndef ENEMY_H_
#define ENEMY_H_

#include <SFML/Graphics.hpp>
class enemy {

public:

	float movementSpeed = 2;
	int damage = 5;
	int life = 5000;
	int direction = 0; // 1 - up // 2 - down // 3 - left // 4 - right
	int counter = 0;
	sf::Vector2f vol;

	enemy();
	void move();
	sf::Sprite spriteEnemy;

	sf::Vector2f playerPosition;
	sf::Vector2f thisPosition;

	sf::Vector2f moveDir;
	sf::Vector2f moveDirNorm;

};
#endif