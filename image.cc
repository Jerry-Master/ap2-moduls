#include <pngwriter.h>

#include <cmath>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;

using Point = pair<int, int>;
using Line = vector<Point>;
using Grid = vector<Line>;

int width = 4000;
int height = 4000;

// Plots a set of points in some colour
void plot(pngwriter& png, const Line& v, const vector<double>& colores = {1.0,0.0,0.0}){
	for (Point p : v) png.plot(p.first, p.second, colores[0], colores[1], colores[2]);
}
// Plots multiple lines
void plot(pngwriter& png, const Grid& v, const vector<double>& colores = {1.0,0.0,0.0}){
	for (Line l : v) plot(png, l, colores);
}
// Returns a vector with the points of a line described by Ax + By + C = 0
// All between the region that goes from (1,1) to (width, height) and with integer coefficients
Line line(double A, double B, double C){
	Line ret;
	if (A == 0 and B == 0) return Line();
	if (A == 0) {
		for (int x = 1; x <= width; x++) ret.push_back(pair<int,int>(x,(-C/B)));
	}else if (B == 0) {
		for (int y = 1; y <= height; y++) ret.push_back(pair<int,int>((-C/A),y));
	}else {
		int y = 1;
		for (int x = 1; (x <= width) and (y <= height); x++){
			y = (-A/B)*x - (C/B); 
			ret.push_back(pair<int,int>(x, y));
		}
	}
	return ret;
}
// Returns the line joining two points
Line line(Point P, Point Q){
	int A = P.second - Q.second;
	int B = Q.first - P.first;
	return line(A, B, - B*P.second - A*P.first);
}
// Returns the segment joining two points
Line segment(Point P, Point Q){
	double A = P.second - Q.second;
	double B = Q.first - P.first;
	double C = - B*P.second - A*P.first;
	if (A == 0 and B == 0) return Line();

	int x_min = min(P.first, Q.first);
	int x_max = max(P.first, Q.first);
	int y_min = min(P.second, Q.second);
	int y_max = max(P.second, Q.second);
	Line ret;
	if (A == 0) {
		for (int x = x_min; x <= x_max; x++) ret.push_back(pair<int,int>(x,y_min));
	}else if (B == 0) {
		for (int y = y_min; y <= y_max; y++) ret.push_back(pair<int,int>(x_min,y));
	}else {
		int y = 1;
		for (int x = x_min; (x <= x_max) and (y <= y_max); x++){
			y = (-A/B)*x - (C/B); 
			ret.push_back(pair<int,int>(x, y));
		}
	}
	return ret;
}
// Creates a grid in the margins given
Grid grid(int dist){
	Grid g;
	Line l;
	for (int y = 1; y <= height; y+=dist){
		l = line(0,1,-y);
		g.push_back(l);
	}
	for (int x = 1; x <= width; x+=dist){
		l = line(1,0,-x);
		g.push_back(l);
	}
	return g;
}
// It represents f(z) = z^2 in the complex plane
void func(Point& p){
	int x = p.first;
	int y = p.second;
	// Move the center
	x -= width/2;
	y -= height/2;

	complex<int> z(x,y);
	z = z*z;

	int scale = 500;
	p.first = z.real()/scale + width/2;
	p.second = z.imag()/scale + height/2;
}
// Computes the euclidean norm
double norm(Point P, Point Q){
	int x = P.first - Q.first;
	int y = P.second - Q.second;
	return x*x + y*y;
}
// Searches the nearest point to one given and puts it next to it in the vector
// Prec: Behind the position i the order is fine
void put_nearest_next(Line& l, int i){
	if (i < l.size() - 1){
		double minim = norm(l[i],l[i+1]);
		int min_pos = i+1;
		for (int ii = i+2; ii < l.size(); ii++){
			if (norm(l[i], l[ii]) < minim) {
				minim = norm(l[i], l[ii]);
				min_pos = ii;
			}
		}
		swap(l[i+1], l[min_pos]);
	}
}
// Joins two lines adding the points of one to another saving the result in the first
void concatenate(Line& l1, const Line& l2){
	for (auto x : l2) l1.push_back(x);
}
// Joins the missing lines between separated points, but only join one point to its nearest one
void fill(Line& l){
	Line added;
	for (int i = 0; i < l.size(); i++){
		put_nearest_next(l,i);
		if (norm(l[i], l[i+1]) < 6000) concatenate(added,segment(l[i], l[i+1]));
	}
	concatenate(l, added);
}
// Applies a function to every point in the grid
void apply(Grid& g){
	for (Line& l : g) {
		for (Point& p : l) func(p);
		fill(l);
	}
}

int main() {
    pngwriter image(width, height, 1.0, "image.png");
	Grid g = grid(50);
	apply(g);
	image.invert();
	plot(image, g, {0.6,0.5,0.9});
	image.close();
}
