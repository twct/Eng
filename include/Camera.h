#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL2/SDL_rect.h>
#include <Vector2f.h>

class Camera
{
private:
    SDL_Rect m_cameraBounds;
    Vector2f m_cameraPosition;
public:
    Camera();
    Camera(const int x, const int y, const int w, const int h);
    Camera(const SDL_Rect &bounds);
    Camera(const Camera &camera);
    void center(const int x, const int y);
    void center(const Vector2f &position);
    void follow(const Vector2f &position);
    const SDL_Rect bounds() const;
};

#endif