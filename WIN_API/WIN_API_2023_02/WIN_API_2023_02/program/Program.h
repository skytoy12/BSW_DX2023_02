#pragma once
class Program
{
public :
	Program();
	~Program();

	// ������ Updata�� Render�� �κκ����� ������.
	void Update();
	void Render(HDC hdc);

private :
	shared_ptr<Scene> _curScene;
};

