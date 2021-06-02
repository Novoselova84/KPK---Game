#include "TXLib.h"

const int SleepTime = 10;

void MoveBall ();

void DrawTextOutput (int x);

int main ()
    {
    txCreateWindow (1200, 800);

    txSetFillColor (RGB (32, 255, 35));

    txClear ();

    MoveBall ();

    return 0;
    }

void MoveBall ()
    {
    int x  = 300, y  = 100, r = 30,
        vx =   7, vy =   5,
        ax =   0, ay =   1;

    int dt = 1;

    int nCollisions = 0;

    txSetColor (TX_LIGHTGREEN, 2);
    txSetFillColor(TX_GREEN);

    txSetTextAlign (TA_BASELINE);
    txSelectFont ("Times", 60);


    while (! txGetAsyncKeyState (VK_LBUTTON))
        {
        DrawTextOutput (x);

        txRectangle (5, 0, 300, 30);
        printf (" Кол-во ударов = %d\r", nCollisions);

        txSetColor     (RGB (x, y, 128), 10);
        txSetFillColor (RGB (x/2, y/2, 128));

        txCircle (x, y, r);

        txLine (x, y, x + vx*5, y + vy*5);
        txCircle (x + vx*5, y + vy*5, 3);

        vx += ax * dt;
        vy += ay * dt;

        x += vx * dt;
        y += vy * dt;

        if (x > 1200 - r)
            {
            vx = - vx;
            x = 1200 - r;

            nCollisions ++;
            }

        if (y > 800 - r)
            {
            vy = - vy;
            y = 800 - r;

            nCollisions ++;
            }

        if (x < 0 + r)
            {
            vx = - vx;
            x = 0 + r;

            nCollisions ++;
            }

        if (y < 0 + r)
            {
            vy = - vy;
            y = 0 + r;

            nCollisions ++;
            }

        if (txGetAsyncKeyState (VK_RIGHT)) vx ++;
        if (txGetAsyncKeyState (VK_LEFT))  vx --;
        if (txGetAsyncKeyState (VK_UP))    vy ++;
        if (txGetAsyncKeyState (VK_DOWN))  vy --;
        if (txGetAsyncKeyState (VK_SPACE)) vx = vy = 0;

        txSleep (SleepTime);
        }
    }

void DrawTextOutput (int x)
    {
    char strX[20] = "";
    sprintf (strX, "x = %d", x);

    int centrX = 1090,
        centrY =   50;

    int textSizeX = txGetTextExtentX ("x = 0000"),
        textSizeY = txGetTextExtentY ("x = 0000");

    txSetColor (TX_YELLOW, 3);
    txSetFillColor (TX_BLACK);
    txRectangle (centrX - textSizeX/2 - 10, centrY - textSizeY/2 - 10, centrX + textSizeX/2 + 10, centrY + textSizeY/2 + 10);
    txDrawText  (centrX - textSizeX/2 - 10, centrY - textSizeY/2 - 10, centrX + textSizeX/2 + 10, centrY + textSizeY/2 + 10, strX);
    }
