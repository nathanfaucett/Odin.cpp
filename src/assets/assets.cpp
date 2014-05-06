#ifndef ODIN_ASSETS_CPP
#define ODIN_ASSETS_CPP

namespace Odin {
	
	inline Assets::Assets(void) {
		m_assetCount = 0;
	}
	inline Assets::~Assets(void) {
		Clear();
	}
	
	inline void Assets::Clear(void) {
		uint32 i, il;
		
		for (i = 0, il = m_assets.Length(); i < il; i++) {
			Asset* asset = m_assets[i];
			Remove(asset);
			delete asset;
		}
	}
	inline void Assets::Add(Asset* asset) {
		if (asset == NULL) {
			return;
		}

		bool has = m_assetsHash.count(asset->p_name) != 0;

		if (!has) {
			asset->p_assets = this;
			m_assets.Push(asset);
			m_assetCount++;
			
			m_assetsHash[asset->p_name] = asset;
		} else {
			LogError("Assets::Add(Asset* asset) asset already member of Assets");
		}
	}
	inline void Assets::Remove(Asset* asset) {
		if (asset == NULL) {
			return;
		}

		bool has = m_assetsHash.count(asset->p_name) != 0;

		if (has) {
			asset->p_assets = NULL;
			m_assets.Splice(m_assets.IndexOf(asset), 1);
			m_assetCount--;
			
			m_assetsHash[asset->p_name] = NULL;
		} else {
			LogError("Assets::Add(Asset* asset) asset already member of Assets");
		}
	}
	template <typename Type> inline Type* Assets::Get(std::string name) {
		
		if (m_assetsHash.count(name) != 0) {
			return reinterpret_cast<Type*>(m_assetsHash[name]);
		}

		return NULL;
	}
	inline bool Assets::Has(std::string name) {

		return m_assetsHash.count(name) != 0;
	}
	
	inline void Assets::Load(void) {
		uint32 i, il;
		
		for (i = 0, il = m_assets.Length(); i < il; i++) m_assets[i]->Load();
	}
	
	Assets Assets;
}

#endif