#include<iostream.h>
#include<graphics.h>
#include<conio.h>

struct point
{
	float x, y;
};

void drawaxis()
{
	int maxx=getmaxx();
	int maxy=getmaxy();
	int maxx_2=maxx/2;
	int maxy_2=maxy/2;
	line(maxx_2,0,maxx_2,maxy);
	line(0,maxy_2,maxx,maxy_2);
}

void putPixel(int x, int y)
{
	int maxx=getmaxx()/2;
	int maxy=getmaxy()/2;
	putpixel(x+maxx, maxy-y, YELLOW);
}

void main()
{
	point p1,p4;
	double r1,r4,t,step, xc, yc;
	cout<<"\nEnter endpoint 1: (x y) :: ";
	cin>>p1.x>>p1.y;
	cout<<"\nEnter endpoint 2: (x y) :: ";
	cin>>p4.x>>p4.y;
	cout<<"\nEnter tangent at P1 (R1) : ";
	cin>>r1;
	cout<<"\nEnter tangent at P2 (R2) : ";
	cin>>r4;

	cout<<"\nEnter stepsize : ";
	cin>>step;

	int gdriver=DETECT, gmode;
	initgraph(&gdriver, &gmode, "C://TURBOC3//BGI");
	drawaxis();
	for(t=0.0; t<=1.0; t+=step)
	{
	      double tsq=t*t, tcu=tsq*t;
	      xc=(2*tcu-3*tsq+1)*p1.x + (-2*tcu+3*tsq)*p4.x + (tcu-2*tsq+t)*r1 + (tcu-tsq)*r4;
	      yc=(2*tcu-3*tsq+1)*p1.y + (-2*tcu+3*tsq)*p4.y + (tcu-2*tsq+t)*r1 + (tcu-tsq)*r4;
	      putPixel((int)xc, (int)yc);
	}
	getch();

	closegraph();
}