#ifndef __MAPBUILDER_HPP__
#define __MAPBUILDER_HPP__

#include "log.hpp"
#include "modelex.hpp"
#include "input_box.hpp"

class MapBuilder {
private:
    bool isMenuDisplayed = true;
    InputBox ib_pos_y;
    const int MENU_START_X = 10, MENU_START_Y = 10;
    const Vector3 zeroes = {0.0f, 0.0f, 0.0f}, ones = {1.0f, 1.0f, 1.0f};

    float text_size(int fontSize, int len);
public:
    ModelEx modelEx;
    Camera3D camera;
    KeyboardKey MENU_KEY = KEY_F1;

    MapBuilder(ModelEx modelEx, Camera3D camera);
    MapBuilder(ModelEx modelEx, Camera3D camera, KeyboardKey CUSTOM_MENU_KEY);
    ~MapBuilder();

    void init_map_builder(int screenWidth, int screenHeight);
};

#endif /*__MAPBUILDER_HPP__*/
