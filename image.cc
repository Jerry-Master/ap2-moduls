#include <pngwriter.h>

#include <cmath>
#include <vector>
using namespace std;

using Point = pair<int, int>;

// Plots a set of points in some colour
void plot(pngwriter& png, const vector<Point>& v, vector<double> colores = {1.0,1.0,1.0}){
	for (Point p : v){
		png.plot(p.first, p.second, colores[0], colores[1], colores[2]);
	}
}

// Returns a vector with the points of a line described by Ax + By + C = 0
// All between the region that goes from (1,1) to (width, height) and with integer coefficients
vector<Point> line(double A, double B, double C, int width, int height){
	vector<Point> ret;
	if (A == 0) {
		
	}else if (B == 0) {
		
	}else {
		int y = 1;
		for (int x = 1; (x <= width) and (y <= height); x++){
			y = (-B/A)*x - (C/A); 
			ret.push_back(pair<int,int>(x, y));
		}
	}
	return ret;
}

int main() {
    pngwriter image(200, 300, 0.0, "image.png");
	vector<Point> r = line(1,1,0,200,300);
	
	plot(image, line);
	image.close();
}
