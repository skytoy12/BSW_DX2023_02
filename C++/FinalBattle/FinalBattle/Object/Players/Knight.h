#pragma once
class Knight : public Player
{
public :
	Knight(float hp, float atk, string name);
	virtual ~Knight();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _stamina = 0;
};

