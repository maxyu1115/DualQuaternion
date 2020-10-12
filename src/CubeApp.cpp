//
// Created by Max on 10/8/2020.
//

#include "CubeApp.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// note that this is a half angle rotation
const GLfloat rotationSpeed = 0.05;

CubeApp &CubeApp::getSingleton() {
    static CubeApp cubeApp;
    return cubeApp;
}

bool CubeApp::init() {

    // Initialize the library
    if ( !glfwInit( ) )
    {
        return false;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", nullptr, nullptr );

    glfwSetKeyCallback( window, keyCallback );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, 1 );


    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    if ( !window )
    {
        glfwTerminate( );
        return false;
    }

    // Make the window's context current
    glfwMakeContextCurrent( window );

    glViewport( 0.0f, 0.0f, screenWidth, screenHeight ); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode( GL_PROJECTION ); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity( ); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000 ); // essentially set coordinate system
    glMatrixMode( GL_MODELVIEW ); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity( ); // same as above comment

    initCube( SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -500, 200 );

    return true;
}

void CubeApp::run() {

    // Loop until the user closes the window
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );

        // Render OpenGL here

        glPushMatrix( );

        drawCube();

        glPopMatrix();


        // Swap front and back buffers
        glfwSwapBuffers( window );

        // Poll for and process events
        glfwPollEvents( );
    }

    glfwTerminate( );

}

void CubeApp::keyCallbackImpl( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    //std::cout << key << std::endl;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if ( action == GLFW_PRESS || action == GLFW_REPEAT )
    {
        switch ( key )
        {
            case GLFW_KEY_UP:
                rotateCube(Rx);
                break;
            case GLFW_KEY_DOWN:
                rotateCube(Rx_r);
                break;
            case GLFW_KEY_RIGHT:
                rotateCube(Ry_r);
                break;
            case GLFW_KEY_LEFT:
                rotateCube(Ry);
                break;
        }

    }
}

void CubeApp::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    getSingleton().keyCallbackImpl(window, key, scancode, action, mods);
}

void CubeApp::initCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength ) {
    GLfloat halfSideLength = edgeLength * 0.5f;
    GLfloat vertices[] =
            {
                    // front face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // back face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom left

                    // left face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // right face
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // top face
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // bottom left

                    // top face
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // top left
                    centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // top right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // bottom right
                    centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // bottom left
            };
    for (int i = 0; i < 24; i++) {
        dq_from_vertex(&CubeApp::dqVertices[8 * i], &vertices[3 * i]);
    }


    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;

    dq_t temp1, temp2;
    dq_t trX, trY, trZ, tr1, tr2;

    // build the two translation dq's
    dq_cr_tran_q(trX, X_AXIS, halfScreenWidth/2);
    dq_cr_tran_q(trY, Y_AXIS, halfScreenHeight/2);
    dq_cr_tran_q(trZ, Z_AXIS, -500/2);
    dq_mult(temp1, trX, trY);
    dq_mult(tr1, temp1, trZ);
    dq_mult(CubeApp::Rx_r, temp1, trZ);

    dq_cr_tran_q(trX, X_AXIS, -halfScreenWidth/2);
    dq_cr_tran_q(trY, Y_AXIS, -halfScreenHeight/2);
    dq_cr_tran_q(trZ, Z_AXIS, 500/2);
    dq_mult(temp1, trX, trY);
    dq_mult(tr2, temp1, trZ);
    dq_mult(CubeApp::Rx, temp1, trZ);

    // set the rotation with respect to cube center dq's
    dq_cr_rot_q(temp1, YZ_PLANE, rotationSpeed);
    dq_mult(temp2, tr1, temp1);
    dq_mult(CubeApp::Rx, temp2, tr2);

    dq_cr_rot_q(temp1, YZ_PLANE, -rotationSpeed);
    dq_mult(temp2, tr1, temp1);
    dq_mult(CubeApp::Rx_r, temp2, tr2);

    dq_cr_rot_q(temp1, ZX_PLANE, rotationSpeed);
    dq_mult(temp2, tr1, temp1);
    dq_mult(CubeApp::Ry, temp2, tr2);

    dq_cr_rot_q(temp1, ZX_PLANE, -rotationSpeed);
    dq_mult(temp2, tr1, temp1);
    dq_mult(CubeApp::Ry_r, temp2, tr2);
}


void CubeApp::drawCube()
{

    GLfloat vertexPoints[72];

    for (int i = 0; i < 24; i++) {
        dq_to_vertex(&vertexPoints[3 * i], &CubeApp::dqVertices[8 * i]);
    }

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer(3, GL_FLOAT, 0, vertexPoints );

    glDrawArrays( GL_QUADS, 0, 24 );

    glDisableClientState( GL_VERTEX_ARRAY );
}

void CubeApp::rotateCube(const dq_t R) {
    dq_t q;
    for (int i = 0; i < 24; i++) {
        for (int j = 0; j < 8; j++) {
            q[j] = CubeApp::dqVertices[8 * i + j];
        }
        dq_sandwhich_map(&CubeApp::dqVertices[8 * i], R, q);
    }
}