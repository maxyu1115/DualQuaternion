#include "CubeApp.h"

int main( void ) {
    if (CubeApp::getSingleton().init()) {
        CubeApp::getSingleton().run();
    }
    return 0;
}