#ifndef SCENARIOMANAGER_HPP
#define SCENARIOMANAGER_HPP

#include<string>
using std::string;

#include<memory>
using std::unique_ptr;

#include<map>
using std::map;

namespace esc
{
	class Application;
	class Scenario;

	typedef unique_ptr<Scenario> ScenarioPtr;
	typedef map<string, unique_ptr<Scenario>> Scenarios;

	class ScenarioManager
	{
		public:

			explicit ScenarioManager(Application * appInstance);
			virtual ~ScenarioManager();

			void addScenario(const string &sceneName, Scenario * scenario);
			void addScenario(const string &sceneName, Scenario * scenario, Scenario * nextScenario);
			bool runScene(const string &sceneName);
			void updateCurrentScene(float elapsed);

			Scenario * getCurrentScenario() const;
			Scenario * getScenario(const string &scenarioName) const;

			size_t getScenarioCount() const;

		private:
			
			Application * applicationInstance;
			Scenario * currentScenario;
			Scenarios scenarios;
	};
}

#endif