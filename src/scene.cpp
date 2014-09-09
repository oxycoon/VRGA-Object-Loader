#include "scene.h"

#include "camera.h"
#include "model.h"

Scene::Scene()
{
    world_ = glm::mat4();
    projection_ = glm::perspective((float)M_PI_4, 1.0f, 0.1f, 100.0f);
}

void Scene::moveCameraUp()
{
    camera_->moveUp();
}

void Scene::moveCameraDown()
{
    camera_->moveDown();
}

void Scene::moveCameraLeft()
{
    camera_->moveLeft();
}

void Scene::moveCameraRight()
{
    camera_->moveRight();
}

void Scene::moveCameraZoomIn()
{
    camera_->zoomIn();
}

void Scene::moveCameraZoomOut()
{
    camera_->zoomOut();
}

void Scene::render()
{

    //world_ = glm::translate(world_, glm::vec3(0.f, 0.f, -5.0f));
    glm::mat4 projectionWorldMatrix = projection_ * world_;
    // Bind our modelmatrix variable to be a uniform called mvpmatrix
    // in our shaderprogram
    glUniformMatrix4fv(glGetUniformLocation(shader_.getProg(), "mvpmatrix"), 1,
                       GL_FALSE, glm::value_ptr(projectionWorldMatrix));

    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // Make our background black
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(std::vector<std::shared_ptr<Model> >::iterator it = sceneObjects_.begin();
        it != sceneObjects_.end(); it++)
        (*it)->render();
}

void Scene::update()
{
    camera_->update();
    world_ = camera_->getMatrix();





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

    // Initialize camera
    camera_.reset(new Camera());
    world_ = camera_->getMatrix();
    shader_.initShader("res/shaders/phong");
    shader_.enable();
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


