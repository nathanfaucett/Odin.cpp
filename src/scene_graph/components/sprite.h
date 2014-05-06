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
			inline void p_Sort(void);

		public:
			Texture* texture;
			
			inline Sprite(void);
			inline Sprite(const Sprite&) = default;
			inline Sprite(Sprite&&) = default;
			inline ~Sprite(void);

			inline virtual Sprite* Clone(void);
			inline virtual Sprite& Copy(const Sprite& other);
			
			inline void Update(void);
			inline void Clear(void);
			
			inline Sprite& operator=(const Sprite&)& = default;
			inline Sprite& operator=(Sprite&&)& = default;
	};
}

#endif