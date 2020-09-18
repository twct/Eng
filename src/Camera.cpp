#include <Camera.h>
#include <Log.h>

Camera::Camera() :
    Camera(0, 0, 0, 0)
{
}

Camera::Camera(const int x, const int y, const int w, const int h)
{
    m_cameraBounds = {x, y, w, h};
    m_cameraPosition = {(float) m_cameraBounds.x, (float) m_cameraBounds.y};
}

Camera::Camera(const SDL_Rect &bounds) :
    Camera(bounds.x, bounds.y, bounds.w, bounds.h)
{
}

Camera::Camera(const Camera &camera) :
    Camera(camera.bounds())
{
}

const SDL_Rect Camera::bounds() const
{
    return m_cameraBounds;
}

void Camera::center(const int x, const int y)
{
    center({(float)x, (float)y});
}

void Camera::center(const Vector2f &position)
{
    m_cameraBounds.x = position.x / (m_cameraBounds.w / 2);
    m_cameraBounds.y = position.y / (m_cameraBounds.h / 2);
}

void Camera::follow(const Vector2f &position)
{
    m_cameraPosition = m_cameraPosition.lerp(position, 0.5);

    center(m_cameraPosition);
}