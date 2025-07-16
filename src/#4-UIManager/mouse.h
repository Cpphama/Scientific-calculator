#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <raylib.h>
#pragma GCC diagnostic pop

class Mouse
{   
    public:
    Mouse();
    ~Mouse();
   
    bool mouseEnabled;
    
    
    Vector2 MousePos;

    void updateMouse();
    bool leftClicked();

    private:
    Vector2 getScaledMousePos();

   

};