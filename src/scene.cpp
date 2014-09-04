#include "scene.h"

#include "model.h"

Scene::Scene()
{
    world_ = glm::mat4();
}

void Scene::render()
{

    for(std::vector<std::shared_ptr<Model> >::iterator it = sceneObjects_.begin();
        it != sceneObjects_.end(); it++)
        (*it)->render();
}

void Scene::update()
{

    //Adds new scene objects to the scene.
    for(std::vector<std::shared_ptr<Model> >::iterator it = newChildren_.begin();
        it != newChildren_.end(); )
    {
        sceneObjects_.push_back((*it));
        it = newChildren_.erase(it);
    }
}

void Scene::init()
{

    // Allocate and assign a Vertex Array Object to our handle
    glGenVertexArrays(1, &vao_);

    // Bind our Vertex Array Object as the current used object
    glBindVertexArray(vao_);

//    // Allocate and assign One Vertex Buffer Object to our handle
//    glGenBuffers(1, vbo_);

//    // Bind our VBO as being the active buffer and storing vertex attributes
//    // (coordinates + colors)
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_[0]);

//    // Specify that our coordinate data is going into attribute index 0, and
//    // contains three doubles per vertex
//    glVertexAttribPointer( (GLuint)0, 3, GL_FLOAT, GL_FALSE,
//                           sizeof ( struct Vertex ),
//                           (void *) offsetof (struct Vertex, position) );

//    // Enable attribute index 0 as being used
//    glEnableVertexAttribArray(0);

//    glVertexAttribPointer ( ( GLuint ) 1, 3, GL_FLOAT, GL_FALSE,
//                sizeof ( struct Vertex ),
//                ( const GLvoid *) offsetof(struct Vertex, color)  );

//    // Enable attribute index 1 as being used
//    glEnableVertexAttribArray ( 1 );

//    glVertexAttribPointer ( ( GLuint ) 2, 3, GL_FLOAT, GL_FALSE,
//                sizeof ( struct Vertex ),
//                ( const GLvoid *) offsetof(struct Vertex, normal)  );

//    // Enable attribute index 2 as being used
//    glEnableVertexAttribArray ( 2 );
}

void Scene::addModelToScene(char *path)
{
    std::shared_ptr<Model> mod;
    mod.reset(new Model(path));
    mod->init();
    addSceneObject(mod);
}

/**
 * @brief Scene::addSceneObject
 * @param newChild
 *
 *  Adds a new object to the list of objects to be added to the scene.
 *  To avoid conflicts gets put into a list of objects to be added during
 *  update.
 */
void Scene::addSceneObject(std::shared_ptr<Model> newChild)
{
    newChildren_.push_back(newChild);
}

/**
 * @brief Scene::removeSceneObject
 * @param child
 *
 *  Removes object from scene.
 */
void Scene::removeSceneObject(const std::shared_ptr<Model> child)
{
    for(std::vector<std::shared_ptr<Model> >::iterator it = sceneObjects_.begin();
        it != sceneObjects_.end(); it++)
    if(*it == child)
    {
        sceneObjects_.erase(it);
        break;
    }
}

void Scene::toggleSceneObject(const std::shared_ptr<Model> child)
{
    for(std::vector<std::shared_ptr<Model> >::iterator it = sceneObjects_.begin();
        it != sceneObjects_.end(); it++)
    if(*it == child)
    {
        break;
    }
}
