#include "Round.h"

Round::Round()
{
}

Round::~Round()
{
}

void Round::Initialize(Input* input)
{
	input_ = input;
}

void Round::RoundManagement()
{
	
}

void Round::AddRound()
{
	round++;
}

void Round::Update()
{
	if (input_->TriggerKey(DIK_UP)) {
		if (selection < 2) {
			selection++;
		}
	}
	if (input_->TriggerKey(DIK_DOWN)) {
		if (selection > 0) {
			selection--;
		}
	}
}
