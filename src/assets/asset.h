#ifndef ODIN_ASSET_H
#define ODIN_ASSET_H

namespace Odin {
	
	class Asset {
		
		private:
			
		protected:
			std::string p_name;
			std::string p_src;

		public:
			inline Asset(std::string name, std::string src);
			inline ~Asset(void);
			
			inline virtual void Load(void);
	};
}

#endif