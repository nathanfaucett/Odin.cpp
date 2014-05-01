#ifndef ODIN_SPRITE_H
#define ODIN_SPRITE_H

namespace Odin {

	class Sprite : public Component {

		private:
			bool m_visible;
			float32 m_width, m_height, m_alpha, m_z;
			int32 m_x, m_y, m_w, m_h;

		protected:
			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Clear(void);

			inline void p_Sort(void);

		public:
			inline Sprite(void);
			inline Sprite(std::string name);
			inline Sprite(const Sprite& other);
			inline Sprite(const Sprite&& other);
			inline ~Sprite(void);

			inline virtual Sprite& Copy(const Sprite& other);
			inline virtual Sprite& Move(const Sprite&& other);
			
			inline void Update(void);
			
			inline Sprite& operator =(const Sprite& other);
			inline Sprite& operator =(const Sprite&& other);
	};
}

#endif