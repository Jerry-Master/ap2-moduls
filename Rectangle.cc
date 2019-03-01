#include "Rectangle.hh"

#include <algorithm>
#include <cassert>
#include <cmath>
using namespace std;

#ifndef UNCERTAINTY
#define UNCERTAINTY 0.0001
#endif

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
void Rectangle::move_to (const Point& p) {
	this->p = p;
}

/** Compares this rectangle to rectangle r. */
bool Rectangle::operator== (const Rectangle& r) const {
	return (abs(w - r.width()) < UNCERTAINTY) and (abs(h - r.height()) < UNCERTAINTY) 
			and (p == r.get_LL());
}

/** Compares this rectangle to rectangle r. */
bool Rectangle::operator!= (const Rectangle& r) const {
	return not (r == *this);
}

/** Intersects this rectangle with another rectangle. 
	If they don't intersect, returns Rectangle(Point(0,0),0,0)*/
Rectangle& Rectangle::operator*= (const Rectangle& r) {
	/** Compute the x coord of the new LL and UR */
	double x_min = max(get_LL().get_x(), r.get_LL().get_x());
	double x_max = min(get_UR().get_x(), r.get_UR().get_x());
	/** Compute the y coord of the new LL and UR */
	double y_min = max(get_LL().get_y(), r.get_LL().get_y());
	double y_max = min(get_UR().get_y(), r.get_UR().get_y());
	
	double width = x_max - x_min;
	double height = y_max - y_min;
	if (width < 0 or height < 0) {
		p = Point(0,0);
		w = 0;
		h = 0;
	}else{
		p = Point(x_min, y_min);
		w = width;
		h = height;	
	}
	return *this;
}

/** Returns the intersection of this rectangle with another rectangle. */
Rectangle Rectangle::operator* (const Rectangle& r) const {
	Rectangle s = *this;
	s *= r;
	return s;
}

/** Rotates this rectangle 90 degrees clockwise or counterclockwise around its LL point. */
void Rectangle::rotate (bool clockwise) {
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
	p += Point(0,-h);
}

/** Vertically flips this rectangle around its LL point.*/
void Rectangle::flip_ver () {
	p += Point(-w,0);
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
	return contains(r.get_LL()) and contains(r.get_UR());
}

