#include "spl/gevents.h"
#include "spl/gwindow.h"

int main(void)
{
    GWindow window = newGWindow(320, 240);
    
    while(true)
    {
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_CLICKED) 
            {
                printf("%.0f, %.0f\n", getX(event), getY(event));
            }
        }
    }
}
