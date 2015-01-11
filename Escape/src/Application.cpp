#include "Application.hpp"

namespace esc
{

	Application::Application(const string &appName)
		:
		  textures(nullptr)
		, sounds(nullptr)
		, screenSize(sf::Vector2i(800, 600))
		, isApplicationPaused(false)
		, applicationName(appName)
	{
		
	}
	
	Application::~Application()
	{
		//
	}

	int Application::run()
	{
		/*
			Steps:
				*step 1:	onApplicationLoad(); 
				*step 2:	if (!loadGameAsset())
							{
								onApplicationDestroy();
								return 1;
							}

				*step 3:	onApplicationLoop();
				*step 4:	onApplicationDestroy();
		*/
		scenarioManager.reset(new ScenarioManager(this));
		onApplicationLoad();
		
		if (!loadGameAssetDefinitions())
		{
			onApplicationDestroy();
			return 1;
		}
		
		return onApplicationLoop();
	}

	sf::RenderWindow * Application::getWindow()
	{
		return &applicationWindow;
	}

	ScenarioManager * Application::getScenarioManager() const
	{
		return scenarioManager.get();
	}

	const string & Application::getApplicationName() const
	{
		return applicationName;
	}

	int Application::onApplicationLoop()
	{
		applicationWindow.create(sf::VideoMode(screenSize.x, screenSize.y, 32), applicationName);
		applicationWindow.setFramerateLimit(60);

		if (scenarioManager->getScenarioCount())
			return 1;

		while (applicationWindow.isOpen())
		{
			if (!isApplicationPaused)
			{
				float elapsedTime = clock.restart().asSeconds();
				scenarioManager->updateCurrentScene(elapsedTime);
			}
		}

		onApplicationDestroy();
		return 0;
	}

}