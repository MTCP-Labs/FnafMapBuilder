#include "modelex.hpp"

ModelEx::ModelEx() {}

ModelEx::ModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale): model(model), position(position), rotationAxis(rotationAxis), rotationAngle(rotationAngle), scale(scale) {}

ModelEx::~ModelEx() {}

void ModelEx::draw() {
    DrawModelEx(model, position, rotationAxis, rotationAngle, scale, WHITE);
}