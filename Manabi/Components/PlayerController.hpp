#pragma once

#include "../Source/Entity.h"

struct PlayerController {
	bool isGrounded;
	bool isJumping;
	float playerSpeed;

	Entity playerCamera;
};