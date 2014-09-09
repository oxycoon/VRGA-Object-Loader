#include <iostream>
#include <string>
#include <stddef.h>
#include <cmath>
#include <memory>

// Ensure we are using opengl's core profile only
#define GL3_PROTOTYPES 1
// Make sure we have glext
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glext.h>

#include "SDL.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "util.h"
#include "model.h"
#include "shader.h"
#include "scene.h"
#include "Input.h"

#define PROGRAM_NAME "MeshLoader"

// This is a handle to the shader program
GLuint shaderprogram;
// This stores the projection matrix
//glm::mat4 projectionmatrix = glm::perspective((float)M_PI_4, 1.0f, 0.1f, 100.0f);
// These are handles used to reference the shaders
GLuint vertexshader, fragmentshader;

bool keyPressed[80];
bool tapKey;
int mousePosX, mousePosY;
float moveX, moveY;

bool quit;

Scene scene;

void setupwindow(SDL_Window  *&window, SDL_GLContext &context) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize SDL's Video subsystem
    sdldie("Unable to initialize SDL"); // Or die on error

  // Request an opengl 3.2 context.
  // SDL doesn't have the ability to choose which profile
  // but it should default to the core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

  // Turn on double buffering with a 24bit Z buffer.
  //* You may need to change this to 16 or 32 for your system
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Create our window centered at 512x512 resolution
  window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 512, 512,
                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window == NULL) // Die if creation failed
    sdldie("Unable to create window");

  // Create our opengl context and attach it to our window
  context = SDL_GL_CreateContext(window);


}

void drawscene(SDL_Window *window)
{
  scene.render();

  // Swap our buffers to make our changes visible
  SDL_GL_SwapWindow(window);
}

void initScene()
{
    glEnable(GL_DEPTH_TEST);

    scene.init();
    scene.addModelToScene("res/models/garg.obj");
}

void resizeWindow(int w, int h)
{
    std::cout << "Resizing window to " << w << "x" << h << std::endl;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, w, 0, h, -1, 1);
    scene.updateProjection(glm::perspective((float)M_PI_4, (float)w/h, 0.1f, 1024.0f));
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//TODO optimalize
void keyDown(SDL_Event event)
{
    std::cout << "Keydown event detected!" << std::endl;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(currentKeyStates [SDL_SCANCODE_Q] && !keyPressed[KEY_ID_Q]) keyPressed[KEY_ID_Q] = true;
    if(currentKeyStates [SDL_SCANCODE_W] && !keyPressed[KEY_ID_W]) keyPressed[KEY_ID_W] = true;
    if(currentKeyStates [SDL_SCANCODE_D] && !keyPressed[KEY_ID_D]) keyPressed[KEY_ID_D] = true;
    if(currentKeyStates [SDL_SCANCODE_S] && !keyPressed[KEY_ID_S]) keyPressed[KEY_ID_S] = true;
    if(currentKeyStates [SDL_SCANCODE_A] && !keyPressed[KEY_ID_A]) keyPressed[KEY_ID_A] = true;
}

//TODO optimalize
void keyUp(SDL_Event event)
{
    std::cout << "Keyup event detected!" << std::endl;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if(!currentKeyStates [SDL_SCANCODE_Q] && keyPressed[KEY_ID_Q]) keyPressed[KEY_ID_Q] = false;
    if(!currentKeyStates [SDL_SCANCODE_W] && keyPressed[KEY_ID_W]) keyPressed[KEY_ID_W] = false;
    if(!currentKeyStates [SDL_SCANCODE_D] && keyPressed[KEY_ID_D]) keyPressed[KEY_ID_D] = false;
    if(!currentKeyStates [SDL_SCANCODE_S] && keyPressed[KEY_ID_S]) keyPressed[KEY_ID_S] = false;
    if(!currentKeyStates [SDL_SCANCODE_A] && keyPressed[KEY_ID_A]) keyPressed[KEY_ID_A] = false;
}

void handleKeyPresses()
{
    if(keyPressed[KEY_ID_Q]==true)      quit = true;
    if(keyPressed[KEY_ID_W]==true)      scene.moveCameraUp();
    if(keyPressed[KEY_ID_A]==true)      scene.moveCameraLeft();
    if(keyPressed[KEY_ID_S]==true)      scene.moveCameraDown();
    if(keyPressed[KEY_ID_D]==true)      scene.moveCameraRight();
}

void mainloop(SDL_Window *window)
{
    SDL_Event event;

    quit = false;
    while ( quit == false )
    {
    // event handling
        while ( SDL_PollEvent( &event ) )
        {
            switch ( event.type )
            {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            if(event.type == SDL_WINDOWEVENT)
            {
                switch(event.window.event)
                {
                    case SDL_WINDOWEVENT_RESIZED:
                        resizeWindow(event.window.data1, event.window.data2);
                        break;
                }
            }
            if(event.type == SDL_KEYDOWN)
            {
                keyDown(event);
            }
            if(event.type == SDL_KEYUP)
            {
                keyUp(event);
            }
            if(event.type == SDL_MOUSEWHEEL)
            {
                if(event.wheel.y > 0)
                    scene.moveCameraZoomIn();
                if(event.wheel.y < 0)
                    scene.moveCameraZoomOut();
            }
        }
    // logic
        scene.update();
        // render
        drawscene(window);

        handleKeyPresses();



        SDL_Delay(33);
    }
}

void destroyScene()
{
  glUseProgram(0);
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDetachShader(shaderprogram, vertexshader);
  glDetachShader(shaderprogram, fragmentshader);
  glDeleteProgram(shaderprogram);
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);
}

void destroywindow(SDL_Window *window, SDL_GLContext context)
{
  destroyScene();
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// Our program's entry point
int main(int argc, char *argv[]) {
  SDL_Window *mainwindow; // Our window handle
  SDL_GLContext maincontext; // Our opengl context handle

  // Create our window, opengl context, etc...
  setupwindow(mainwindow, maincontext);

  initScene();

  // Call our function that performs opengl operations
  mainloop(mainwindow);

  // Destroy scene, delete our opengl context, destroy our window, 
  // and shutdown SDL
  destroywindow(mainwindow, maincontext);

  return 0;
}
