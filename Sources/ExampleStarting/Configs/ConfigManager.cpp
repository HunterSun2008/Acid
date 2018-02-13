#include "ConfigManager.hpp"

#include <Helpers/FileSystem.hpp>
#include <Devices/Display.hpp>
#include <Devices/Audio.hpp>
#include <Events/Events.hpp>
#include <Events/EventTime.hpp>

namespace Demo
{
#define LINK_GET(t, f) [&]() -> t { return f; }
#define LINK_SET(t, f) [&](const t &v) -> void { f; }

	ConfigManager::ConfigManager()
	{
		FileSystem::CreateFolder("Configs");

		m_configAudio = new Config(new FileCsv(FileSystem::GetWorkingDirectory() + "/Configs/Audio.csv"));
		m_configAudio->Load();
	//	m_configAudio->Link<float>("MasterVolume", 1.0f, nullptr, nullptr);

		m_configGraphics = new Config(new FileCsv(FileSystem::GetWorkingDirectory() + "/Configs/Graphics.csv"));
		m_configGraphics->Load();
		m_configGraphics->Link<float>("FpsLimit", 0.0f, LINK_GET(float, Display::Get()->GetFpsLimit()), LINK_SET(float, Display::Get()->SetFpsLimit(v)));
		m_configGraphics->Link<bool>("Antialiasing", true, LINK_GET(bool, Display::Get()->IsAntialiasing()), LINK_SET(bool, Display::Get()->SetAntialiasing(v)));
		m_configGraphics->Link<bool>("Fullscreen", false, LINK_GET(bool, Display::Get()->IsFullscreen()), LINK_SET(bool, Display::Get()->SetFullscreen(v)));
		m_configGraphics->Link<int>("DisplayWidth", 1080, LINK_GET(int, Display::Get()->GetWidth()));
		m_configGraphics->Link<int>("DisplayHeight", 720, LINK_GET(int, Display::Get()->GetHeight()));

		Events::Get()->AddEvent(new EventTime(2.5f, false, [&]() -> void { Save(); }));
	}

	ConfigManager::~ConfigManager()
	{
		Save();

		delete m_configAudio;
		delete m_configGraphics;
	}

	void ConfigManager::Save()
	{
		printf("Saving config manager\n");
		m_configAudio->Save();
		m_configGraphics->Save();
	}
}