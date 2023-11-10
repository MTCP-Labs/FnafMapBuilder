#include "modelex.hpp"

ModelEx::ModelEx() {}

ModelEx::ModelEx(Model model, Texture2D texture, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale): model(model), texture(texture), position(position), rotationAxis(rotationAxis), rotationAngle(rotationAngle), scale(scale) {
    SetMaterialTexture(&model.materials[0], MATERIAL_MAP_DIFFUSE, texture); 
}

ModelEx::~ModelEx() {}

void ModelEx::draw() {
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
}