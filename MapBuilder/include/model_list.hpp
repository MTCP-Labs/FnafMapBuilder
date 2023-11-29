#ifndef __MODEL_LIST_HPP__
#define __MODEL_LIST_HPP__

#include <raylib.h>
#include <raymath.h>

#include <unordered_map>
#include <string>

#define FLT_MAX 340282346638528859811704183484516925440.0f

class ModelList {
protected:
    std::unordered_map<std::string, Model*> modelList;
    std::unordered_map<std::string, Texture2D*> textureList;

    Model* get(std::string id);
    Model* get_infocus_model(Camera3D camera);
    void draw_all_models();
public:
    ModelList();
    ~ModelList();
    
    void add(std::string id, Model* model);
    void set_material_texture(std::string id, int mapType, Texture2D *texture);
    void unload_all_models();
    void unload_all_textures();
};

#endif /*__MODELEX_LIST_HPP__*/
