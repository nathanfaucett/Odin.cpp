#ifndef ODIN_BASE_GAME_CPP
#define ODIN_BASE_GAME_CPP

namespace Odin {

	inline void BaseGame::p_Init(void) {

	}

	inline void BaseGame::p_Update(void) {
		Time.Update();
	}

	inline void BaseGame::p_Clear(void) {

	}

	inline BaseGame::BaseGame(void) : Object("Odin") {
		p_Init();
	}

	inline BaseGame::BaseGame(std::string Name) : Object(Name) {
		p_Init();
	}

	inline BaseGame::BaseGame(const BaseGame& other) : Object() {
		Copy(other);
	}
	
	inline BaseGame::BaseGame(const BaseGame&& other) : Object() {
		Move(std::move(other));
	}

	inline BaseGame::~BaseGame(void) {
		p_Clear();
	}

	inline BaseGame& BaseGame::Copy(const BaseGame& other) {
		Object::Copy(static_cast<Object>(other));
		
		return *this;
	}

	inline BaseGame& BaseGame::Move(const BaseGame&& other) {
		Object::Move(std::move(static_cast<Object>(other)));
		
		return *this;
	}

	inline BaseGame& BaseGame::operator =(const BaseGame& other) {
		return Copy(other);
	}
	
	inline BaseGame& BaseGame::operator =(const BaseGame&& other) {
		return Move(std::move(other));
	}
}

#endif