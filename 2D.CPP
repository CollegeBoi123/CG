#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <math.h>
void drawPolygon(int coordinate[], int size)
{
	cleardevice();
	int xmax = getmaxx(), ymax = getmaxy();
	line(xmax / 2, 0, xmax / 2, ymax);
	line(0, ymax / 2, xmax, ymax / 2);
	for (int i = 0; i < size; i = i + 2)
		line(xmax / 2 + coordinate[i % size], ymax / 2 - coordinate[(i + 1) % size], xmax / 2 + coordinate[(i + 2) % size], ymax / 2 - coordinate[(i + 3) % size]);
	getch();
}
void translate(int coordinate[], int size, int h, int k)
{

	for (int i = 0; i < size; i = i + 2)
	{
		coordinate[i] += h;
		coordinate[i + 1] += k;
	}
	// drawPolygon(coordinate,size);
}
void rotate(int coordinate[], int size, int x, int y, double angle)
{

	translate(coordinate, size, -x, -y);
	double rad_angle = angle * (M_PI / 180);
	for (int i = 0; i < size; i = i + 2)
	{
		// cout<<coordinate[i]<<"  "<<coordinate[i+1]<<endl;
		int x = (coordinate[i] * cos(rad_angle)) + ((-1) * coordinate[i + 1] * sin(rad_angle));
		int y = (coordinate[i] * sin(rad_angle)) + (coordinate[i + 1] * cos(rad_angle));
		// cout<<x<<"  "<<y<<endl;
		coordinate[i] = x;
		coordinate[i + 1] = y;
	}
	translate(coordinate, size, x, y);
}
void scale(int coordinate[], int size, int facx, int facy)
{
	drawPolygon(coordinate, size);
	for (int i = 0; i < size; i = i + 2)
		coordinate[i % size] *= facx, coordinate[(i + 1) % size] *= facy;
	drawPolygon(coordinate, size);
}
void reflection(int coordinate[], int size, int x1, int x2, int y1, int y2)
{

	int dx = x2 - x1, dy = y2 - y1;
	if (!dx)
	{
		// reflection about y-axis
		for (int i = 0; i < size; i = i + 2)
			coordinate[i] = -1 * coordinate[i];
	}
	else
	{
		double slope = dy / dx;
		int intercept = y1 - (slope * x1);
		translate(coordinate, size, 0, -1 * intercept);
		double angle = atan2(dy, dx) * (180 / M_PI);
		rotate(coordinate, size, 0, 0, -1 * angle);
		for (int i = 1; i < size; i = i + 2)
			coordinate[i] = -1 * coordinate[i];
		rotate(coordinate, size, 0, 0, angle);
		translate(coordinate, size, 0, intercept);
	}
}
int main(void)
{

	/* request auto detection */
	int gdriver = DETECT, gmode;
	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");

	cout << "Enter the number of points of polygon\n";
	int n;
	cin >> n;
	n = n * 2;
	int *coordinate = new int[n];
	cout << "Enter the coordinate as x then y:\n";
	for (int i = 0; i < n; i++)
	{
		cin >> coordinate[i];
	}
	int breakMenu = 1;
	do
	{
		cleardevice();
		cout << "            MENU                  \n";
		cout << "      1.Translate\n";
		cout << "      2.Scale\n";
		cout << "      3.Rotate\n";
		cout << "      4.Change the Polygon\n";
		cout << "      5.Reflection\n";
		cout << "      6.Exit\n";
		cout << "\n Enter you choice number\n";
		int choice;
		cin >> choice;
		switch (choice)
		{
		case 1:
			int h, k;
			cout << "Enter the magnitude by which you want to translate x and y respectively : \n";
			cin >> h >> k;
			drawPolygon(coordinate, n);
			translate(coordinate, n, h, k);
			drawPolygon(coordinate, n);
			break;
		case 2:
			cout << "Enter the magnitude by which you want to scale x and y respectively : \n";
			cin >> h >> k;
			drawPolygon(coordinate, n);
			scale(coordinate, n, h, k);
			drawPolygon(coordinate, n);
			break;
		case 3:
			int x, y;
			cout << "Enter the points about to rotate\n";
			cin >> x >> y;
			double angle;
			cout << "Enter the angle by which to rotate\n";
			cin >> angle;
			drawPolygon(coordinate, n);
			rotate(coordinate, n, x, y, angle);
			drawPolygon(coordinate, n);
			break;
		case 4:
			cout << "Enter the number of points of polygon\n";
			cin >> n;
			n = n * 2;
			coordinate = new int[n];
			cout << "Enter the coordinate as x then y:\n";
			for (int i = 0; i < n; i++)
			{
				cin >> coordinate[i];
			}
			break;
		case 5:
			int x1, x2, y1, y2;
			cout << "Enter the points for the line x and y respectively:\n";
			cin >> x1 >> y1 >> x2 >> y2;
			drawPolygon(coordinate, n);
			reflection(coordinate, n, x1, x2, y1, y2);
			drawPolygon(coordinate, n);
			break;
		case 6:
			breakMenu = 0;
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	} while (breakMenu);

	getch();
	closegraph();
	return 0;
}
