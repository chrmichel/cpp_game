#pragma once

#include "Components.h"

struct Damage {
	int melee;
	int ranged;
	int fire;
	int ice;
};

class CombatComponent : public Component {
public:
	CombatComponent(int mh, int ms, int mm, int str)
	:maxHealth(mh), maxStamina(ms), health(mh), stamina(ms), strength(str) {
		resistance = { 0, 0, 0, 0 };
	}
	~CombatComponent() {}
	void init() {}
	void update() {
	}
	void draw() {}
	Damage dealDamage() {
		return {strength, 0, 0, 0};
	}
	void takeDamage(Damage atkdmg) {
		if (atkdmg.melee > resistance.melee) {
			health -= (atkdmg.melee - resistance.melee);
		}
		if (atkdmg.melee > resistance.melee) {
			health -= (atkdmg.melee - resistance.melee);
		}
		if (atkdmg.melee > resistance.melee) {
			health -= (atkdmg.melee - resistance.melee);
		}
		if (atkdmg.melee > resistance.melee) {
			health -= (atkdmg.melee - resistance.melee);
		}
	}
private:
	int maxHealth;
	int maxStamina;
	int health;
	int stamina;

	float health_regen = 0.3;
	float stamina_regen = 0.5;
	
	int strength;
	Damage resistance;
};