
#include "TXLib.h"

const int SleepTime = 20;

void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor);

void PhysicsBall (int* x, int* y, int r, int* vx, int* vy, int* ax, int* ay, int dt, int* nCollisions);

void ControlBall (int* vx, int* vy);

void DrawTextOutput (int x);

void MoveBall ();

int main ()
    {
    txCreateWindow (1200, 800);

    txSetFillColor (RGB (255, 40, 255));

    txClear ();

    MoveBall ();

    return 0;
    }

void MoveBall ()
    {
    int x1  = 100, y1  = 100, r1 = 50,
        vx1 =   5, vy1 =   3,
        ax1 =   0, ay1 =   1;

    int x2  = 300, y2  = 300, r2 = 30,
        vx2 =   6, vy2 =   4,
        ax2 =   0, ay2 =   1;

    int x3  = 800, y3  = 500, r3 = 20,
        vx3 =   7, vy3 =   5,
        ax3 =   0, ay3 =   1;

    int dt = 1;

    int nCollisions = 0;

    txSetTextAlign (TA_BASELINE);
    txSelectFont ("Times", 60);

    while (! txGetAsyncKeyState (VK_LBUTTON))
        {
        DrawTextOutput (x1);

        txRectangle (5, 0, 320, 30);
        printf (" Кол-во ударов = %d\r", nCollisions);

        DrawBall (x1, y1, r1, vx1, vy1, TX_BLUE,   TX_GREEN);
        DrawBall (x2, y2, r2, vx2, vy2, TX_CYAN,   TX_RED);
        DrawBall (x3, y3, r3, vx3, vy3, TX_ORANGE, TX_BLUE);

        PhysicsBall (&x1, &y1, r1, &vx1, &vy1, &ax1, &ay1, dt, &nCollisions);
        PhysicsBall (&x2, &y2, r2, &vx2, &vy2, &ax2, &ay2, dt, &nCollisions);
        PhysicsBall (&x3, &y3, r3, &vx3, &vy3, &ax3, &ay3, dt, &nCollisions);

        ControlBall (&vx1, &vy1);

        txSleep (SleepTime);
        }
    }

void DrawBall (int x, int y, int r, int vx, int vy, COLORREF color, COLORREF fillcolor)
    {
    txSetColor     (color, 2);
    txSetFillColor (fillcolor);

    txCircle (x, y, r);
    txLine (x, y, x + vx*5, y + vy*5);
    txCircle (x + vx*5, y + vy*5, 3);
    }

void PhysicsBall (int* x, int* y, int r, int* vx, int* vy, int* ax, int* ay, int dt, int* nCollisions)
    {
    *vx = *vx + *ax * dt;
    *vy = *vy + *ay * dt;

    *x = *x + *vx * dt;
    *y = *y + *vy * dt;

    if (*x > 1200 - r)
        {
        *vx = - *vx;
        *x  = 1200 - r;

        (*nCollisions) ++;
        }

    if (*y > 800 - r)
        {
        *vy = - *vy;
        *y  = 800 - r;

        (*nCollisions) ++;
        }

    if (*x < 0 + r)
        {
        *vx = - *vx;
        *x  = 0 + r;

        (*nCollisions) ++;
        }

    if (*y < 0 + r)
        {
        *vy = - *vy;
        *y = 0 + r;

        (*nCollisions) ++;
        }
    }

void ControlBall (int* vx, int* vy)
    {
    if (txGetAsyncKeyState (VK_RIGHT)) (*vx) ++;
    if (txGetAsyncKeyState (VK_LEFT))  (*vx) --;
    if (txGetAsyncKeyState (VK_UP))    (*vy) ++;
    if (txGetAsyncKeyState (VK_DOWN))  (*vy) --;

    if (txGetAsyncKeyState (VK_SPACE)) *vx = *vy = 0;
    }

void DrawTextOutput (int x)
    {
    char strX[20] = "";
    sprintf (strX, "x = %d", x);

    int centrX = 1090,
        centrY =   50;

    int textSizeX = txGetTextExtentX ("x = 000000"),
        textSizeY = txGetTextExtentY ("x = 000000");

    txSetColor (TX_YELLOW, 3);
    txSetFillColor (TX_BLACK);
    txRectangle (centrX - textSizeX/2 - 10, centrY - textSizeY/2 - 10, centrX + textSizeX/2 + 10, centrY + textSizeY/2 + 10);
    txDrawText  (centrX - textSizeX/2 - 10, centrY - textSizeY/2 - 10, centrX + textSizeX/2 + 10, centrY + textSizeY/2 + 10, strX);
    }
