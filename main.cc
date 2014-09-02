#include <iostream>
#include <string>
#include <stddef.h>
#include <cmath>

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
#include "loader.h"

#define PROGRAM_NAME "MeshLoader"

// This is a handle to the shader program
GLuint shaderprogram;
// This stores the projection matrix
glm::mat4 projectionmatrix = glm::perspective((float)M_PI_4, 1.0f, 0.1f, 100.0f);
// handles for Vertex Array Object and One Vertex Buffer Object
GLuint vao, vbo[1];
// These are handles used to reference the shaders
GLuint vertexshader, fragmentshader;
Loader loader;

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

//struct Vertex
//{
//  GLfloat position[3];
//  GLfloat color[3];
//};


void drawscene(SDL_Window *window)
{
  glm::mat4 modelmatrix = glm::mat4();
  modelmatrix = glm::translate(modelmatrix, glm::vec3(0.f, 0.f, -5.0f));

  // multiply our modelmatrix and our projectionmatrix.
  // Results are stored in modelmatrix
  modelmatrix = projectionmatrix * modelmatrix;

  // Bind our modelmatrix variable to be a uniform called mvpmatrix
  // in our shaderprogram
  glUniformMatrix4fv(glGetUniformLocation(shaderprogram, "mvpmatrix"), 1,
                     GL_FALSE, glm::value_ptr(modelmatrix));

  // Make our background black
  glClearColor(0.0, 0.0, 0.0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Invoke glDrawArrays telling that our data consists of individual triangles
  glDrawArrays(GL_TRIANGLES, 0, 12);

  // Swap our buffers to make our changes visible
  SDL_GL_SwapWindow(window);
}

void initScene()
{
  // An array of 12 Vertices to make 4 coloured triangles
  // in the shape of a tetrahedron
  const struct Vertex v[4]  = {
    {{ 1.0f,  1.0f,  1.0f }, { 0.0f, 1.0f, 1.0f }},
    {{ -1.0f, -1.0f,  1.0f }, { 1.0f, 0.0f, 1.0f }},
    {{ -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 0.0f }},
    {{ 1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f }}
  };

  const struct Vertex tetrahedron[12] =
  {
    v[0], v[1], v[2],
    v[0], v[1], v[3],
    v[0], v[2], v[3],
    v[1], v[2], v[3]
  };

  std::vector<Vertex> model;
  std::vector<GLushort> elements;

  loader.load("res/models/garg.obj", model, elements);




  // These pointers will receive the contents of our shader source code files
  GLchar *vertexsource, *fragmentsource;

  // Allocate and assign a Vertex Array Object to our handle
  glGenVertexArrays(1, &vao);

  // Bind our Vertex Array Object as the current used object
  glBindVertexArray(vao);

  // Allocate and assign One Vertex Buffer Object to our handle
  glGenBuffers(1, vbo);

  // Bind our VBO as being the active buffer and storing vertex attributes
  // (coordinates + colors)
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

  // Copy the vertex data from tetrahedron to our buffer 12 * sizeof(GLfloat)
  // is the size of the tetrahedrom array, since it contains 12 Vertex values
//  glBufferData ( GL_ARRAY_BUFFER, 12 * sizeof ( struct Vertex ), tetrahedron,
//                 GL_STATIC_DRAW );
  glBufferData ( GL_ARRAY_BUFFER, model.size() * sizeof ( struct Vertex ), &model.front(),
                 GL_STATIC_DRAW );

  // Specify that our coordinate data is going into attribute index 0, and
  // contains three doubles per vertex
  glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE,
                         sizeof ( struct Vertex ),
                         (void *) offsetof (struct Vertex, position) );

  // Enable attribute index 0 as being used
  glEnableVertexAttribArray(0);

  glVertexAttribPointer ( ( GLuint ) 1, 3, GL_FLOAT, GL_FALSE, 
			  sizeof ( struct Vertex ), 
			  ( const GLvoid *) offsetof(struct Vertex, color)  );

  // Enable attribute index 1 as being used
  glEnableVertexAttribArray ( 1 );  

  // Read our shaders into the appropriate buffers
  vertexsource = filetobuf("res/shaders/simple.vert");
  fragmentsource = filetobuf("res/shaders/simple.frag");

  // Assign our handles a "name" to new shader objects
  vertexshader = glCreateShader(GL_VERTEX_SHADER);
  fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

  // Associate the source code buffers with each handle
  glShaderSource(vertexshader, 1, (const GLchar **)&vertexsource, 0);
  glShaderSource(fragmentshader, 1, (const GLchar **)&fragmentsource, 0);

  // Compile our shader objects
  glCompileShader(vertexshader);
  glCompileShader(fragmentshader);

  // Assign our program handle a "name"
  shaderprogram = glCreateProgram();

  // Attach our shaders to our program
  glAttachShader(shaderprogram, vertexshader);
  glAttachShader(shaderprogram, fragmentshader);

  // Bind attribute 0 to in_Position and attribute 1 (colors) to in_Color
  glBindAttribLocation(shaderprogram, 0, "in_Position");
  glBindAttribLocation(shaderprogram, 1, "in_Color");

  // Link our program, and set it as being actively used
  glLinkProgram(shaderprogram);
  glUseProgram(shaderprogram);

  free(vertexsource);
  free(fragmentsource);
}

void resizeWindow(SDL_Window *window, int w, int h)
{

}

void mainloop(SDL_Window *window)
{
  SDL_Event event;

  bool quit = false;
  while ( quit == false )
  {
    // event handling
    while ( SDL_PollEvent( &event ) )
    {
        switch ( event.type ) {
            case SDL_QUIT:
                quit = true;
                break;
//            case SDL_WINDOWEVENT_RESIZED:
//                SDL_Log("Window %d resized to %d,%d",
//                    event.window.windowID, event.window.data1,
//                    event.window.data2);
//                std::cout << "Window resized!" << std::endl;
//                break;
//            case SDL_WINDOWEVENT_MOVED:
//                std::cout << "Window moved!" << std::endl;
//                break;
      }
    }
    // logic

    // render
    drawscene(window);
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
