#pragma once
class Magician : public Player
{
public :
	Magician(float hp, float atk, string name);
	virtual ~Magician();
	virtual void Attack(shared_ptr<Creature> victim) override;

private :
	int _MagicPoint = 0;
};

