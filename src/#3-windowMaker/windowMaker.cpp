#include "windowmaker.h"
#include "applicationsConsts.h"



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <raymath.h>
#pragma GCC diagnostic pop
#include <iostream>


void Window::windowInit()
{
    SetTraceLogLevel(LOG_ERROR);
    SetTargetFPS(60);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    
        

    InitWindow(window::windowWidth,window::windowHeight,"Calculator");
m_icon = LoadImage("icon.png"); 
    if(IsImageValid(m_icon))
    {
        std::cout << "image vaild";
        SetWindowIcon(m_icon);
        UnloadImage(m_icon);
    }
    SetWindowMinSize(window::windowWidth,window::windowHeight);
    updateScale();
    target = LoadRenderTexture(window::windowWidth,window::windowHeight);
    SetTextureFilter(target.texture,TEXTURE_FILTER_BILINEAR);
}

void Window::updateScale()
{
    float scale  = 
                //scale X  
    fmin(static_cast<float>(GetScreenWidth())  / window::windowWidth,
    
                //scale Y
    static_cast<float>(GetScreenHeight()) / window::windowHeight);

    m_viewPortWidth  = static_cast<float>(window::windowWidth  * scale);
    m_viewPortHeight = static_cast<float>(window::windowHeight * scale);

    m_viewPortX = ((static_cast<float>(GetScreenWidth())   - m_viewPortWidth)  / 2);
    m_viewPortY = ((static_cast<float>(GetScreenHeight())  - m_viewPortHeight) / 2);

}

void Window::cleanUp()
{
    UnloadTexture(target.texture);
    CloseWindow();
}




void Window::drawInstructionToVirtualWindow(Color color)
{
    BeginTextureMode(target);
    ClearBackground(color);
}



void Window::endOfInstructionToVirtualWindow()
{
    EndTextureMode();
}


void Window::drawVirtualWindow(Color color)
{
     BeginDrawing();
            ClearBackground(color);
                DrawTexturePro(target.texture,
                {0,0,static_cast<float>(window::windowWidth), - static_cast<float>(window::windowHeight)},
                {static_cast<float>(m_viewPortX), static_cast<float>(m_viewPortY),
                static_cast<float>(m_viewPortWidth), static_cast<float>(m_viewPortHeight)},
                {0,0},
                0.0f,
                WHITE
            );
        DrawRectangleLines(static_cast<int>(m_viewPortX),static_cast<int>(m_viewPortY),
            static_cast<int>(m_viewPortWidth),static_cast<int>(m_viewPortHeight),GREEN);
        
        EndDrawing();
}



