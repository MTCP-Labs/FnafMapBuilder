#ifndef __MODELEX_HPP__
#define __MODELEX_HPP__

#include <raylib.h>

class ModelEx {
public:
    Model model;
    Texture2D texture;
    Vector3 position, rotationAxis, scale;
    float rotationAngle;

    ModelEx();
    ModelEx(Model model, Texture2D texture, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);
    ~ModelEx();
    
    void draw();
};

#endif /* __MODELEX_HPP__ */