#ifndef __FNAF_CAMERA_HPP__
#define __FNAF_CAMERA_HPP__

#include <raylib.h>

namespace fnaf {
namespace core {

typedef struct fnaf_camera_controls {
    int fcKEY_FORWARD;
    int fcKEY_BACKWORD;
    int fcKEY_LEFT;
    int fcKEY_RIGHT;
    int fcKEY_UP;
    int fcKEY_DOWN;
} fnaf_camera_controls;

class fnaf_camera final {
private:
    Vector3 m_current_pos;
    fnaf_camera_controls* m_controls;
public:
    fnaf_camera();
    ~fnaf_camera();

    fnaf_camera(const fnaf_camera&);

    Vector3 operator +  (const Vector3&);
    Vector3 operator -  (const Vector3&);
    
    bool operator <  (const Vector3&);
    bool operator >  (const Vector3&);

    bool operator != (const fnaf_camera&);
    bool operator != (const Vector3&);
    bool operator == (const fnaf_camera&);
    
    fnaf_camera operator =  (const fnaf_camera&);
public:

    void enable_free_roam(Vector3& start_point = (Vector3) {0, 0, 0}) noexcept;
    void update_camera() noexcept;
    void set_movement_controls(const fnaf_camera_controls*) noexcept;

    Vector3 get_current_pos() const noexcept;
    Vector3 set_current_pos() noexcept;

};

}
}

#endif /* __FNAF_CAMERA_HPP__ */