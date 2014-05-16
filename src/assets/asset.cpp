#ifndef ODIN_ASSET_CPP
#define ODIN_ASSET_CPP

namespace Odin {
	
	inline Asset::Asset(std::string name, std::string src) : Object() {
		p_name = name;
		p_src = src;
		p_assets = NULL;
	}
	inline Asset::~Asset(void) {
		if (p_assets != NULL) {
			p_assets->Remove(this);
		}
	}
	
	inline void Asset::SetName(std::string name) {
		if (p_assets != NULL) {
			if (p_assets->Has(name)) {
				LogError("Asset::SetName(std::string name) can't change name Assets already has asset named "+ name);
			} else {
				p_assets->Remove(this);
				p_name = name;
				p_assets->Add(this);
			}
		} else {
			p_name = name;
		}
	}
	inline void Asset::Load(void) {}
}

#endif