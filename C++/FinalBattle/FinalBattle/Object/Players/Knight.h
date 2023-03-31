#pragma once
<<<<<<< HEAD
class Knight : public Player, public enable_shared_from_this<Knight>
=======
class Knight : public Player
>>>>>>> 2e4d2fe2d450b077c17627bf5771d7baab763d76
{
public :
	Knight(float hp, float atk, string name);
	virtual ~Knight();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _stamina = 0;
};

