#pragma once
class Player : public Creature
{
public :
	Player(float hp, float atk, string name);
	virtual ~Player();
	virtual void Attack(shared_ptr<Creature> victim) override;
	
	

protected :
	

};

