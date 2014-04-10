#ifndef ODIN_BASE_GAME_H
#define ODIN_BASE_GAME_H

namespace Odin {

	class BaseGame : public Object {

		private:

		protected:
			inline virtual void p_Init(void);
			inline virtual void p_Update(void);
			inline virtual void p_Clear(void);

		public:
			inline BaseGame(void);
			inline BaseGame(std::string Name);
			inline BaseGame(const BaseGame& other);
			inline BaseGame(const BaseGame&& other);
			inline ~BaseGame(void);

			inline virtual BaseGame& Copy(const BaseGame& other);
			inline virtual BaseGame& Move(const BaseGame&& other);
			
			inline BaseGame& operator =(const BaseGame& other);
			inline BaseGame& operator =(const BaseGame&& other);
	};
}

#endif