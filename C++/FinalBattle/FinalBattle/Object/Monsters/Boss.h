#pragma once
class Boss : public Monster
{
public :

	struct AggroInfo
	{
		shared_ptr<Creature> Attacker;
		int totalDamage;
	};
	Boss(float hp, float atk, string name);
	virtual ~Boss();
	virtual void Attack(shared_ptr<Creature> victim) override;
	virtual void Damaged(float amount, shared_ptr<Creature> attacker = nullptr) override;
	
	void AttackPlayersByAggro();

	void Angry();
	

private :
	vector<AggroInfo> _aggrotable;
	int _range = 4;
};

