#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include<string>
using std::string;

#include <SFML/Graphics.hpp>

#include "Application.hpp"
#include "IUpdatableObject.hpp"

namespace esc
{ 
	class Scenario  : public IUpdatableObject
	{
		public:
		
			Scenario(const string &sName, Application &appInstance);
			virtual ~Scenario();
			
			bool setNewTransitionScene(const string & scenarioName, Scenario * newScenario);
			bool setNextScenario(const string & scenarioName);

			virtual bool onScenarioTransition(Scenario * fromScenario) = 0;
			virtual bool startScenario() = 0;
			virtual void update(float elapsed) = 0;
			virtual bool isDestroyable();

			const string & getName() const;
			Scenario * getNextScenario() const; 

		protected:

			virtual void onEndScenario() = 0;
			virtual bool loadGameAssets();

			Application * getApplicationInstance() const;
			sf::RenderWindow * getApplicationWindowInstance() const;

		private:
			
			static int scenarioID_generator;
			int scenarioID;
	
			Application * applicationInstance; 
			sf::RenderWindow * applicationWindowInstance;
			//AssetManager assetManager;
			
			Scenario * nextScenario;
			string scenarioName;
	};
}

#endif