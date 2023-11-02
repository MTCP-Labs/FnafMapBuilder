#include "core/fnaf_camera.hpp"

using namespace fnaf::core;

fnaf_camera::fnaf_camera() {

}

fnaf_camera::~fnaf_camera() {

}

fnaf_camera::fnaf_camera(const fnaf_camera&) {

}

Vector3 fnaf_camera::operator + (const Vector3& vec) {
    return (Vector3) { 
        this->m_current_pos.x + vec.x,
        this->m_current_pos.y + vec.y,
        this->m_current_pos.z + vec.z
    };
}

Vector3 fnaf_camera::operator - (const Vector3& vec) {
    return (Vector3) { 
        this->m_current_pos.x - vec.x,
        this->m_current_pos.y - vec.y,
        this->m_current_pos.z - vec.z
    };
}

bool fnaf_camera::operator < (const Vector3& vec) {
    return (
        this->m_current_pos.x < vec.x &&
        this->m_current_pos.y < vec.y &&
        this->m_current_pos.z < vec.z
    );
}

bool fnaf_camera::operator > (const Vector3& vec) {
    return (
        this->m_current_pos.x > vec.x &&
        this->m_current_pos.y > vec.y &&
        this->m_current_pos.z > vec.z
    );
}

bool fnaf_camera::operator != (const Vector3& vec) {
    return (
        this->m_current_pos.x != vec.x &&
        this->m_current_pos.y != vec.y &&
        this->m_current_pos.z != vec.z
    );
}

bool fnaf_camera::operator == (const Vector3& vec) {
    return (
        this->m_current_pos.x == vec.x &&
        this->m_current_pos.y == vec.y &&
        this->m_current_pos.z == vec.z
    );
}

fnaf_camera fnaf_camera::operator = (const fnaf_camera& fc) {
    this->m_current_pos = fc.get_current_pos();
    this->m_controls = const_cast<fnaf_camera_controls*>(fc.get_controls());
    return *this;
}


void fnaf_camera::enable_free_roam(const Vector3& start_point) noexcept {
    this->m_mode = FNAF_CAM_FREE;
    this->m_current_pos = start_point;
}

void fnaf_camera::update_camera() noexcept {
    UpdateCamera(&this->m_camera, this->m_mode);
}

void fnaf_camera::set_movement_controls(const fnaf_camera_controls*) noexcept {

}

void fnaf_camera::set_current_pos(const Vector3&) noexcept {

}

const Vector3 fnaf_camera::get_current_pos() const noexcept {
    return this->m_current_pos;
}

const fnaf_camera_controls* fnaf_camera::get_controls() const noexcept {
    return this->m_controls;
}