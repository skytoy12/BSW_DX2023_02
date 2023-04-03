#pragma once
class Program
{
public :
	Program();
	~Program();

	// 게임은 Updata와 Render가 두부분으로 갈린다.
	void Updata();
	void Render(HDC hdc);

private :
	shared_ptr<Scene> _curScene;
};

