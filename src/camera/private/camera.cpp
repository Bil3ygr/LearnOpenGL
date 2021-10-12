#include "camera/public/camera.h"

#include "utils/public/mousemanager.h"
#include "utils/public/helper.h"

Camera::Camera()
{
    enable_ = true;
    speed_ = 2.5f;

    pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
    front_ = glm::vec3(0.0f, 0.0f, -1.0f);
    up_ = glm:: vec3(0.0f, 1.0f, 0.0f);

    euler_angle_ = new EulerAngle();
    mouse_pos_ = glm::vec2();
    first_mouse_ = true;
    fov_ = 45.0f;

    Register();
}

Camera::Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) :
    pos_(pos), front_(front), up_(up)
{
    enable_ = true;
    speed_ = 2.5f;

    euler_angle_ = new EulerAngle();
    mouse_pos_ = glm::vec2();
    first_mouse_ = true;
    fov_ = 45.0f;

    Register();
}

Camera::~Camera()
{
    if (program_)
        ShaderManager::Instance().SetMat4(program_, "view", glm::mat4(1.0f));
    SAFE_DELETE(euler_angle_)
}

void Camera::Register()
{
    REGISTER_MOUSE_MOVE("camera_move", UpdateFront);
    REGISTER_MOUSE_SCROLL("camera_fov", UpdateFov);
}

void Camera::Update()
{
    // Update(glm::lookAt(pos_, pos_ + front_, up_));
    Update(LookAt());
}

void Camera::Update(glm::mat4 view)
{
    if (!program_)
        return;

    ShaderManager::Instance().SetMat4(program_, "view", view);

    int width, height;
    glfwGetWindowSize(const_cast<GLFWwindow*>(MainWindow::Instance().window()), &width, &height);
    glm::mat4 projection = glm::perspective(glm::radians(fov_), (float)(width / height), 0.1f, 100.0f);
    ShaderManager::Instance().SetMat4(program_, "projection", projection);
}

void Camera::LookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
    pos_ = pos;
    front_ = front;
    up_ = up;
}

const glm::mat4& Camera::LookAt()
{
    /*
    *          |Rx  Ry  Rz  0|   |1  0  0 -Px|
    * LookAt = |Ux  Uy  Uz  0| * |0  1  0 -Py|
    *          |Dx  Dy  Dz  0|   |0  0  1 -Pz|
    *          | 0   0   0  1|   |0  0  0  1 |
    *
    * D -> direction: pos - target;
    * R -> right: glm::cross((0, 1, 0), direction);
    * U -> up: real up vector, not (0, 1, 0);
    * P -> position: camera pos;
    */
    glm::vec3 dir = glm::normalize(-front_);
    glm::vec3 right = glm::normalize(glm::cross(up_, dir));
    glm::vec3 up = glm::normalize(glm::cross(dir, right));
    glm::mat4 space(1.0f);
    for (int i = 0; i < 3; i++)
        space[i] = VEC3_TO_4(right, up, dir, i);
    glm::mat4 pos(1.0f);
    pos[3] = glm::vec4(-pos_, 1.0f);
    return space * pos;
}

void Camera::UpdateFront(float x, float y)
{
    if (first_mouse_)
    {
        mouse_pos_ = glm::vec2(x, y);
        first_mouse_ = false;
        return;
    }

    float sensitivity = 0.05f;
    ADD_YAW(euler_angle_, (x - mouse_pos_.x) * sensitivity);
    ADD_PITCH(euler_angle_, (mouse_pos_.y - y) * sensitivity);

    front_ = euler_angle_->ToVec3();
    mouse_pos_ = glm::vec2(x, y);
}

void Camera::UpdateFov(float x, float y)
{
    if (fov_ >= 1.0f && fov_ <= 60.0f)
        fov_ -= y;
    if (fov_ <= 1.0f)
        fov_ = 1.0f;
    if (fov_ >= 60.0f)
        fov_ = 60.0f;
}

void Camera::SetMoveSpeed(float speed)
{
    speed_ = speed;
}

void Camera::MoveLeft()
{
    pos_ -= speed() * glm::normalize(glm::cross(front_, up_));
}

void Camera::MoveRight()
{
    pos_ += speed() * glm::normalize(glm::cross(front_, up_));
}

void Camera::MoveFront()
{
    pos_ += speed() * front_;
}

void Camera::MoveBack()
{
    pos_ -= speed() * front_;
}

void Camera::ResetMousePos()
{
    first_mouse_ = true;
}
