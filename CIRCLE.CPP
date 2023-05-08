#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
void circlePlotPoint(int xc,int yc,int x,int y)
{
    int xmax = getmaxx()/2, ymax = getmaxy()/2;
    putpixel(xmax+(xc+x),ymax-(yc+y),255);
    putpixel(xmax+(xc-x),ymax-(yc+y),255);
    putpixel(xmax+(xc+x),ymax-(yc-y),255);
    putpixel(xmax+(xc-x),ymax-(yc-y),255);
    putpixel(xmax+(xc+y),ymax-(yc+x),255);
    putpixel(xmax+(xc-y),ymax-(yc+x),255);
    putpixel(xmax+(xc+y),ymax-(yc-x),255);
    putpixel(xmax+(xc-y),ymax-(yc-x),255);
}
void circleMidPoint(int xc,int yc, int radius)
{
    int x=0;
    int y=radius;
    int p=1-radius;
    circlePlotPoint(xc,yc,x,y);
    while(x<y)
    {
        x++;
        if(p<0)
        {
            p+=2*x+1;
        }
        else
        {
            y--;
            p+=2*(x-y)+1;
        }
        circlePlotPoint(xc,yc,x,y);
    }
}
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

   int xmax = getmaxx(), ymax = getmaxy();
   line(xmax / 2, 0, xmax / 2, ymax);
   line(0, ymax / 2, xmax, ymax / 2);
   circleMidPoint(0,0,100);
   /* clean up */
   getch();
   closegraph();
   return 0;
}
