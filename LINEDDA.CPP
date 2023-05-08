#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define ROUND(a) ((int)(a + 0.5))
void lineDDA(int xa, int ya, int xb, int yb)
{
    int dx = xb - xa, dy = yb - ya, steps, k;
    int xmax = getmaxx(), ymax = getmaxy();
    float xIncrement, yIncrement, x = xa, y = ya;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    xIncrement = dx / float(steps);
    yIncrement = dy / float(steps);
    putpixel(xmax / 2 + ROUND(x), ymax / 2 - ROUND(y), 255);
    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        putpixel(xmax / 2 + ROUND(x), ymax / 2 - ROUND(y), 255);
    }
}
int main(void)
{
    /* request auto detection */
    int gdriver = DETECT, gmode, errorcode;

    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
    lineDDA(0, 0, 100, 50);

    /* clean up */
    getch();
    closegraph();
    return 0;
}
