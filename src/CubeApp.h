//
// Created by Max on 10/8/2020.
//

#ifndef DUALQUATERNION_CUBEAPP_H
#define DUALQUATERNION_CUBEAPP_H

#include <GLFW/glfw3.h>
#include "DualQuaternionGeometry.h"


class CubeApp {
public:
    static CubeApp& getSingleton();
    static void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
    void keyCallbackImpl( GLFWwindow *window, int key, int scancode, int action, int mods );

    bool init();
    void run();

private:
    CubeApp() = default;
    CubeApp(CubeApp const&);
    void initCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength );
    void drawCube();
    void rotateCube(const dq_t R);

private:
    GLFWwindow *window;
    float dqVertices[192]; // 24 * 8
    dq_t Rx, Ry, Rx_r, Ry_r;

};


#endif //DUALQUATERNION_CUBEAPP_H
