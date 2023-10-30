#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreateViewport();
	void CreatePerspective();
	void CreateOrthographic();

public :
	void SetEnvironment();
	void PostSet();

	void PostRender();

	Matrix GetPersMatrix() { return persMatrix; }

private:
	MatrixBuffer* persBuffer;
	Matrix        persMatrix;

	MatrixBuffer* orthoBuffer;
	Matrix        orthoMatrix;

	ViewBuffer* UIViewBuffer;

	LightBuffer* lightBuffer;


};


