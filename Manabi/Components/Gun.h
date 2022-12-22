#pragma once

struct Gun {
	bool isEquipped;
	bool shoot;

	int maxBullet;

	float fireRateTimer;
	float fireRate;
};