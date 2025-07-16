#include "buttons.h"
#include "applicationsConsts.h"
#include <cstdint>
#include <iostream>
#include <array>
#include "logic.h"

static LogicParser parser;

namespace symboles
{

    constexpr std::array<const char *, 10> nums = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    constexpr std::array<const char *, 8> operators = {"+", "-", "/", "x", "%", "=", "C","^"}; // (0 = +) (1 = -) (2 = ÷) (3 = x) (4 = %) (5 = =) (6 = C) (7 = ^)
    constexpr std::array<const char *, 2> parenthesis = {"(", ")"};
    constexpr std::array<const char *, 3> constants = {"g", "e","π"};
    constexpr const char * point= {"."};
    constexpr const char * deg  = "DEG";
    constexpr const char * rad  = "RAD";
    constexpr const char * log  = "log";
    constexpr const char * ln   = "ln"; 
    constexpr const char * xChar = "X";
    constexpr const char * sqrt  = "√";
    constexpr std::array<const char *,11> sinFuncs = {"sin","asin","sinh"};
    constexpr std::array<const char *,11> cosFuncs = {"cos","acos","cosh"};
    constexpr std::array<const char *,11> tanFuncs = {"tan","atan","tanh"}; 

    /*
        DB | DB | DB | DB | RED
        CY | CY | CY | DB | ORG
        CY | CY | CT | DB |
        CY | CY | CT | DB |
        CY | CY | CT | DB |  DB

        
        23  |  24  |   25   |    26    |  27          0   |   1   |    2   |   3     |   4
    
        28  |  29  |   30   |    31    |  32          5   |   6   |    7   |   8     |   9
    
        33  |  34  |   35   |    36    |  37          10  |  11   |   12   |   13    |
    
        38  |  39  |   40   |    41    |  42          14  |  15   |   16   |   17    |   22
    
        43  |  44  |   45   |    46    |  47          18  |  19   |   20   |   21    |


    */

}

static constexpr Color M_DARKBLUE = {39, 22, 192, 255};

static constexpr Color M_SILVER   = {123,121,122,255};
static constexpr Color M_HOVERCOLOR ={20, 121,180,255};


LayoutManager::LayoutManager()
{
    int codepoints[] = {// ASCII 32–126
    32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,
    48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,
    64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,
    80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
    96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,
    112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,
    // π and √
    0x03C0, // π
    0x221A  // √
    };
    
    
    m_font = LoadFontEx("../font/arial.ttf",30,codepoints,sizeof(codepoints)/sizeof(int));

    Image backspacepng = LoadImage("../textures/backspace.png");

    if (IsImageValid(backspacepng))
    {
        m_backspaceTexture = LoadTextureFromImage(backspacepng);
        m_backspaceIconLoaded = true;
        std::cout << "backspace icon loaded..\n";
    }
    else
    {
        m_backspaceIconLoaded = false;
        std::cout << "backspace icon load failed..\n";
    }

    if (IsFontValid(m_font))
    {
        std::cout << "font is vaild...\n";
        m_fontLoaded = true;
    }
    else
    {
        std::cout << "font could't be loaded using raylib default font...";
        m_fontLoaded = false;
    }
    if (m_backspaceIconLoaded)
        UnloadImage(backspacepng);
}











void LayoutManager::setButtonsInfo()
{
    // padding 15

    for(size_t i = 0; i <= 47; i++)
    {
        if (i <= 4)
        {
            setRightSideInfo(ButtonLayout[i],
                            (415 + (static_cast<float>(i) * 55.5f)), 125, M_DARKBLUE);
            if (i == 4)
            {
                ButtonLayout[i].color = {192, 2, 22, 255};
            } // redish color
        }
        else if (i <= 9)
        {
            setRightSideInfo(ButtonLayout[i],
                            (415 + (static_cast<float>(i - 5) * 55.5f)), 178.5, BLUE);
            if (i == 8)
            {
                ButtonLayout[i].color = M_DARKBLUE;
            }
            if (i == 9)
            {
                ButtonLayout[i].color = {254, 173, 76, 255};
            } // orangeish color
        }
        else if (i <= 13)
        {
            setRightSideInfo(ButtonLayout[i],
                            (415 + (static_cast<float>(i - 10) * 55.5f)), 232.0f, BLUE);
            if (i == 13)
            {
                ButtonLayout[i].color = M_DARKBLUE;
            }
        }
        else if (i <= 17)
        {
            setRightSideInfo(ButtonLayout[i],
                            (415 + (static_cast<float>(i - 14) * 55.5f)), 285.5f, BLUE);
            if (i == 17)
            {
                ButtonLayout[i].color = M_DARKBLUE;
            }
        }
        else if (i <= 21)
        {
            setRightSideInfo(ButtonLayout[i],
                            (415 + (static_cast<float>(i - 18) * 55.5f)), 339.0f, BLUE);
            if (i == 21)
            {
                ButtonLayout[i].color = M_DARKBLUE;
            }
        }
        else if (i == 22)
        {
            ButtonLayout[i].rect.x = 637;
            ButtonLayout[i].rect.y = 232.0f;
            ButtonLayout[i].rect.height = 155.0f;
            ButtonLayout[i].rect.width = 48;
            ButtonLayout[i].color = {39, 22, 142, 255};
        }
        else if (i <= 27)
        {
            setLeftSideInfo(ButtonLayout[i],20 + (static_cast<float>(i - 23) * 77.5f)
                                                            ,ButtonLayout[0].rect.y,M_SILVER);
        }
        else if (i <= 32)
        {
            setLeftSideInfo(ButtonLayout[i],20 + (static_cast<float>(i - 28) * 77.5f)
                                                            ,ButtonLayout[5].rect.y,M_SILVER);
        }
        else if (i <= 37)
        {
            setLeftSideInfo(ButtonLayout[i],20 + (static_cast<float>(i - 33) * 77.5f)
                                                            ,ButtonLayout[12].rect.y,M_SILVER);
        }
        else if (i <= 42)
        {
            setLeftSideInfo(ButtonLayout[i],20 + (static_cast<float>(i - 38) * 77.5f)
                                                            ,ButtonLayout[17].rect.y,M_SILVER);
        }
        else if(i <= 47)
        {
            setLeftSideInfo(ButtonLayout[i],20 + (static_cast<float>(i - 43) * 77.5f)
                                                            ,ButtonLayout[20].rect.y,M_SILVER);
        }
        
    }

    
    
    
    
    

}

void LayoutManager::drawButtons()
{
    // drawing the button outline
    {
        DrawRectangleRoundedLines({calculatorScreen.screenRect.x, calculatorScreen.screenRect.y + 60,
                                   calculatorScreen.screenRect.width, calculatorScreen.screenRect.height * 5.4f},
                                  0.05f, 10, {111, 111, 111, 255});
        DrawRectangleRounded({calculatorScreen.screenRect.x + 1, calculatorScreen.screenRect.y + 61,
                              calculatorScreen.screenRect.width - 2, calculatorScreen.screenRect.height * 5.4f},
                             0.05f, 10, {88, 90, 100, 216});
    }

    for (size_t i = 0; i <= 47; i++)
    {
        DrawRectangleRounded(ButtonLayout[i].rect, 0.1f, 0, ButtonLayout[i].color);
    }
}


void LayoutManager::setRightSideInfo(Buttons &button, float posX, float posY, Color color)
{

    button.rect.width = 48;
    button.rect.height = 48;
    button.rect.x = posX;
    button.rect.y = posY;
    button.color = color;
}

void LayoutManager::setLeftSideInfo(Buttons & button,float posX,float posY,Color color)
{
    button.rect.width = 72;
    button.rect.height = 48;
    button.rect.x = posX;
    button.rect.y = posY;
    button.color = color;
}
















bool LayoutManager::isMouseTouchingButton()
{
    // optimizning touch detection
    if (calcMouse.MousePos.x >= ButtonLayout[22].rect.x && calcMouse.MousePos.x <= ButtonLayout[22].rect.x + ButtonLayout[22].rect.width && calcMouse.MousePos.y >= ButtonLayout[22].rect.y &&
        calcMouse.MousePos.y <= ButtonLayout[22].rect.y + ButtonLayout[22].rect.height)
    {
        ButtonLayout[22].isHoverdedOver = true;
        m_currentlyOn = static_cast<unsigned int>(22);
        return true;
    }
    else if (calcMouse.MousePos.y >= ButtonLayout[0].rect.y && calcMouse.MousePos.y <= ButtonLayout[0].rect.y + ButtonLayout[0].rect.height)
    {
        for (size_t i = 0; i <= 4; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }
    else if (calcMouse.MousePos.y >= ButtonLayout[5].rect.y && calcMouse.MousePos.y <= ButtonLayout[5].rect.y + ButtonLayout[5].rect.height)
    {
        for (size_t i = 5; i <= 9; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }
    else if (calcMouse.MousePos.y >= ButtonLayout[10].rect.y && calcMouse.MousePos.y <= ButtonLayout[10].rect.y + ButtonLayout[10].rect.height)
    {
        for (size_t i = 10; i <= 13; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }
    else if (calcMouse.MousePos.y >= ButtonLayout[14].rect.y && calcMouse.MousePos.y <= ButtonLayout[14].rect.y + ButtonLayout[14].rect.height)
    {
        for (size_t i = 14; i <= 17; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }
    else if (calcMouse.MousePos.y >= ButtonLayout[18].rect.y && calcMouse.MousePos.y <= ButtonLayout[18].rect.y + ButtonLayout[18].rect.height)
    {
        for (size_t i = 18; i <= 21; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }
    return false;
}


bool LayoutManager::isMouseTouchingButton2()
{
    if(parser.ismodeDeg)ButtonLayout[23].color = {98, 104, 252,255};
    else{ButtonLayout[24].color = {98, 104, 252,255};}


    if (calcMouse.MousePos.y >= ButtonLayout[23].rect.y && calcMouse.MousePos.y <= ButtonLayout[23].rect.y + ButtonLayout[23].rect.height)
    {
        for (size_t i = 23; i <= 27; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }else if(calcMouse.MousePos.y >= ButtonLayout[28].rect.y && calcMouse.MousePos.y <= ButtonLayout[28].rect.y + ButtonLayout[28].rect.height)
    {
        for (size_t i = 28; i <= 32; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }else if(calcMouse.MousePos.y >= ButtonLayout[33].rect.y && calcMouse.MousePos.y <= ButtonLayout[33].rect.y + ButtonLayout[33].rect.height)
    {
        for (size_t i = 33; i <= 37; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }else if(calcMouse.MousePos.y >= ButtonLayout[38].rect.y && calcMouse.MousePos.y <= ButtonLayout[38].rect.y + ButtonLayout[38].rect.height)
    {
        for (size_t i = 38; i <= 42; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }else if(calcMouse.MousePos.y >= ButtonLayout[43].rect.y && calcMouse.MousePos.y <= ButtonLayout[43].rect.y + ButtonLayout[43].rect.height)
    {
        for (size_t i = 43; i <= 47; i++)
        {
            if (calcMouse.MousePos.x > ButtonLayout[i].rect.x && calcMouse.MousePos.x < ButtonLayout[i].rect.x + ButtonLayout[i].rect.width && calcMouse.MousePos.y > ButtonLayout[0].rect.y &&
                calcMouse.MousePos.y < ButtonLayout[i].rect.y + ButtonLayout[i].rect.height)
            {
                ButtonLayout[i].isHoverdedOver = true;
                m_currentlyOn = static_cast<unsigned int>(i);
                return true;
            }
        }
    }


    return false;
}






void LayoutManager::draw()
{
    if (m_fontLoaded != false)
    {
        calculatorScreen.drawCalcScreen();
        drawEquation();
        drawButtons();
        drawNumsAndSymbole();
        if (calcMouse.MousePos.x >= ButtonLayout[0].rect.x && isMouseTouchingButton() == true)
        {
            ButtonLayout[m_currentlyOn].color = M_HOVERCOLOR;
            m_hoverHappend = true;
            
        }else if(calcMouse.MousePos.x <= 402  && isMouseTouchingButton2() == true)
        {
            ButtonLayout[m_currentlyOn].color = M_HOVERCOLOR;
            m_hoverHappend = true;
        }
        else
        {
            if (m_hoverHappend)
                setBackDefualtColorAfterHover();
        }
    }
    else
    {
        DrawText("This Application relies on arial.tff", 100, 110, 30, WHITE);
        DrawText("very funny deleting it",230,150,30,WHITE);
        DrawText("well jokes on you I don't work now >:)",90,190,30,WHITE);
        DrawText("put the font back in",230,230,30,WHITE);

    }   
}

void LayoutManager::drawNumsAndSymbole()
{
        // right side drawing 
    {
            // numbers drawing

        // 0
        DrawTextEx(m_font, symboles::nums[0], {(ButtonLayout[19].rect.x + 17), (ButtonLayout[19].rect.y + 10)}, 30, 2, BLACK);

        // 1 2 3
        DrawTextEx(m_font, symboles::nums[1], {(ButtonLayout[5].rect.x + 18), (ButtonLayout[5].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[2], {(ButtonLayout[6].rect.x + 18), (ButtonLayout[6].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[3], {(ButtonLayout[7].rect.x + 17), (ButtonLayout[7].rect.y + 10)}, 30, 2, BLACK);

        // 4 5 6
        DrawTextEx(m_font, symboles::nums[4], {(ButtonLayout[10].rect.x + 18), (ButtonLayout[10].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[5], {(ButtonLayout[11].rect.x + 17), (ButtonLayout[11].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[6], {(ButtonLayout[12].rect.x + 17), (ButtonLayout[12].rect.y + 10)}, 30, 2, BLACK);

        // 7 8 9
        DrawTextEx(m_font, symboles::nums[7], {(ButtonLayout[14].rect.x + 18), (ButtonLayout[14].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[8], {(ButtonLayout[15].rect.x + 17), (ButtonLayout[15].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::nums[9], {(ButtonLayout[16].rect.x + 17), (ButtonLayout[16].rect.y + 10)}, 30, 2, BLACK);

        // constants drawings
        DrawTextEx(m_font, symboles::constants[0], {(ButtonLayout[0].rect.x + 17), (ButtonLayout[0].rect.y + 5)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::constants[1], {(ButtonLayout[18].rect.x + 18), (ButtonLayout[18].rect.y + 7)}, 30, 2, BLACK);

        // parenthesis drawing
        DrawTextEx(m_font, symboles::parenthesis[0], {(ButtonLayout[1].rect.x + 17), (ButtonLayout[1].rect.y + 8)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::parenthesis[1], {(ButtonLayout[2].rect.x + 19), (ButtonLayout[2].rect.y + 8)}, 30, 2, BLACK);

        // oprator drawings
        DrawTextEx(m_font, symboles::operators[0], {(ButtonLayout[21].rect.x + 16), (ButtonLayout[21].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[1], {(ButtonLayout[17].rect.x + 19), (ButtonLayout[17].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[2], {(ButtonLayout[8].rect.x + 20), (ButtonLayout[8].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[3], {(ButtonLayout[13].rect.x + 17), (ButtonLayout[13].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[4], {(ButtonLayout[3].rect.x + 12), (ButtonLayout[3].rect.y + 10)}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[5], {(ButtonLayout[22].rect.x + 17), (ButtonLayout[22].rect.y + (ButtonLayout[22].rect.height / 2.37f))}, 30, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[6], {(ButtonLayout[4].rect.x + 16), (ButtonLayout[4].rect.y + 10)}, 30, 2, BLACK);
        if (m_backspaceIconLoaded)
        {
            DrawTexture(m_backspaceTexture, static_cast<int>(ButtonLayout[9].rect.x + 6), static_cast<int>(ButtonLayout[9].rect.y + 16), WHITE);
        }
        else
        {
            DrawTextEx(m_font, "B", {(ButtonLayout[9].rect.x + 16), (ButtonLayout[9].rect.y + 10)}, 30, 2, BLACK);
        }

        // drawing point
        DrawTextEx(m_font, symboles::point, {(ButtonLayout[20].rect.x + 20), (ButtonLayout[20].rect.y - 12.5f)}, 50, 2, BLACK);
    }
  
        // drawing left side text
    {
        

        //first row
        DrawTextEx(m_font, symboles::deg, {(ButtonLayout[23].rect.x + 10), (ButtonLayout[23].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font, symboles::rad, {(ButtonLayout[24].rect.x + 10), (ButtonLayout[24].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font, symboles::log, {(ButtonLayout[25].rect.x + 20), (ButtonLayout[25].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font, symboles::ln,  {(ButtonLayout[26].rect.x + 27), (ButtonLayout[26].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font, symboles::operators[7],{(ButtonLayout[27].rect.x + 28), (ButtonLayout[27].rect.y + 12)}, 36, 2, BLACK);



        // second row 

        DrawTextEx(m_font, symboles::xChar, {(ButtonLayout[28].rect.x + 30), (ButtonLayout[28].rect.y + 14)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[28].rect.x + 46), (ButtonLayout[28].rect.y + 12)}, 12, 2, BLACK);

        DrawTextEx(m_font, symboles::xChar, {(ButtonLayout[29].rect.x + 30), (ButtonLayout[28].rect.y + 14)}, 26, 2, BLACK);
        DrawTextEx(m_font,"3", {(ButtonLayout[29].rect.x + 46), (ButtonLayout[29].rect.y + 12)}, 12, 2, BLACK);

        DrawTextEx(m_font, symboles::sqrt, {(ButtonLayout[30].rect.x + 28), (ButtonLayout[28].rect.y + 14)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::sqrt, {(ButtonLayout[31].rect.x + 28), (ButtonLayout[28].rect.y + 14)}, 26, 2, BLACK);
        DrawTextEx(m_font, "3", {(ButtonLayout[31].rect.x + 28), (ButtonLayout[28].rect.y + 12)}, 12, 2, BLACK);

        DrawTextEx(m_font, symboles::constants[2],{(ButtonLayout[32].rect.x + 28), (ButtonLayout[28].rect.y + 10)}, 26, 2, BLACK);





        //thrid row

        DrawTextEx(m_font, symboles::sinFuncs[0], {(ButtonLayout[33].rect.x + 20), (ButtonLayout[33].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::sinFuncs[0], {(ButtonLayout[34].rect.x + 19), (ButtonLayout[33].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[34].rect.x + 51), (ButtonLayout[34].rect.y + 12)}, 12, 2, BLACK);
        
        DrawTextEx(m_font, symboles::sinFuncs[1], {(ButtonLayout[35].rect.x + 13), (ButtonLayout[33].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::sinFuncs[1], {(ButtonLayout[36].rect.x + 12), (ButtonLayout[33].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[36].rect.x + 58), (ButtonLayout[34].rect.y + 12)}, 12, 2, BLACK);
         
        DrawTextEx(m_font, symboles::sinFuncs[2], {(ButtonLayout[37].rect.x + 13), (ButtonLayout[33].rect.y + 12)}, 26, 2, BLACK);

        //forth row

        DrawTextEx(m_font, symboles::cosFuncs[0], {(ButtonLayout[38].rect.x + 18), (ButtonLayout[38].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::cosFuncs[0], {(ButtonLayout[39].rect.x + 17), (ButtonLayout[38].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[39].rect.x + 54), (ButtonLayout[38].rect.y + 12)}, 12, 2, BLACK);


        DrawTextEx(m_font, symboles::cosFuncs[1], {(ButtonLayout[40].rect.x + 11), (ButtonLayout[40].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::cosFuncs[1], {(ButtonLayout[41].rect.x + 9), (ButtonLayout[40].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[41].rect.x + 59), (ButtonLayout[41].rect.y + 10)}, 12, 2, BLACK);
         
        DrawTextEx(m_font, symboles::cosFuncs[2], {(ButtonLayout[42].rect.x + 11), (ButtonLayout[40].rect.y + 12)}, 26, 2, BLACK);
        
        
        
        //fifth row

        DrawTextEx(m_font, symboles::tanFuncs[0], {(ButtonLayout[43].rect.x + 20), (ButtonLayout[43].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::tanFuncs[0], {(ButtonLayout[44].rect.x + 19), (ButtonLayout[43].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[44].rect.x + 53), (ButtonLayout[44].rect.y + 12)}, 12, 2, BLACK);


        DrawTextEx(m_font, symboles::tanFuncs[1], {(ButtonLayout[45].rect.x + 11), (ButtonLayout[43].rect.y + 12)}, 26, 2, BLACK);
        
        DrawTextEx(m_font, symboles::tanFuncs[1], {(ButtonLayout[46].rect.x + 9), (ButtonLayout[43].rect.y + 12)}, 26, 2, BLACK);
        DrawTextEx(m_font,"2", {(ButtonLayout[46].rect.x + 56), (ButtonLayout[43].rect.y + 11)}, 12, 2, BLACK);
         
        DrawTextEx(m_font, symboles::tanFuncs[2], {(ButtonLayout[47].rect.x + 11), (ButtonLayout[43].rect.y + 13)}, 26, 2, BLACK);
        

    }


}










void LayoutManager::setBackDefualtColorAfterHover()
{
    /*

            DB | DB | DB | DB | RED
            CY | CY | CY | DB | ORG
            CY | CY | CT | DB |
            CY | CY | CT | DB |
            CY | CY | CT | DB |  DB

            0   |   1   |    2   |   3     |   4

            5   |   6   |    7   |   8     |   9

            10  |  11   |   12   |   13    |

            14  |  15   |   16   |   17    |   22

            18  |  19   |   20   |   21    |

    */

    for (size_t i = 0; i <= ButtonLayout.size(); i++)
    {

        if (i == 4)
        {
            ButtonLayout[i].color = {192, 2, 22, 255};
        }
        else if (i == 9)
        {
            ButtonLayout[i].color = {254, 173, 76, 255}; // orangeish color
        }
        else if (i <= 3 || i == 8 || i == 13 || i == 17 || i == 21 || i == 22)
        {
            ButtonLayout[i].color = M_DARKBLUE;
        }
        else if (i <= 7 || i <= 12 || i <= 16 || i <= 20)
        {
            ButtonLayout[i].color = BLUE;
        }else if(i <= 47)
        {
            if(i == 23 && parser.ismodeDeg){continue;}
            if(i == 24 && !parser.ismodeDeg){continue;}


            ButtonLayout[i].color = M_SILVER;
        }
    }
    m_hoverHappend = false;
}

void LayoutManager::checkInput()
{
    switch (m_currentlyOn)
    {
    case 0:
        if (calcMouse.leftClicked())
        {
            parser.pushConstants(input::constants::g);
        }
        break;
    case 1:
        if (calcMouse.leftClicked())
        {
            parser.pushparenthesis(input::parenthesis::openingPar);
        }
        break;
    case 2:
        if (calcMouse.leftClicked())
        {
            parser.pushparenthesis(input::parenthesis::closingPar);
        }
        break;
    case 3:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::model);
        }
        break;
    case 4:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::clear);
        }
        break;
    case 5:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("1");
        }
        break;
    case 6:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("2");
        }
        break;
    case 7:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("3");
        }
        break;
    case 8:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::division);
        }
        break;
    case 9:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::backspace);
        }
        break;
    case 10:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("4");
        }
        break;
    case 11:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("5");
        }
        break;
    case 12:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("6");
        }
        break;
    case 13:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::multiplication);
        }
        break;
    case 14:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("7");
        }
        break;
    case 15:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("8");
        }
        break;
    case 16:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("9");
        }
        break;
    case 17:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::subtraction);
        }
        break;
    case 18:
        if (calcMouse.leftClicked())
        {
            parser.pushConstants(input::constants::euler);
        }
        break;
    case 19:
        if (calcMouse.leftClicked())
        {
            parser.pushNumber("0");
        }
        break;
    case 20:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::point);
        }
        break;
    case 21:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::addition);
        }
        break;
    case 22:
        if (calcMouse.leftClicked())
        {
            parser.pushOperand(input::oprands::equals);
        }
        break;
    case 23:
        if (calcMouse.leftClicked())
        {
            if(!parser.ismodeDeg)parser.ismodeDeg = true;
            ButtonLayout[24].color = M_SILVER;  
        }
        break;
    case 24:
        if (calcMouse.leftClicked())
        {
            if(parser.ismodeDeg)parser.ismodeDeg = false;
            ButtonLayout[23].color = M_SILVER; 
        }
        break;
    case 25:
        if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::log); 
        }
        break;
    case 26:
        if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::ln); 
        }
        break;
    case 27:
        if (calcMouse.leftClicked())
        {
           parser.pushOperand(input::oprands::power); 
        }
        break;
    case 28:
        if (calcMouse.leftClicked())
        {
           parser.pushOperand(input::oprands::power);
           std::string temp = parser.returnEqAndInter();

           if(temp.empty() || temp[temp.length() - 1] != '^')return;
           else(parser.pushNumber("2"));
        }
        break;
    case 29:
        if (calcMouse.leftClicked())
        {
           parser.pushOperand(input::oprands::power);
           std::string temp = parser.returnEqAndInter();

           if(temp.empty() || temp[temp.length() - 1] != '^')return;
           else(parser.pushNumber("3"));
        }
        break;
    case 30: //root of 2
        if (calcMouse.leftClicked())
        {
           parser.pushOperand(input::oprands::power);
           std::string temp = parser.returnEqAndInter();

           if(temp.empty() || temp[temp.length() - 1] != '^')return;
           else(parser.pushNumber("0.5"));
        }
        break;
    case 31: // root of 3
        if (calcMouse.leftClicked())
        {
           parser.pushOperand(input::oprands::power);
           std::string temp = parser.returnEqAndInter();

           if(temp.empty() || temp[temp.length() - 1] != '^')return;
           else{
            parser.pushparenthesis(input::parenthesis::openingPar);
            parser.pushNumber("1");
            parser.pushOperand(input::oprands::division);
            parser.pushNumber("3");
            parser.pushparenthesis(input::parenthesis::closingPar);
            }
        }
        break;
    case 32:
        if (calcMouse.leftClicked())
        {
           parser.pushConstants(input::constants::pi);
        }
        break;
    case 33:
        if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::sin);
        }
        break;
    case 34:
        if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::sinsq);
        }
        break;
    case 35:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::asin);
        }
        break;
    case 36:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::asinsq);
        }
        break;
    case 37:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::sinh);
        }
        break;
    case 38:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::cos);
        }
        break;
    case 39:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::cossq);
        }
        break;
    case 40:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::acos);
        }
        break;
    case 41:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::acossq);
        }
        break;
    case 42:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::cosh);
        }
        break;
    case 43:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::tan);
        }
        break;
    case 44:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::tansq);
        }
        break;
    case 45:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::atan);
        }
        break;
    case 46:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::atansq);
        }
        break;
    case 47:
         if (calcMouse.leftClicked())
        {
           parser.pushFunction(input::function::trig::tanh);
        }
        break;
    default:
        break;
    }
    m_currentlyOn = 1000;
}

void LayoutManager::drawEquation()
{
    if (m_fontLoaded)
    {
        if (parser.result.empty())
        {
            Vector2 textSize = MeasureTextEx(m_font, (parser.returnEqAndInter()).c_str(), 30, 0);
            float x = calculatorScreen.screenRect.x + calculatorScreen.screenRect.width - 8 - textSize.x;
            float y = calculatorScreen.screenRect.y + 14;
            DrawTextEx(m_font, (parser.returnEqAndInter()).c_str(), {x, y}, 30, 0, WHITE);
        }
        else
        {
            Vector2 textSize = MeasureTextEx(m_font, (parser.result).c_str(), 30, 0);
            float x = calculatorScreen.screenRect.x + calculatorScreen.screenRect.width - 8 - textSize.x;
            float y = calculatorScreen.screenRect.y + 14;
            DrawTextEx(m_font, (parser.result).c_str(), {x, y}, 30, 0, WHITE);
            /* DrawTextEx(m_font, parser.result.c_str(), {calculatorScreen.screenRect.x + 8, calculatorScreen.screenRect.y + 16}, 30, 0, WHITE); */
        }
    }
    else if (!m_fontLoaded)
    {
        std::cout << "add defualt text to draw Equation function \n";
    }
}





CalcScreen::CalcScreen()
{
    topScreenRect.x = 15;
    topScreenRect.y = 15;
    topScreenRect.height = 50;
    topScreenRect.width = (window::windowWidth - 30);
    // screenRect

    screenRect.x = topScreenRect.x;
    screenRect.y = (topScreenRect.y * 4);
    screenRect.width = topScreenRect.width;
    screenRect.height = topScreenRect.height;
}

void CalcScreen::drawCalcScreen()
{
    DrawRectangleRounded(screenRect, 0.12f, 1, BLACK);
    DrawRectangleRounded(topScreenRect, 0.12f, 1, {38, 38, 38, 255});
}




LayoutManager::~LayoutManager()
{
    if (m_fontLoaded)
        UnloadFont(m_font);
    if (m_backspaceIconLoaded)
        UnloadTexture(m_backspaceTexture);
}




