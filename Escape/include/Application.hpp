#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include<string>
using std::string;

#include<map>
using std::map;
using std::pair;

#include<memory>
using std::unique_ptr;

#include<SFML/Audio.hpp>
#include<SFML/System/Clock.hpp>

#include "Asset.hpp"
#include "ScenarioManager.hpp"
#include "Scenario.hpp"

namespace esc
{
	typedef Asset<sf::Texture> TextureAsset;
	typedef Asset<sf::SoundBuffer> SoundAsset;

	class Application 
	{
		public:

			explicit Application(const string &appName);
			virtual ~Application();

			virtual int run() final;

			virtual sf::Texture		* loadTextureFromFile(const string & path) = 0;
			virtual sf::SoundBuffer	* loadSoundFromFile(const string & path) = 0;

			virtual void onApplicationLoad() = 0;
			virtual void onApplicationDestroy() = 0;

			sf::RenderWindow * getWindow();
			ScenarioManager * getScenarioManager() const;
			void pause(bool);

			void setApplicationName(const string &appName);
			const string & getApplicationName() const;
			

		protected:
			
			virtual bool loadGameAssetDefinitions() = 0;

			TextureAsset * textures;
			SoundAsset * sounds;
			sf::Vector2i screenSize;

		private:

			int onApplicationLoop();

			sf::RenderWindow applicationWindow;
			unique_ptr<ScenarioManager> scenarioManager;

			Scenarios scenes;
			sf::Clock clock;

			bool isApplicationPaused;
			string applicationName;
	};
}

#endif