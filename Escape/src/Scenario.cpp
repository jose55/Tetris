#include "Scenario.hpp"

namespace esc
{
	Scenario::Scenario(const string &sName, Application &appInstance)
		: 
	 	  applicationInstance(&appInstance)
		, scenarioName(sName)
	{
	}

	Scenario::~Scenario()
	{
	}

	bool Scenario::setNewTransitionScene(const string &sname, Scenario * newScene)
	{
		if (newScene == this || sname.compare(scenarioName) == 0)
			return false;

		ScenarioManager * sManager = applicationInstance->getScenarioManager();
		sManager->addScenario(sname, newScene);
		nextScenario = sManager->getScenario(sname);
	}

	bool Scenario::setNextScenario(const string & scenarioName)
	{
		if (scenarioName.compare(scenarioName) == 0)
			return false;

		ScenarioManager * sManager = applicationInstance->getScenarioManager();
		nextScenario = sManager->getScenario(scenarioName);
	}

	bool Scenario::isDestroyable()
	{
		return false;
	}

	const string & Scenario::getName() const
	{
		return scenarioName;
	}

	Scenario * Scenario::getNextScenario() const
	{
		return nextScenario;
	}

	bool Scenario::loadGameAssets()
	{
		return true;
	}

	Application * Scenario::getApplicationInstance() const
	{
		return applicationInstance;
	}

	sf::RenderWindow * Scenario::getApplicationWindowInstance() const
	{
		return applicationWindowInstance;
	}
}