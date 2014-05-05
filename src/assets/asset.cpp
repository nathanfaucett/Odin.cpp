#ifndef ODIN_ASSET_CPP
#define ODIN_ASSET_CPP

namespace Odin {
	
	inline Asset::Asset(std::string name, std::string src) {
		p_name = name;
		p_src = src;
	}
	inline Asset::~Asset(void) {}
	
	inline void Asset::Load(void) {}
}

#endif