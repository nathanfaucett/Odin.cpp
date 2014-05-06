#ifndef ODIN_TEXTURE_CPP
#define ODIN_TEXTURE_CPP

namespace Odin {
	
	inline Texture::Texture(std::string name, std::string src) : Asset(name, src) {
		m_image = NULL;
		m_needsUpdate = true;
		
		m_width = 0;
		m_height = 0;
		m_invWidth = 0.0f;
		m_invHeight = 0.0f;

		m_generateMipmap = true;
		m_flipY = true;
		m_premultiplyAlpha = false;

		m_anisotropy = 0;

		m_filter = TextureFilter::Linear;
		m_format = TextureFormat::RGBA;
		m_wrap = TextureWrap::Clamp;
		m_type = TextureType::UnsignedByte;
	}
	inline Texture::~Texture(void) {
		if (m_image != NULL) SDL_FreeSurface(m_image);
	}
	
	inline void Texture::Load(void) {
		m_image = IMG_Load(p_src.c_str());
		
		if(m_image == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", p_src.c_str(), IMG_GetError());
		} else {
			m_width = m_image->w;
			m_height = m_image->h;
			m_invWidth = 1.0f / m_width;
			m_invHeight = 1.0f / m_width;
		}
	}
}

#endif