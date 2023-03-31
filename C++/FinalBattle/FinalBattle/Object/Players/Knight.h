#pragma once
class Knight : public Player, public enable_shared_from_this<Knight>
{
public :
	Knight(float hp, float atk, string name);
	virtual ~Knight();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _stamina = 0;
};

