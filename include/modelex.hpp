#ifndef __MODELEX_HPP__
#define __MODELEX_HPP__

#include <raylib.h>

class ModelEx {
public:
    Model model;
    Vector3 position, rotationAxis, scale;
    float rotationAngle;
public:
    ModelEx();
    ModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale);
    ~ModelEx();
    
    void draw();
};

#endif /* __MODELEX_HPP__ */