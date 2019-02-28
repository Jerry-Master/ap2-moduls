#include "Rectangle.hh"

#include <cassert>
using namespace std;


/** Constructor. */
Rectangle::Rectangle (double w, double h, const Point& p)
:   p(p),
    w(w),
    h(h)
{
    assert(w >= 0);
    assert(h >= 0);
}


/** Gets the LL (lower-left) point of this rectangle. */
Point Rectangle::get_LL () const {
    return p;
}


/** Gets the UR (upper-right) point of this rectangle. */
Point Rectangle::get_UR () const {
    return Point(p.get_x() + w, p.get_y() + h);
}


/** Gets the area of this rectangle. */
double Rectangle::area () const {
    return w * h;
}


/** Gets the width of this rectangle. */
double Rectangle::width () const {
    return w;
}


/** Gets the height of this rectangle. */
double Rectangle::height () const {
    return h;
}


// ***********************************************************
// Implement the rest of the Rectangle methods by yourself !!!
// ***********************************************************

/** Scales this rectangle with a factor s >= 0. */
void Rectangle::scale (double s) {
	w *= s;
	h *= s;
}

/** Moves the LL of this rectangle to some point p. */
void move_to (const Point& p) {
	this->p += p;
}

/** Compares this rectangle to rectangle r. */
bool Rectangle::operator== (const Rectangle& r) const {
	return (w == r.getWidth()) and (h == r.getWidth()) and (p == r.getLL());
}

/** Compares this rectangle to rectangle r. */
bool Rectangle::operator!= (const Rectangle& r) const {
	return not r == *this;
}

/** Intersects this rectangle with another rectangle. */
Rectangle& Rectangle::operator*= (const Rectangle& r) {
	double x_min = max(getLL().get_x(), r.getLL().get_x());
	double x_max = min(getUR().get_x(), r.getUR().get_x());
	
	double y_min = max(getLL().get_y(), r.getLL().get_y());
	double y_max = min(getUR().get_y(), r.getUR().get_y());
	
	double width = x_max - x_min;
	double height = y_max - y_min;
	if (width < 0 or height < 0) {
		p = Point(0,0);
		w = 0;
		h = 0;
	}else{
		
	}
		
}

/** Returns the intersection of this rectangle with another rectangle. */
Rectangle Rectangle::operator* (const Rectangle& r) const {
	Rectangle s = *this;
	s *= r;
	return s;
}

/** Rotates this rectangle 90 degrees clockwise or counterclockwise around its LL point. */
void Rectangle::rotate (bool clockwise=true) {
	if (clockwise) {
		p += Point(0,-w);
		swap(w,h);
	}else{
		p += Point(-h, 0);
		swap(w,h);
	}
}

/** Horizontally flips this rectangle around its LL point.*/
void Rectangle::flip_hor () {
	p += Point(-w,0);
}

/** Vertically flips this rectangle around its LL point.*/
void Rectangle::flip_ver () {
	p += Point(0,-h);
}

/** Check whether point p is contained in this rectangle. */
bool Rectangle::contains (const Point& p) const {
			// It is up and right to the LL
	return (this->p.get_x() <= p.get_x()) and (this->p.get_y() <= p.get_y()) 
			// It is down and left to the UR
	   and (this->p.get_x()+w >= p.get_x()) and (this->p.get_y()+h >= p.get_y());
}

/** Check whether rectangle r is fully contained in this rectangle. */
bool Rectangle::contains (const Rectangle& r) const {
	return contains(r.getLL()) and contains(r.getUR());
}

