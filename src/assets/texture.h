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

            float32 m_anisotropy;

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
			
			inline virtual void SetGenerateMipmap(bool value);
			inline virtual bool GetGenerateMipmap(void);
			
			inline virtual void SetFlipY(bool value);
			inline virtual bool GetFlipY(void);
			
			inline virtual void SetPremultiplyAlpha(bool value);
			inline virtual bool GetPremultiplyAlpha(void);
			
			inline virtual void SetAnisotropy(float32 value);
			inline virtual float32 GetAnisotropy(void);
			
			inline virtual void SetFilter(TextureFilter value);
			inline virtual TextureFilter GetFilter(void);
			
			inline virtual void SetFormat(TextureFormat value);
			inline virtual TextureFormat GetFormat(void);
			
			inline virtual void SetWrap(TextureWrap value);
			inline virtual TextureWrap GetWrap(void);
			
			inline virtual void SetType(TextureType value);
			inline virtual TextureType GetType(void);
	};
}

#endif