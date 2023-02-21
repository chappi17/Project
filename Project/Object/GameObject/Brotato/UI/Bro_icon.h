#pragma once
class Bro_icon
{
public:
	Bro_icon();
	~Bro_icon();

	void Update();
	void Render();
	void PostRender();

	void SetEvent(CallBack callback) { _callback = callback; }

	shared_ptr<Quad> Getrailgun() { return _railgun_icon; }
	shared_ptr<Quad> Getsmg() { return _smg_icon; }
	shared_ptr<Quad> GetGun() { return _gun_icon; }

	void SetActive(bool isActive);
	bool IsActive() { return _isActive; }
private:
	bool _isActive = false;
	shared_ptr<Quad> _player_icon;

	shared_ptr<Quad> _gun_icon;
	shared_ptr<Quad> _railgun_icon;
	shared_ptr<Quad> _smg_icon;

	CallBack _callback;
};

