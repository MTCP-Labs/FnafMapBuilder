#ifndef __MAPBUILDER_HPP__
#define __MAPBUILDER_HPP__

#include <raylib.h>
#include <raymath.h>

#include "input_box.hpp"
#include "model_list.hpp"

class MapBuilder : public ModelList {
private:
    const int MENU_START_X = 10, MENU_START_Y = 0;
    const Vector3 zeroes = {0.0f, 0.0f, 0.0f}, ones = {1.0f, 1.0f, 1.0f};

    int screenWidth, screenHeight;
    bool isMenuDisplayed = false;  

    Camera3D camera = { 0 };

    Model *inFocusModel;
    float rotationAngle;
    float propertyList[3][3];

    InputBox inputBoxList[3][3];
    InputBox *inFocusInputBox;  


    float text_size(int fontSize, int len);

    void init_camera();

    void init_property_list();
    void update_infocus_model();
    void set_transform();

    void init_input_box_list();
    void draw_input_box_list();
    void set_infocus_input_box();
    void reset_infocus_input_box();

public:
    KeyboardKey MENU_KEY = KEY_F1;
    KeyboardKey CAMERA_RESET_KEY = KEY_F2;

    MapBuilder();
    ~MapBuilder();

    void init_map_builder();
};

#endif /*__MAPBUILDER_HPP__*/
