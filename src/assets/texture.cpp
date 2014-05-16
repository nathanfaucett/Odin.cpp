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

		m_anisotropy = 0.0f;

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

	inline void Texture::SetGenerateMipmap(bool value) {
		m_generateMipmap = value;
		m_needsUpdate = true;
	}
	inline bool Texture::GetGenerateMipmap(void) {
		return m_generateMipmap;
	}
	
	inline void Texture::SetFlipY(bool value) {
		m_flipY = value;
		m_needsUpdate = true;
	}
	inline bool Texture::GetFlipY(void) {
		return m_flipY;
	}
	
	inline void Texture::SetPremultiplyAlpha(bool value) {
		m_premultiplyAlpha = value;
		m_needsUpdate = true;
	}
	inline bool Texture::GetPremultiplyAlpha(void) {
		return m_premultiplyAlpha;
	}
	
	inline void Texture::SetAnisotropy(float32 value) {
		m_anisotropy = value;
		m_needsUpdate = true;
	}
	inline float32 Texture::GetAnisotropy(void) {
		return m_anisotropy;
	}
	
	inline void Texture::SetFilter(TextureFilter value) {
		m_filter = value;
		m_needsUpdate = true;
	}
	inline TextureFilter Texture::GetFilter(void) {
		return m_filter;
	}
	
	inline void Texture::SetFormat(TextureFormat value) {
		m_format = value;
		m_needsUpdate = true;
	}
	inline TextureFormat Texture::GetFormat(void) {
		return m_format;
	}
	
	inline void Texture::SetWrap(TextureWrap value) {
		m_wrap = value;
		m_needsUpdate = true;
	}
	inline TextureWrap Texture::GetWrap(void) {
		return m_wrap;
	}
	
	inline void Texture::SetType(TextureType value) {
		m_type = value;
		m_needsUpdate = true;
	}
	inline TextureType Texture::GetType(void) {
		return m_type;
	}
}

#endif