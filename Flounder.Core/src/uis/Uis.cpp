#include "uis.hpp"

namespace Flounder
{
	uis::uis() :
		IModule(),
		m_managerUis(nullptr),
		m_selector(new uiselector()),
		m_container(new containerscreen(nullptr, Vector2(0.5f, 0.5f), Vector2(1.0f, 1.0f), false)),
		m_objects(new std::vector<UiObject*>()),
		m_arial(new fonttype("res/fonts/arial.png", "res/fonts/arial.fnt")),
		m_berlinSans(new fonttype("res/fonts/berlinSans.png", "res/fonts/berlinSans.fnt")),
		m_cafeFrancoise(new fonttype("res/fonts/cafefrancoise.png", "res/fonts/cafefrancoise.fnt")),
		m_candara(new fonttype("res/fonts/candara.png", "res/fonts/candara.fnt")),
		m_segoe(new fonttype("res/fonts/segoe.png", "res/fonts/segoe.fnt"))
	{
	}

	uis::~uis()
	{
		delete m_managerUis;
		delete m_selector;
		delete m_container;
		delete m_objects;

		delete m_arial;
		delete m_berlinSans;
		delete m_cafeFrancoise;
		delete m_candara;
		delete m_segoe;
	}

	void uis::Update()
	{
		if (m_managerUis != nullptr)
		{
			m_selector->update(m_managerUis->IsGamePaused());
			m_managerUis->Update();
		}

		m_objects->clear();
		m_container->Update();
		m_container->GetAll(m_objects);
	}
}