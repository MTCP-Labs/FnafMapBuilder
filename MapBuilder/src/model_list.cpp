#include "model_list.hpp"

using json = nlohmann::json;

ModelList::ModelList() {}

ModelList::~ModelList() {}

Model* ModelList::get(std::string id) {
    return (modelList.find(id) != modelList.end()) ? modelList[id] : nullptr;
}

Model* ModelList::get_infocus_model(Camera3D camera) {
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

void ModelList::load_properties() {
    std::ifstream inFile(jsonPath);
    if (inFile.is_open()) {
        inFile >> properties;
        inFile.close();
    } else {
        std::cerr << "Unable to open file: properties.json for reading." << std::endl;
    }

    for(auto &p : properties.items()) {
        std::vector<std::vector<float>> t = p.value();
        get(p.key())->transform = {
            t[0][0], t[0][1], t[0][2], t[0][3],
            t[1][0], t[1][1], t[1][2], t[1][3],
            t[2][0], t[2][1], t[2][2], t[2][3],
            t[3][0], t[3][1], t[3][2], t[3][3]
        };
    }
}

void ModelList::store_properties() {
    for(auto p : modelList) {
        Matrix t = get(p.first)->transform;
        std::vector<std::vector<float>> transform = {
            {t.m0, t.m4, t.m8, t.m12},
            {t.m1, t.m5, t.m9, t.m13},
            {t.m2, t.m6, t.m10, t.m14},
            {t.m3, t.m7, t.m11, t.m15}
        };
        properties[p.first] = transform;
    }

    std::ofstream outFile(jsonPath);
    if (outFile.is_open()) {
        outFile << properties;
        outFile.close();
    } else {
        std::cerr << "Unable to open file: properties.json for writing." << std::endl;
    }
}


void ModelList::add(std::string id, Model *model) {
    modelList[id] = model;
}

void ModelList::set_material_texture(std::string id, int mapType, Texture2D *texture) {
    SetMaterialTexture(&get(id)->materials[0], mapType, *texture);
    textureList[id] = texture;
}

void ModelList::draw_all_models() {
    if(!isLoaded) {
        load_properties();
        isLoaded = true;
    }
    for(auto p : modelList) {
        DrawModel(*p.second, (Vector3) {0.0f, 0.0f, 0.0f}, 1.0f, WHITE);        // Draw models with the provided offests 
    }
}

void ModelList::unload() {
    store_properties();
    for(auto p : modelList) {
        UnloadModel(*p.second);
    }
    for(auto p : textureList) {
        UnloadTexture(*p.second);
    }
}