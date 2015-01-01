#ifndef SCENARIO_HPP
#define SCENARIO_HPP

#include<string>
using std::string;

#include<SFML/Graphics.hpp>

namespace esc
{ 
	class Scenario 
	{

		public:
		
			Scenario(const string &, sf::RenderWindow &);
			virtual ~Scenario();

			virtual void onStartScenario() = 0;
			virtual void onScenarioLoop();
			virtual void onEndScenario() = 0;

		private:

	};
}
#endif