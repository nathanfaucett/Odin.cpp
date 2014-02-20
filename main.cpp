#include <iostream>
#include "odin.h"
using namespace Odin;


int main(void) {
	
    init();
	
	Time.update();
	
	Mat3 m;
	
	std::cout << m.ToString() << std::endl;
	
    return 0;
}