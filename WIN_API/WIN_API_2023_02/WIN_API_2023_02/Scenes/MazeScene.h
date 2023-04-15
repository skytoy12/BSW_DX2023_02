#pragma once
class MazeScene : public Scene
{
public :
	MazeScene();
	~MazeScene();
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private :
	shared_ptr<Maze> _maze;
	shared_ptr<MazeRunner> _runner;
};
