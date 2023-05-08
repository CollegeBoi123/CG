#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
typedef unsigned int outcode;
enum
{
    TOP = 0x1,
    BOTTOM = 0x2,
    RIGHT = 0x4,
    LEFT = 0x8
};
void drawline(int x1, int y1, int x2, int y2)
{
    int xmax = getmaxx(), ymax = getmaxy();
    line(xmax / 2, 0, xmax / 2, ymax);
    line(0, ymax / 2, xmax, ymax / 2);
    line(x1 + xmax / 2, ymax / 2 - y1, xmax / 2 + x2, ymax / 2 - y2);
}
outcode CompOutCode(double x, double y, double xmin, double xmax, double ymin, double ymax)
{
    outcode code = 0;
    if (y > ymax)
        code |= TOP;
    else if (y < ymin)
        code |= BOTTOM;
    if (x > xmax)
        code |= RIGHT;
    else if (x < xmin)
        code |= LEFT;
    return code;
}
void cohenSutherLandLineClipAndDraw(double x0, double y0, double x1, double y1, double xmin, double xmax, double ymin, double ymax)
{
    outcode outcode0, outcode1, outcodeOut;
    double x, y;
    int accept = 0, done = 0;
    outcode0 = CompOutCode(x0, y0, xmin, xmax, ymin, ymax);
    outcode1 = CompOutCode(x1, y1, xmin, xmax, ymin, ymax);
    do
    {
        if (!(outcode0 | outcode1))
        {
            accept = 1;
            done = 1;
        }
        else if (outcode0 & outcode1)
        {
            done = 1;
        }
        else
        {

            outcodeOut = outcode0 ? outcode0 : outcode1;
            if (outcodeOut & TOP)
            {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (outcodeOut & BOTTOM)
            {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (outcodeOut & RIGHT)
            {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else
            {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }
        }
        if (outcodeOut == outcode0)
        {
            x0 = x, y0 = y, outcode0 = CompOutCode(x0, y0, xmin, xmax, ymin, ymax);
        }
        else
        {
            x1 = x, y1 = y, outcode1 = CompOutCode(x1, y1, xmin, xmax, ymin, ymax);
        }
    } while (done == 0);
    if (accept)
    {

        drawline(x0, y0, x1, y1);
    }
}
int main(void)
{
    /* request auto detection */
    int gdriver = DETECT, gmode, errorcode;
    int xmax, ymax;

    /* initialize graphics and local variables */
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

    /* read result of initialization */
    errorcode = graphresult();
    /* an error occurred */
    if (errorcode != grOk)
    {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);
    }
    drawline(0, 0, 100, 100);
    drawline(20, 20, 80, 20);
    drawline(20, 20, 20, 80);
    drawline(20, 80, 80, 80);
    drawline(80, 20, 80, 80);

    getch();
    cleardevice();
    cohenSutherLandLineClipAndDraw(0, 0, 100, 100, 20, 80, 20, 80);
    drawline(20, 20, 80, 20);
    drawline(20, 20, 20, 80);
    drawline(20, 80, 80, 80);
    drawline(80, 20, 80, 80);

    /* clean up */
    getch();
    closegraph();
    return 0;
}
