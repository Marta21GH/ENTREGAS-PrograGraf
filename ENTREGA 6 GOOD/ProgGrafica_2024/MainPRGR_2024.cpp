#include <iostream>
#include "libprgr/vectorMath.h"
#define GLAD_BIN
#include "libprgr/common.h"
#include "libprgr/render.h"
#include "libprgr/Sphere.h"     
#include "libprgr/Collider.h" 

using namespace libPRGR;

int main(int argc, char** argv)
{
    Render* r = new Render();
        Camera* cam1 = new Camera({ 0,0,-3,1 }, { 0,1,0,0 }, { 0,0,0,1 });
    Light* light1 = new OrbitalLight({ 0,0,-3,1 }, { 1,1,1,1 }, 0.5, 1.0, 2.0, LightType::POINT, { 0, 0, 0, 1 }, 1.0f);
    //Light* light2 = new OrbitalLight({ 1,0,-2,1 }, { 0.9,0.8,1,1 }, 0.5, 1.0, 2.0, LightType::POINT, { 0, 0, 0, 1 }, 1.0f);

    GLFWwindow* window = r->initGLFW();

    // Crear objeto
    Object* objf = new Object();
    objf->loadFromFile("data/cubeSplit.fiis");

    // Crear colisionador para el objeto
    Sphere* col = new Sphere();
    Collider::particle part;
    part.min = objf->pos - Vector4f{ 0.5f, 0.5f, 0.5f, 0 };
    part.max = objf->pos + Vector4f{ 0.5f, 0.5f, 0.5f, 0 };
    col->addParticle(part);
    col->update(objf->computeModelMatrix());
    objf->coll = col;

    r->setUpObject(objf);
    r->putCamera(cam1);
    r->putLight(light1);
    //r->putLight(light2);

    r->mainLoop();
    r->deinitGLFW();
    return 0;
}
