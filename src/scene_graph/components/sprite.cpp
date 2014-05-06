#ifndef ODIN_SPRITE_CPP
#define ODIN_SPRITE_CPP

namespace Odin {

	inline Sprite::Sprite(void) : Component() {
		texture = NULL;
		
		m_z = 0.0f;
		m_alpha = 1.0f;
		m_visible = true;

		m_width = 1.0f;
		m_height = 1.0f;

		m_x = 0;
		m_y = 0;
		m_w = 1;
		m_h = 1;
	}

	inline Sprite::~Sprite(void) {
		Clear();
	}
	
	inline Sprite* Sprite::Clone(void) {
		return &((new Sprite())->Copy(*this));
	}
	
	inline Sprite& Sprite::Copy(const Sprite& other) {
		
		texture = other.texture;
		m_z = other.m_z;
		m_alpha = other.m_alpha;
		m_visible = other.m_visible;

		m_width = other.m_width;
		m_height = other.m_height;

		m_x = other.m_x;
		m_y = other.m_y;
		m_w = other.m_w;
		m_h = other.m_h;
		
		return *this;
	}

	inline void Sprite::p_Init(void) {
		Component::p_Init();
	}

	inline void Sprite::p_Start(void) {
		Component::p_Start();
	}

	inline void Sprite::p_Sort(void) {
		p_order = m_z;
	}

	inline void Sprite::Update(void) {

	}

	inline void Sprite::Clear(void) {
		texture = NULL;
		m_z = 0.0f;
		m_alpha = 1.0f;
		m_visible = true;

		m_width = 1.0f;
		m_height = 1.0f;

		m_x = 0;
		m_y = 0;
		m_w = 1;
		m_h = 1;
	}
}

#endif