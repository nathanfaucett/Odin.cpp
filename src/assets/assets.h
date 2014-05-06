#ifndef ODIN_ASSETS_H
#define ODIN_ASSETS_H

namespace Odin {
	
	class Assets {
		
		private:
			uint32 m_assetCount;
			Array<Asset*> m_assets;
			std::unordered_map<std::string, Asset*> m_assetsHash;
			
		protected:

		public:
			inline Assets(void);
			inline ~Assets(void);
			
			inline void Clear(void);
			inline void Add(Asset* asset);
			inline void Remove(Asset* asset);
			template <typename Type> inline Type* Get(std::string name);
			inline bool Has(std::string name);
			
			inline void Load(void);
	};
}

#endif