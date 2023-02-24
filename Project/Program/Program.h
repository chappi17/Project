#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

private:
	double TimeSet = 0.0f;
};

