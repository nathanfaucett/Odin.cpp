#ifndef ODIN_SPRITE_CPP
#define ODIN_SPRITE_CPP

namespace Odin {

	inline Sprite::Sprite(void) : Component() {
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
	
	inline Sprite::Sprite(std::string Name) : Component(Name) {
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
	
	inline Sprite::Sprite(const Sprite& other) : Component() {
		Copy(other);
	}
	
	inline Sprite::Sprite(const Sprite&& other) : Component() {
		Move(std::move(other));
	}

	inline Sprite::~Sprite(void) {
		p_Clear();
	}
	
	inline Sprite& Sprite::Copy(const Sprite& other) {
		Component::Copy(static_cast<Component>(other));
		
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
	
	inline Sprite& Sprite::Move(const Sprite&& other) {
		Component::Move(std::move(static_cast<Component>(other)));
		
		m_z = std::move(other.m_z);
		m_alpha = std::move(other.m_alpha);
		m_visible = std::move(other.m_visible);

		m_width = std::move(other.m_width);
		m_height = std::move(other.m_height);

		m_x = std::move(other.m_x);
		m_y = std::move(other.m_y);
		m_w = std::move(other.m_w);
		m_h = std::move(other.m_h);
		
		return *this;
	}

	inline void Sprite::p_Clear(void) {
		Component::p_Clear();
	}

	inline void Sprite::p_Init(void) {

	}

	inline void Sprite::p_Start(void) {

	}

	inline void Sprite::p_Update(void) {

	}

	inline void Sprite::p_Sort(void) {
		p_order = m_z;
	}

	inline Sprite& Sprite::operator =(const Sprite& other) {
		return Copy(other);
	}
	
	inline Sprite& Sprite::operator =(const Sprite&& other) {
		return Move(std::move(other));
	}
}

#endif