#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define ROUND(a) ((int)(a + 0.5))

int xmax = getmaxx();
int ymax = getmaxy();

void ellipsePlotPoints(int, int, int, int);

void ellipseMidPoint(int xc, int yc, int rx, int ry)
{
   int rx2 = rx * rx, ry2 = ry * ry, tworx2 = 2 * rx2, twory2 = 2 * ry2;
   int p;
   int x = 0, y = ry, px = 0, py = tworx2 * y;

   ellipsePlotPoints(xc, yc, 4*x, 4*y);

   p = ROUND(ry2 - (rx2 * ry) + (0.25 * rx2));
   while (px < py)
   {
      x++;
      px += twory2;
      if (p < 0)
      {
	 p += ry2 + px;
      }
      else
      {
	 y--;
	 py -= tworx2;
	 p += ry2 + px - py;
      }
      ellipsePlotPoints(xc, yc, 4*x,4*y);
   }

   p = ROUND(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);
   while (y > 0)
   {
      y--;
      py -= tworx2;
      if (p > 0)
	 p += rx2 - py;
      else
      {
	 x++;
	 px += twory2;
	 p += rx2 - py + px;
      }
      ellipsePlotPoints(xc, yc,4*x,4*y);
   }
}

void ellipsePlotPoints(int xc, int yc, int x, int y)
{
   putpixel(xc + x, yc + y, 255);
   putpixel(xc - x, yc + y, 255);
   putpixel(xc + x, yc - y, 255);
   putpixel(xc - x, yc - y, 255);
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

   setcolor(getmaxcolor());
   xmax = getmaxx();
   ymax = getmaxy();

   // draw a diagonal
   ellipseMidPoint(xmax/2,ymax/2, 35,12);
   /* clean up */
   getch();
   closegraph();
   return 0;
}
