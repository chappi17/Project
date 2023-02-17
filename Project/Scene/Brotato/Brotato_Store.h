#pragma once
class BrotatoScene;
class Brotato_Store : public Scene 
{
public:
	Brotato_Store();
	~Brotato_Store();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Save_Slot();
	void Load_Slot();

	void ChangeScene_Game();
	
	void SetEvent(CallBack callback) { _callback = callback;}

private:

	shared_ptr<Button> _button_Next_Wave;

	shared_ptr<BrotatoScene> _camera;

	shared_ptr<Store_menu> _menu;
	CallBack _callback;
};

