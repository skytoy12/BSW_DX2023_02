#pragma once
<<<<<<< HEAD
class Magician : public Player, public enable_shared_from_this<Magician>
=======
class Magician : public Player
>>>>>>> 2e4d2fe2d450b077c17627bf5771d7baab763d76
{
public :
	Magician(float hp, float atk, string name);
	virtual ~Magician();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _MagicPoint = 0;
};

