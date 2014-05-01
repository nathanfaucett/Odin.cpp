#include "src/odin.cpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();
	
	Window window("Odin Window");
	window.SetOpenGL();
	window.SetResizable();
	window.Create(64, 64, 960, 640);
	
	SDL_Event event;
	bool play = true;
	while(play) {
		Time.Update();
		while(SDL_PollEvent(&event)) {
			window.Update(&event);
			
			switch(event.type) {
				case SDL_QUIT:
					play = false;
					break;
			}
		}
	}
	std::cout << window.GetX() << std::endl;
	std::cout << window.GetY() << std::endl;
	std::cout << window.GetWidth() << std::endl;
	std::cout << window.GetHeight() << std::endl;

	std::cout << "END" << std::endl;
	return 0;
}