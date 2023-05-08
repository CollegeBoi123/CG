#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define ROUND(a) ((int)(a + 0.5))
void lineDDA(int xa, int ya, int xb, int yb)
{
    int dx = xb - xa, dy = yb - ya, steps, k;
    float xIncrement, yIncrement, x = xa, y = ya;
    if (abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    xIncrement = dx / float(steps);
    yIncrement = dy / float(steps);
    putpixel(ROUND(x), ROUND(y), 255);
    for (k = 0; k < steps; k++)
    {
        x += xIncrement;
        y += yIncrement;
        putpixel(ROUND(x), ROUND(y), 255);
    }
}