#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "DDA.h"
void lineBres(int xa, int ya, int xb, int yb)
{
   int dx = abs(xa - xb), dy = abs(ya - yb);
   int p = 2 * dy - dx;
   int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
   int x, y, xEnd;
   int xmax = getmaxx(), ymax = getmaxy();
   if (xa > xb)
   {
      x = xb;
      y = yb;
      xEnd = xa;
   }
   else
   {
      x = xa;
      y = ya;
      xEnd = xb;
   }
   putpixel(xmax / 2 + x, ymax / 2 - y, 255);
   while (x < xEnd)
   {
      x++;
      if (p < 0)
         p += twoDy;
      else
      {
         y++;
         p += twoDyDx;
      }
      putpixel(xmax / 2 + x, ymax / 2 - y, 255);
   }
}
int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode;

   /* initialize graphics and local variables */
   initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

   int xmax = getmaxx(), ymax = getmaxy();
   lineDDA(xmax / 2, 0, xmax / 2, ymax);
   lineDDA(0, ymax / 2, xmax, ymax / 2);
   lineBres(0, 0, 10, 10);
   /* clean up */
   getch();
   closegraph();
   return 0;
}
