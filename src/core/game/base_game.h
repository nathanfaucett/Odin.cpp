#ifndef ODIN_BASE_GAME_H
#define ODIN_BASE_GAME_H

namespace Odin {

	class BaseGame {

		private:
			
		protected:
			std::string p_name;
			
			inline virtual void p_Init(void);
			inline virtual void p_Clear(void);

		public:
			inline BaseGame(void);
			inline BaseGame(std::string name);
			inline ~BaseGame(void);
			
			inline virtual void Update(void);
	};
}

#endif