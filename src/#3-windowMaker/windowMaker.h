#pragma once


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <raylib.h>
#pragma GCC diagnostic pop




class Window
{
public:
void updateScale();
void windowInit();
void cleanUp();

void drawInstructionToVirtualWindow(Color color);//starts texture mode

void endOfInstructionToVirtualWindow();//ends texture mode

void drawVirtualWindow(Color color);//

Window() = default;
~Window() = default;
RenderTexture2D target;





private:

float m_viewPortWidth       {1.0};
float m_viewPortHeight      {1.0};
float m_viewPortX           {1.0};
float m_viewPortY           {1.0};
Image m_icon;

};