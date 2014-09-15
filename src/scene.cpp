#include "scene.h"

#include "camera.h"
#include "model.h"

#include "lightsettings.h"

Scene::Scene()
{
    world_ = glm::mat4();
    projection_ = glm::perspective((float)M_PI_4, 1.0f, 0.1f, 100.0f);
}

glm::mat4 Scene::getWorld()
{
    return world_;
}

std::shared_ptr<Camera> Scene::getCamera()
{
    return camera_;
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

void Scene::moveCameraRotate(glm::vec3 eulerAngles)
{
    camera_->rotateCamera(eulerAngles);
}

void Scene::shaderCycle()
{
    shader_manager_.cycleShader();
}

void Scene::modelCycle()
{
    if(scene_objects_.size() > 0)
    {
        toggleSceneObject(scene_objects_[modelIndex_]);

        modelIndex_++;
        if(modelIndex_ >= scene_objects_.size())
            modelIndex_ = 0;

        toggleSceneObject(scene_objects_[modelIndex_]);
    }
}

void Scene::render()
{
    //glPushMatrix();
    //world_ = glm::translate(world_, glm::vec3(0.f, 0.f, -5.0f));
    glm::mat4 mvp = projection_ * camera_->getViewMatrix() * world_;
    // Bind our modelmatrix variable to be a uniform called mvpmatrix
    // in our shaderprogram
    //glMultMatrixf(glm::value_ptr(mvp));

    glUniformMatrix4fv(glGetUniformLocation(shader_manager_.getActiveProg(), "mvpmatrix"), 1,
                       GL_FALSE, glm::value_ptr(mvp));

    glUniformMatrix4fv(glGetUniformLocation(shader_manager_.getActiveProg(), "vmatrix"), 1,
                       GL_FALSE, glm::value_ptr(camera_->getViewMatrix()));

    glUniformMatrix4fv(glGetUniformLocation(shader_manager_.getActiveProg(), "mmatrix"), 1,
                       GL_FALSE, glm::value_ptr(world_));

    //uniform for the light
    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.position"), 1,
               glm::value_ptr(glm::vec3(kLightPosition)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.ambient"), 1,
               glm::value_ptr(glm::vec3(kLightAmbient)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.diffuse"), 1,
               glm::value_ptr(glm::vec3(kLightDiffuse)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.specular"), 1,
               glm::value_ptr(glm::vec3(kLightSpecular)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.spotDirection"), 1,
               glm::value_ptr(glm::vec3(kLightDirection)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.halfVector"), 1,
               glm::value_ptr(glm::vec3(camera_->getPosition() - kLightDirection)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.eyePosition"), 1,
               glm::value_ptr(glm::vec3(camera_->getPosition())));

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.spotExponent"), kLightSpotExponent);

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.spotCutoff"), kLightCutoff);

        glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.spotCosCutoff"), kLightCosCutoff);

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.constantAttenuation"), kLightAttConst);

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.linearAttenuation"), kLightAttLin);

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "light1.quadraticAttenuation"), kLightAttQuad);


    //uniforms for material
    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "material1.emission"), 1,
               glm::value_ptr(glm::vec3(kMaterialEmission)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "material1.ambient"), 1,
               glm::value_ptr(glm::vec3(kMaterialAmbient)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "material1.diffuse"), 1,
               glm::value_ptr(glm::vec3(kMaterialDiffuse)));

    glUniform3fv(glGetUniformLocation(shader_manager_.getActiveProg(), "material1.specular"), 1,
               glm::value_ptr(glm::vec3(kMaterialSpecular)));

    glUniform1f(glGetUniformLocation(shader_manager_.getActiveProg(), "material1.shininess"), kMaterialShininess);


    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    // Make our background black
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(std::vector<std::shared_ptr<Model> >::iterator it = scene_objects_.begin();
        it != scene_objects_.end(); it++)
        (*it)->render();
    //glPopMatrix();
}

void Scene::update()
{
    camera_->update();
    world_ = camera_->getMatrix();
    //world_ = glm::mat4();

    //Adds new scene objects to the scene.
    for(std::vector<std::shared_ptr<Model> >::iterator it = new_children_.begin();
        it != new_children_.end(); )
    {
        scene_objects_.push_back((*it));
        it = new_children_.erase(it);
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
    camera_->init();
    world_ = camera_->getMatrix();
    shader_manager_.loadShader("res/shaders/phong");
    shader_manager_.loadShader("res/shaders/simple");
    shader_manager_.loadShader("res/shaders/toon");
    shader_manager_.loadShader("res/shaders/simplevertexlight");
    shader_manager_.loadShader("res/shaders/simplefragmentlight");
    shader_manager_.loadShader("res/shaders/pointlight");
    shader_manager_.loadShader("res/shaders/spotlight");
    shader_manager_.activeShader(0);
}

void Scene::addModelToScene(char *path)
{
    std::shared_ptr<Model> mod;
    mod.reset(new Model(path));
    if(mod->init())
        addSceneObject(mod);
    else
        std::cout << "File not added to scene" <<std::endl;
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
    new_children_.push_back(newChild);
}

/**
 * @brief Scene::removeSceneObject
 * @param child
 *
 *  Removes object from scene.
 */
void Scene::removeSceneObject(const std::shared_ptr<Model> child)
{
    for(std::vector<std::shared_ptr<Model> >::iterator it = scene_objects_.begin();
        it != scene_objects_.end(); it++)
    if(*it == child)
    {
        scene_objects_.erase(it);
        break;
    }
}

void Scene::toggleSceneObject(const std::shared_ptr<Model> child)
{
    for(std::vector<std::shared_ptr<Model> >::iterator it = scene_objects_.begin();
        it != scene_objects_.end(); it++)
    if(*it == child)
    {
        break;
    }
}

void Scene::updateProjection(glm::mat4 projection)
{
    projection_ = projection;
}


