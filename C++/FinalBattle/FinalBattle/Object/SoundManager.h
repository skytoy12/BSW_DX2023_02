#pragma once
class SoundManager
{
private :
	SoundManager();
	~SoundManager();
public :
	static void Creat()
	{
		if (_instance == nullptr)
			_instance = new SoundManager();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static SoundManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;

		return nullptr;
	}

	void PAsound() { cout << _palyerattacksound << endl; }
	void AAsound() { cout << _archerattacksound << endl; }
	void KAsound() { cout << _knightattacksound << endl; }
	void MGAsound() { cout << _magicianattacksound << endl; }
	void MAsound() { cout << _monsterattacksound << endl; }
	void BAsound() { cout << _Bossattacksound << endl; }
	void TAsound() { cout << _tauntsound << endl; }
	void FBsound() { cout << _fireballsound << endl; }

private :
	static SoundManager* _instance;
	string _palyerattacksound;
	string _archerattacksound;
	string _knightattacksound;
	string _magicianattacksound;
	string _monsterattacksound;
	string _Bossattacksound;
	string _tauntsound;
	string _fireballsound;
};

