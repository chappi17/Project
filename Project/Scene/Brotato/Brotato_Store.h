#pragma once
class Brotato_Store : public Scene 
{
public:
	Brotato_Store();
	~Brotato_Store();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save();
	void Load();

private:
	shared_ptr<Button> _button;

};

