#ifndef ODIN_GAME_CONFIG_HPP
#define ODIN_GAME_CONFIG_HPP

namespace Odin {

	class GameConfig {
		public:
			uint32 fps;
			std::string host;
            uint32 port;
			
			inline GameConfig(void) {
				fps = 60;
				host = "127.0.0.1";
				port = 3000;
			}
	} GameConfig;
}

#endif