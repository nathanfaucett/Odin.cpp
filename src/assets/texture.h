#ifndef ODIN_TEXTURE_H
#define ODIN_TEXTURE_H

namespace Odin {
	
	class Texture : public Asset {
		
		private:
			friend class OpenGLRenderer;
			SDL_Surface* m_image;
			uint32 m_textureID;
			
			int32 m_width;
            int32 m_height;
            float32 m_invWidth;
            float32 m_invHeight;

            bool m_generateMipmap;
            bool m_flipY;
            bool m_premultiplyAlpha;

            int32 m_anisotropy;

            TextureFilter m_filter;
            TextureFormat m_format;
            TextureWrap m_wrap;
            TextureType m_type;
			
			bool m_needsUpdate;
		protected:

		public:
			inline Texture(std::string name, std::string src);
			inline virtual ~Texture(void);
			
			inline virtual void Load(void);
	};
}

#endif