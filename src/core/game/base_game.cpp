#ifndef ODIN_BASE_GAME_CPP
#define ODIN_BASE_GAME_CPP

namespace Odin {

	inline BaseGame::BaseGame(void) {
		p_name = "Odin Game";
	}

	inline BaseGame::BaseGame(std::string name) {
		p_name = name;
	}

	inline BaseGame::~BaseGame(void) {
		p_Clear();
	}

	inline void BaseGame::p_Init(void) {
		
	}

	inline void BaseGame::p_Clear(void) {
		
	}

	inline void BaseGame::Update(void) {
		Time.Update();
	}
}

#endif