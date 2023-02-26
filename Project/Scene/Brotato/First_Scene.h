#pragma once
class First_Scene :public  Scene
{
public:
	First_Scene();
	~First_Scene();

	void SetEvent(CallBack callback) { _callback = callback; }

	void ChangeScene_Stage0();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Quad> _quad;
	shared_ptr<Button> _button_Start;
	shared_ptr<Button> _button_Exit;

	CallBack _callback;
};

