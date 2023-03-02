#pragma once
class HPBar
{
public:
	HPBar();
	~HPBar();

	void Update();
	void Render();

	shared_ptr<Transform> GetTransform() { return _quad->GetTransform(); }

	float& ratio() { return _sliderBuffer->_data.ratio; }

private:
	shared_ptr<Quad> _backGround;
	shared_ptr<Quad> _quad;
	shared_ptr<SliderBuffer> _sliderBuffer;
};

