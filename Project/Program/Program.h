#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render();

	void Play();

private:
	double TimeSet = 0.0f;
};

