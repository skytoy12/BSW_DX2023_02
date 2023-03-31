#pragma once
class Archer : public Player, public enable_shared_from_this<Archer>
{
public :
	Archer(float hp, float atk, string name);
	virtual ~Archer();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _concentration = 0;
};

