#pragma once 
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#include <raylib.h>
#pragma GCC diagnostic pop
#include "mouse.h"
#include <array>


struct Buttons{
public:
Buttons() = default;
~Buttons() = default;

Rectangle rect;
Color color;
bool isHoverdedOver = false;


};



class CalcScreen
{  
    public:
    CalcScreen();
    ~CalcScreen() = default;


    Rectangle topScreenRect;
    Rectangle screenRect;
    
    void drawCalcScreen();

};




class LayoutManager
{
    public:
    LayoutManager();
   ~LayoutManager();

    void draw();
    
    //  25 left 23 button right  

    std::array<Buttons,48> ButtonLayout;
    CalcScreen calculatorScreen;
    Mouse calcMouse;
    void checkInput();
    
    void setButtonsInfo();
    

    private:
    void setRightSideInfo(Buttons & button,float posX,float posY,Color color);
    void setLeftSideInfo(Buttons & button,float posX,float posY,Color color);
    void drawButtons();
    bool isMouseTouchingButton();   // right side
    bool isMouseTouchingButton2(); // left side
    void drawNumsAndSymbole();
    void setBackDefualtColorAfterHover();
    void drawEquation();

    bool m_hoverHappend;
    Font m_font;
    bool m_fontLoaded;
    unsigned int  m_currentlyOn;
    Texture2D m_backspaceTexture;
    bool m_backspaceIconLoaded;
    bool m_goToLeft = true;
};