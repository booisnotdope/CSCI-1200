#ifndef __POLYGONS_H_
#define __POLYGONS_H_

#include <vector>
#include <string>
#include <algorithm>

#include "utilities.h"

using namespace std;

#include "utilities.h"
class Polygon{
	public:
		Polygon(std::string aName, std::vector<Point> p) : name(aName), points(p) {
			bool eq = true;
			int dist = DistanceBetween(points[0], points[points.size()-1]);
			for(int i = 0; i < points.size()-1; i++){
			if(EqualSides((DistanceBetween(points[i], points[i+1])), dist) == false)
				eq = false;
			}
			equalsides = eq;
		}
		std::string getName(){return name;}
		virtual ~Polygon(){};
		
		bool HasAllEqualSides(){
			return equalsides;
		}
	protected:
		std::vector<Point> points;
		std::string name;
		bool equalsides;
};

class Quadrilateral: public Polygon{
public:
	Quadrilateral(std::string aName, std::vector<Point> p) : Polygon(aName, p){
		if(p.size() != 4){
			throw 1;
		}
	}
};

class Triangle: public Polygon{
public:
	Triangle(std::string aName, std::vector<Point> p) : Polygon(aName, p){
		
		if(p.size() != 3){
			throw 1;
		}
	}
};

class IsoscelesTriangle: public Triangle{
public:
	IsoscelesTriangle(std::string aName, std::vector<Point> p) : Triangle(aName, p){
		
		double side1 = DistanceBetween(p[0], p[1]);
		double side2 = DistanceBetween(p[1], p[2]);
		double side3 = DistanceBetween(p[0], p[2]);
		if(EqualSides(side1, side2) == false && EqualSides(side1, side3) == false&& EqualSides(side2, side3) == false){
			throw 1;
		}
	}
};

class EquilateralTriangle: public IsoscelesTriangle{
public:
	EquilateralTriangle(std::string aName, std::vector<Point> p) :IsoscelesTriangle(aName, p){

		double side1 = DistanceBetween(p[0], p[1]);
		double side2 = DistanceBetween(p[1], p[2]);
		double side3 = DistanceBetween(p[0], p[2]);
		if(EqualSides(side1, side2) == false || EqualSides(side1, side3) == false || EqualSides(side2, side3) == false){
			throw 1;
		}
		
		double ang1 = Angle(p[0], p[1], p[2]);
		double ang2 = Angle(p[1], p[2], p[0]);
		double ang3 = Angle(p[2], p[0], p[1]);
		if(EqualAngles(ang1, ang2) == false || EqualAngles(ang2, ang1) ==  false || EqualAngles(ang3, ang2) == false){
			throw 1;
		}
	}
};

class Rectangle: public Quadrilateral{
public:
	Rectangle(std::string aName, std::vector<Point> p) : Quadrilateral(aName, p){
		
		double ang1 = Angle(p[0], p[1], p[2]);
		double ang2 = Angle(p[1], p[2], p[3]);
		double ang3 = Angle(p[2], p[3], p[0]);
		double ang4 = Angle(p[3], p[0], p[1]);
		if(EqualAngles(ang1, ang2) ==  false || EqualAngles(ang2, ang3) == false ||
			EqualAngles(ang3, ang4) == false || EqualAngles(ang1, ang4) == false){
			throw 1;
		}

	}
};

class Square: public Rectangle{
public:
	Square(std::string name, std::vector<Point> p) : Rectangle(name, p){
		
		double side1 = DistanceBetween(p[0], p[1]);
		double side2 = DistanceBetween(p[1], p[2]);
		double side3 = DistanceBetween(p[2], p[3]);
		double side4 = DistanceBetween(p[0], p[3]);

		if(EqualSides(side1, side2) == false || EqualSides(side1, side3) == false ||
		 EqualSides(side2, side3) == false || EqualSides(side1, side4) == false){
			throw 1;
		}
	}
	
};

#endif