#pragma once
class EliteMonster : public Monster
{
public :
	EliteMonster();
	~EliteMonster();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Attack() override;

private :

};

