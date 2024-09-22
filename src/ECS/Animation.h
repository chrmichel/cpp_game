#pragma once

struct Animation {
	int index{}, frame{}, speed{};

	Animation() {}
	Animation(int i, int f, int s) : index{ i }, frame{ f }, speed{ s } {}
};