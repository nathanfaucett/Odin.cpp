#ifndef ODIN_ASSET_H
#define ODIN_ASSET_H

namespace Odin {
	
	class Assets;
	
	class Asset : public Object {
		
		private:
			friend class Assets;
			
		protected:
			std::string p_name;
			std::string p_src;
			Assets* p_assets;

		public:
			inline Asset(std::string name, std::string src);
			inline virtual ~Asset(void);
			
			inline void SetName(std::string name);
			inline virtual void Load(void);
	};
}

#endif