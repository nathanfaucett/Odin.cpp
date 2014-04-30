#include "src/odin.cpp"
using namespace Odin;


int main (int argc, char* argv[]) {
	std::cout << "START" << std::endl;
	std::cout.precision(16);

	Init();
	
	Quatf q;
	Mat43f m;
	m.Rotate(Mathf.PI * 0.5f, Mathf.PI * 0.5f, Mathf.PI * 0.5f);
	
	q *= m;
	std::cout << m.ToString() << std::endl;
	std::cout << q.ToString() << std::endl;
	
	q.Zero().RotateZ(Mathf.PI * 0.5f);
	std::cout << m.ToString() << std::endl;
	std::cout << q.ToString() << std::endl;
	
	
	std::cout << "END" << std::endl;
	return 0;
}