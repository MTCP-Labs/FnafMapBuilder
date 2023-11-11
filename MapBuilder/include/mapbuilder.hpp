#ifndef __MAPBUILDER_HPP__
#define __MAPBUILDER_HPP__

#include <vector>
#include <cmath>

#include "log.hpp"
#include "modelex.hpp"
#include "input_box.hpp"

class MapBuilder {
private:
    const int MENU_START_X = 10, MENU_START_Y = 0;
    const Vector3 zeroes = {0.0f, 0.0f, 0.0f}, ones = {1.0f, 1.0f, 1.0f};
    
    float *modelex_property_list[3][3];

    InputBox inputBoxList[3][3];
    InputBox *inFocusInputBox = nullptr;

    bool isMenuDisplayed = true;    

    float text_size(int fontSize, int len);
    
    void init_modelex_property_list();

    void init_input_box_list();
    void draw_input_box_list();
    void set_infocus_input_box();
    void reset_infocus_input_box();

    void update_modelex();
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
