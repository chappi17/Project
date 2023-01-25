#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Update() abstract;
	virtual void PreRender() {};
	virtual void Render() abstract;
	virtual void PostRender() {};

	virtual void PrevScene() {}
	virtual void NextScene() {}

	virtual void Init() {}

protected:
};

