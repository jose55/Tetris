#include "ScenarioManager.hpp"

#include "Application.hpp"
#include "Scenario.hpp"

namespace esc
{
	ScenarioManager::ScenarioManager(Application * appInstance)
		:
		applicationInstance(appInstance)
	{
	
	}

	ScenarioManager::~ScenarioManager(){}

	void ScenarioManager::addScenario(const string &scenarioName, Scenario * scenario)
	{
		if (scenario == nullptr) return;
		scenarios[scenarioName] = ScenarioPtr(scenario);
	}

	void ScenarioManager::addScenario(const string &scenarioName, Scenario * scenario, Scenario * nextScenario)
	{
		if (scenario == nullptr || nextScenario == nullptr) return;

		scenario->setNextScenario(nextScenario->getName());
		scenarios[scenarioName] = ScenarioPtr(scenario);
	}

	bool ScenarioManager::runScene(const string &scenarioName)
	{
		if (scenarios.find(scenarioName) == scenarios.end())
			return false;

		if (currentScenario == nullptr)
		{
			currentScenario = scenarios[scenarioName].get();
			currentScenario->startScenario();
		}
		else 
		{
			Scenario * tmpPreviousScenario = currentScenario;
			currentScenario = scenarios[scenarioName].get();
			currentScenario->onScenarioTransition(tmpPreviousScenario);
			currentScenario->startScenario();
		}
	}

	void ScenarioManager::updateCurrentScene(float elapsed)
	{
		if (currentScenario == nullptr) return;

		currentScenario->update(elapsed);
	
		if (currentScenario->isDestroyable())
		{
			Scenario * tmpNextScenario = currentScenario->getNextScenario();
			auto iter = scenarios.find(currentScenario->getName());

			if (iter != scenarios.end())
			{
				tmpNextScenario->onScenarioTransition(currentScenario);
				currentScenario = tmpNextScenario;
				currentScenario->startScenario();
				scenarios.erase(iter);
			}
		}
	}

	Scenario * ScenarioManager::getCurrentScenario() const
	{
		return currentScenario;
	}

	Scenario * ScenarioManager::getScenario(const string &scenarioName) const
	{
		if (scenarios.find(scenarioName) == scenarios.end())
			return nullptr;

		return scenarios[scenarioName];
	}

	size_t ScenarioManager::getScenarioCount() const
	{
		return scenarios.size();
	}
}