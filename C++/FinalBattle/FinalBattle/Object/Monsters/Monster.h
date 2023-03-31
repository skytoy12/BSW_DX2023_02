#pragma once
class Monster : public Creature
{
public :
	Monster(float hp, float atk, string name);
	~Monster();
	virtual void Attack(shared_ptr<Creature> victim) override;
	virtual void MonsterAttack(vector<shared_ptr<Creature>> victim, int size);

private :
};

