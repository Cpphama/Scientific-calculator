#include "starter.h"
#include "windowMaker.h"
#include "applicationsConsts.h"
#include "buttons.h"


void start()
{

    Window win;
    win.windowInit();
    LayoutManager manager;
    manager.setButtonsInfo();


    while (WindowShouldClose() == false)
    {
        if(IsWindowResized())win.updateScale();
        
        // update mouse & check for clicks
        {
            manager.calcMouse.updateMouse();
            manager.checkInput();
        }
        
       
        win.drawInstructionToVirtualWindow({89,89,89,255});//draw here to 

        manager.draw();

        win.endOfInstructionToVirtualWindow();//here



        win.drawVirtualWindow(BLACK);
    }





    win.cleanUp();


}