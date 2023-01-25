#pragma once

class MyXML
{
public:
	MyXML(wstring path) : _path(path) { ReadXML(); }
	~MyXML();

	void ReadXML();

	Vector2 GetAverage() { return _average; }
	vector<Action::Clip> GetClips() { return _clips; }

private:
	wstring _path;
	vector<Action::Clip> _clips;

	Vector2 _average;
};

