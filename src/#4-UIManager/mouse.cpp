#include "mouse.h"
#include "applicationsConsts.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <raymath.h>
#pragma GCC diagnostic pop



Mouse::Mouse()
{
    mouseEnabled = true;
    EnableCursor();   
    MousePos.x = static_cast<float>(GetMouseX());
    MousePos.y = static_cast<float>(GetMouseY());
}

Vector2 Mouse::getScaledMousePos()
{
    Vector2 mousePos = GetMousePosition();
            Vector2 windowSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
                Vector2 virtualSize = {window::windowWidth, window::windowHeight}; // Your target virtual size

                // Calculate the scale and offset (accounts for letterboxing)
                    float scale = fmin(windowSize.x / virtualSize.x, windowSize.y / virtualSize.y);
                         Vector2 offset = {
                            (windowSize.x - virtualSize.x * scale) * 0.5f,
                                (windowSize.y - virtualSize.y * scale) * 0.5f};

                            // Convert screen mouse position to virtual coordinates
                        Vector2 virtualMousePos = {
                     (mousePos.x - offset.x) / scale,
                 (mousePos.y - offset.y) / scale};
            // Clamp to ensure coordinates stay within virtual screen
         virtualMousePos.x = Clamp(virtualMousePos.x, 0, virtualSize.x);
    virtualMousePos.y = Clamp(virtualMousePos.y, 0, virtualSize.y);
    return virtualMousePos;
}


void Mouse::updateMouse()
{
    MousePos = getScaledMousePos();

}

bool Mouse::leftClicked()
{
    if(IsMouseButtonPressed(0))
    {return true;}
    else{return false;}
}

Mouse::~Mouse()
{
    mouseEnabled = false;
    DisableCursor();
}





