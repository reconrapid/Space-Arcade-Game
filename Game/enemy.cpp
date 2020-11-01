#include "enemy.h"

enemy::enemy() {


}

void enemy::move(){


	/*direction = rand() % 100;   

	if (direction == 1) {
		spriteEnemy.move(0, -movementSpeed);
	}
	else if (direction == 2) {
		spriteEnemy.move(0, movementSpeed);
	}
	else if (direction == 3) {
		spriteEnemy.move(-movementSpeed, 0);
	}
	else if (direction == 4) {
		spriteEnemy.move(movementSpeed, 0);
	}
	else {

	}*/

	// Make movement
	thisPosition = spriteEnemy.getPosition();
	moveDir = playerPosition - thisPosition;
	moveDirNorm = moveDir / sqrt(pow(moveDir.x, 2) + pow(moveDir.y, 2));
	vol = moveDirNorm * movementSpeed;

	float angle = atan2(playerPosition.y - thisPosition.y, playerPosition.x - thisPosition.x) * 180 / 3.141;
	spriteEnemy.setRotation(angle - 90.f);






}