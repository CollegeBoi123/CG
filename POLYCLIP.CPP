#include<graphics.h>
#include<conio.h>
#include<iostream.h>

struct Point 
{
	float x,y;
};

void drawLine(float x0, float y0, float x1, float y1)
{
	int max_x = getmaxx();
	int max_y = getmaxy();
	int max_x_2 = max_x / 2;
	int max_y_2 = max_y / 2;
	
	x0 = max_x_2 + x0;
	x1 = max_x_2 + x1;
	y0 = max_y_2 - y0;
	y1 = max_y_2 - y1;
	
	line(x0,y0,x1,y1);	
}

void drawPoly(Point *poly, int poly_size)
{
	for(int i = 0; i < poly_size; ++i)
	{
		int k = (i+1) % poly_size;
		drawLine(poly[i].x, poly[i].y, poly[k].x, poly[k].y);
	}
      getch();
}

// func. to check if a point lies on left of an edge
int inside(Point p, Point ep1, Point ep2)
{
	return (ep2.y - ep1.y)*p.x + (ep1.x - ep2.x)*p.y + (ep2.x*ep1.y - ep1.x*ep2.y) < 0;
}

Point intersection(Point v1, Point v2, Point ep1, Point ep2)
{
	Point ip;

	float n1 = v1.x*v2.y - v1.y*v2.x;
	float n2 = ep1.x*ep2.y - ep1.y*ep2.x;

	float num_x = n1 * (ep1.x - ep2.x) - n2 * (v1.x - v2.x);
	float num_y = n1 * (ep1.y - ep2.y) - n2 * (v1.y - v2.y);

	float den = (v1.x - v2.x) * (ep1.y - ep2.y) - (v1.y - v2.y) * (ep1.x - ep2.x);

	ip.x = num_x / den;
	ip.y = num_y / den;

	return ip;
}


Point* clip(Point *poly, int &poly_size, Point ep1, Point ep2)
{
	Point *result = new Point[20];
	int counter = 0;

	for(int i = 0; i < poly_size; ++i)
	{

		Point C = poly[i];
		int Cin = inside(C, ep1, ep2);
		Point D = poly[(i+1) % poly_size];

		int Din = inside(D, ep1, ep2);

		if(Din != Cin)
			result[counter++] = intersection(C, D, ep1, ep2);

		if(Din)
			result[counter++] = D;
	}

	poly_size = counter;

	return result;
}

void sutherlandHogdmanPolyClip(Point *poly, int poly_size, Point *clipPoly, int clipPoly_size)
{

	for(int i = 0; i < clipPoly_size; i++)
	{
		int k = (i+1) % clipPoly_size;
		poly = clip(poly, poly_size, clipPoly[i], clipPoly[k]);

	}

	drawPoly(poly, poly_size);
}

int main()
{
	int gd = DETECT, gm;
	initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

	int max_x = getmaxx();
	int max_y = getmaxy();
	int max_x_2 = max_x / 2;
	int max_y_2 = max_y / 2;

	int xmin = 50;
	int ymin = 50;
	int xmax = 150;
	int ymax = 150;

	
	Point *clipPoly = new Point[4];
	clipPoly[0].x =xmin;
	clipPoly[0].y=ymin;
	clipPoly[1].x=xmax;
	clipPoly[1].y=ymin;
	clipPoly[2].x = xmax;
	clipPoly[2].y=ymax;
	clipPoly[3].x = xmin;
	clipPoly[3].y=ymax;

	int clipPoly_size = 4;
	cout<<"Enter the vertices : \n";
	int poly_size;
      cin>>poly_size;
	Point *poly = new Point[poly_size];
	cout<<"Enter the coordinates of vertices: \n";
	for(int i = 0; i < poly_size; ++i)
	{
		cin>>poly[i].x>>poly[i].y;
	}
      cleardevice();
	line(max_x_2,0,max_x_2,max_y);
	line(0,max_y_2,max_x,max_y_2);
      rectangle(max_x_2 + xmin, max_y_2 - ymax, max_x_2 + xmax, max_y_2 - ymin);
	drawPoly(poly, poly_size);
      cleardevice();
      line(max_x_2,0,max_x_2,max_y);
	line(0,max_y_2,max_x,max_y_2);
      rectangle(max_x_2 + xmin, max_y_2 - ymax, max_x_2 + xmax, max_y_2 - ymin);
	sutherlandHogdmanPolyClip(poly, poly_size, clipPoly, clipPoly_size);

	getch();
	closegraph();
	return 0;
}


