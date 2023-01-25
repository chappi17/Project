#include "framework.h"
#include "MyXML.h"

MyXML::~MyXML()
{
}

void MyXML::ReadXML()
{
	// MyXML("Effect/JumpDustA.png")
	// ÀüÃ¼ : Resource/Texture/
	wstring srvPath = _path; // explosion.png
	shared_ptr<SRV> srv = SRVManager::GetInstance()->AddSRV(srvPath);

	wstring xmlWPath = L"Resource/Texture/" + _path.substr(0, _path.find_last_of('.')) + L".xml";
	string xmlPath = string(xmlWPath.begin(), xmlWPath.end());

	shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();
	document->LoadFile(xmlPath.c_str());
	assert(document != nullptr);

	tinyxml2::XMLElement* textureAtlas = document->FirstChildElement();
	tinyxml2::XMLElement* row = textureAtlas->FirstChildElement();

	_average.x = 0;
	_average.y = 0;
	int count = 0;

	while (true)
	{
		if (row == nullptr)
			break;
		int x = row->FindAttribute("x")->IntValue();
		int y = row->FindAttribute("y")->IntValue();
		int w = row->FindAttribute("w")->IntValue();
		_average.x += w;
		int h = row->FindAttribute("h")->IntValue();
		_average.y += h;

		count++;

		Action::Clip clip = Action::Clip(x, y, w, h, srv);
		_clips.push_back(clip);

		row = row->NextSiblingElement();
	}

	shared_ptr<Sprite> sprite;
	_average.x /= count * 1.5f;
	_average.y /= count * 1.5f;
}
