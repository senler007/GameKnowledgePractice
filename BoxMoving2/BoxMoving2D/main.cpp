#include "GameLib/Framework.h"
using namespace GameLib;

#include "State.h"
#include "File.h"

void mainloop();

State* gstate = 0;

namespace GameLib {
	void Framework::update(){
		mainloop();
	}
}

void mainloop() {


	if (!gState) {
		File
	}
}