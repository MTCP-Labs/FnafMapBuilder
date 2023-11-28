#include "model_list.hpp"

ModelList::ModelList() {}

ModelList::~ModelList() {}

Model* ModelList::get(std::string id) {
    return (modelList.find(id) != modelList.end()) ? modelList[id] : nullptr;
}

Model *ModelList::get_infocus_model(Camera3D camera) {
    Ray ray = (Ray){ camera.position, Vector3Normalize(Vector3Subtract(camera.target, camera.position))};

    RayCollision collision = { 0 };
    collision.distance = FLT_MAX;
    collision.hit = false;

    for(auto p : modelList) {
        // Check ray collision against model meshes
        RayCollision meshHitInfo = { 0 };
        for (int m = 0; m < p.second->meshCount; m++)
        {
            meshHitInfo = GetRayCollisionMesh(ray, p.second->meshes[m], p.second->transform);
            if (meshHitInfo.hit)
            {
                if ((!collision.hit) || (collision.distance > meshHitInfo.distance)) collision = meshHitInfo;

                break;
            }
        }

        if (meshHitInfo.hit)
        {
            return p.second;        // Return the model which collided with the ray
        }
    }

    return nullptr;
}

void ModelList::draw_all_models() {
    for(auto p : modelList) {
        DrawModel(*p.second, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);        // Draw models with the provided offests 
    }
}


void ModelList::add(std::string id, Model *model) {
    modelList[id] = model;
}

void ModelList::set_material_texture(std::string id, int mapType, Texture2D *texture) {
    SetMaterialTexture(&get(id)->materials[0], mapType, *texture);
    textureList[id] = texture;
}

void ModelList::unload_all_models() {
    for(auto p : modelList) {
        UnloadModel(*p.second);
    }
}

void ModelList::unload_all_textures() {
    for(auto p : textureList) {
        UnloadTexture(*p.second);
    }
}
