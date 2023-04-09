#pragma once
#include "Input.h"

class Round
{
public:
	Round();
	~Round();

	void Initialize(Input* input);
	void RoundManagement();
	void AddRound();
	void Update();

private:
	int round = 0;
	int selection = 0;
	Input* input_ = nullptr;

};