//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle height and width
#define PWIDTH 70
#define PHEIGHT 10

// brick height and width
#define BWIDTH 35 //2.5 px on each side
#define BHEIGHT 10

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);
 
    

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    double xvelocity = drand48()*3;
    double yvelocity = 2.0;
        
    
    

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
   

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
       
        //paddle
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event) - getWidth(paddle) /2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
        
        //ball
       
       
            move(ball, xvelocity, yvelocity);
            
            //horizontal movement
            if (getX(ball) + getWidth(ball) >= WIDTH)
            {
                xvelocity = -xvelocity;
            }
            
            else if (getX(ball) <= 0)
            {
                xvelocity = -xvelocity;
            }
            
            //vertical movement
            if (getY(ball) + getWidth(ball) >= HEIGHT)
            {
                yvelocity = -yvelocity;
            }
            
            else if (getY(ball) <= 0)
            {
                yvelocity = -yvelocity;
            }
            
            
        pause(10);
        
        //detect collision
        
      
            GObject object = detectCollision(window, ball);
            
            //paddle
            if (object == paddle)
            {
                // TODO
                yvelocity = -yvelocity;
            }
            
            //remove bricks
            if (object !=NULL && object !=paddle && object !=label)
            {   
                
                yvelocity = -yvelocity;
                //void removeGWindow(GWindow window, GRect brick);
                
                
                points++;
                updateScoreboard(window, label, points);
                removeGWindow(window, object);
            } 
            
            if (getY(ball) + getHeight(ball) >= getHeight(window))
            {
                //void removeGWindow(GWindow window, GOval ball);
                lives--;
                //removeGWindow(window, ball);
                setLocation(ball,(.5*WIDTH - 7), 510);
                setLocation(paddle, (.5*WIDTH - PWIDTH/2), 550);
                waitForClick();
                
            }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // TODO
    for(int i=0; i<= ROWS; i++)
    {
        for(int j=0; j<= COLS; j++)
        {
            
            GRect brick = newGRect((40*(j)+2.5), 15*i + 2.5, BWIDTH, BHEIGHT);
            setColor(brick, "Red");
            setFilled(brick, true);
            add(window, brick, "SOUTH");
            
            if(i==1)
            {
                setColor(brick, "Orange");
            }
            
            if(i==2)
            {
                setColor(brick, "Yellow");
            }
            
            if(i==3)
            {
                setColor(brick, "Green");
            }
            
            if(i==4)
            {
                setColor(brick, "Blue");
            }
            
            if(i==5)
            {
                setColor(brick, "Red");
            }
            
            if(i==6)
            {
                setColor(brick, "Orange");
            }

        }
       
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(.5*WIDTH - 7, 510, 14, 14);
    setColor(ball, "Black");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(.5*WIDTH - PWIDTH/2, 550, PWIDTH, PHEIGHT);
    setColor(paddle, "Black");
    setFilled(paddle, true);
    add(window, paddle, "SOUTH");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-50");
    setColor(label, "Pink");
    add(window, label);
    setLocation(label, (WIDTH/2 - .5*getWidth(label)), 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
