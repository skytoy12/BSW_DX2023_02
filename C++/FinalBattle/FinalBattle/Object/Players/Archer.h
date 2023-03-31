#pragma once
<<<<<<< HEAD
class Archer : public Player, public enable_shared_from_this<Archer>
=======
class Archer : public Player
>>>>>>> 2e4d2fe2d450b077c17627bf5771d7baab763d76
{
public :
	Archer(float hp, float atk, string name);
	virtual ~Archer();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _concentration = 0;
};

