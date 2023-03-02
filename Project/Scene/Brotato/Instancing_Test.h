#pragma once
class Instancing_Test :public Scene
{
public:

	Instancing_Test();
	~Instancing_Test();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

private:

	shared_ptr<HPBar> _bar;

};