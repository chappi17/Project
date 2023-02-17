#pragma once
class Bro_Player;
class Store_menu
{
public:
	Store_menu();
	~Store_menu();

	void Update();
	void Render();
	void PostRender();

	void SetEvent(CallBack callback) { _callback = callback; }

	void Unlock_rail();
	void Unlock_smg();

	static bool isActive_R;
	static bool isAcitve_S;

private:

	shared_ptr<Button> _button_G;
	shared_ptr<Button> _button_R;
	shared_ptr<Button> _button_SMG;	

	shared_ptr<Quad> _quad_G;
	shared_ptr<Quad> _quad_R;
	shared_ptr<Quad> _quad_SMG;

	shared_ptr<Bro_icon> _icon;

	shared_ptr<Bro_Player> _player;

	CallBack _callback;
};

