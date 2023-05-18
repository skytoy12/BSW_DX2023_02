#pragma once
class SolorSystem : public Scene
{
public :
	SolorSystem();
	virtual~SolorSystem();

	virtual void Update() override;

	virtual void Render() override;


private :
	shared_ptr<class Planet> _planetSun;
	shared_ptr<class Planet> _planetEarth;
	shared_ptr<class Planet> _planetMoon;

	shared_ptr<Dungreed> _player;

};

