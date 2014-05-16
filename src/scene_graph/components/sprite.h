#ifndef ODIN_SPRITE_H
#define ODIN_SPRITE_H

namespace Odin {

	class Sprite : public Component {

		private:
			bool m_visible;
			float32 m_width, m_height, m_alpha;
			int32 m_x, m_y, m_w, m_h;
			
		protected:

		public:
			uint32 layer;
			int32 z;
			Texture* texture;
			
			inline Sprite(void);
			inline Sprite(const Sprite&) = default;
			inline Sprite(Sprite&&) = default;
			inline ~Sprite(void);

			inline virtual Sprite* Clone(void);
			inline virtual Sprite& Copy(const Sprite& other);
			
			inline void Update(void);
			inline void Clear(void);
			inline static float32 Sort(Sprite* a, Sprite* b);
			
			inline Sprite& operator=(const Sprite&)& = default;
			inline Sprite& operator=(Sprite&&)& = default;
	};
}

#endif