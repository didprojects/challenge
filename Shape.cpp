/**
 * @file Shape.cpp
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the implementation of the Shape class, Rectangle class, Circle class and Polygon class.
 */

#include "Shape.h"
#include <cmath>
#include <cfloat>

using namespace std;

#define THRESHOLD_MIN_VAL 0.00001  // Consider a result is 0 if it is less than THRESHOLD_MIN_VAL

// Check if the particle is on the side of the area
bool isPointOnLineSegment(Point point, Point lineStartPoint, Point lineEndPoint);
// Check if two given line segments intersect
bool isIntersect(Point lineAStartPoint, Point lineAEndPoint, Point lineBStartPoint, Point lineBEndPoint);

bool Rectangle::isPointInsideArea(Point p){
    int count = 0;

    float minX = DBL_MAX;
    for(int i = 0; i < mVertices.size(); i++){
        minX = min(minX, mVertices[i].pX);
    }

    // Cast a horizontal ray from point p
    Point linePoint1 = p;
    Point linePoint2 = p;
    // The end x value of the ray should be less than the smallest x value of the area
    linePoint2.pX = minX - 100; 

    for(int i = 0; i < mVertices.size(); i++){
        Point p1, p2;
        if(i <= mVertices.size() - 2){
            p1 = mVertices[i];
            p2 = mVertices[i+1];
        }else if(i == mVertices.size() - 1){
            p1 = mVertices[i];
            p2 = mVertices[0];
        }

        // If the particle is on the line segment of p1p2, it is inside of the area
        if(isPointOnLineSegment(p, p1, p2)){  
            return true;
        }

        // If the line segment p1p2 parallels with the particle ray, they don't intersect
        if(fabs(p1.pY - p2.pY) < THRESHOLD_MIN_VAL){
            continue; 
        } 
        
        // If the area vertex is on the particle ray, only consider the vertex with bigger y
        if(isPointOnLineSegment(p1, linePoint1, linePoint2)){
            if(p1.pY > p2.pY) count++;
        }else if(isPointOnLineSegment(p2, linePoint1, linePoint2)){
            if(p2.pY > p1.pY) count++;
        }
        // Check if the line segment p1p2 and the particle ray intersect
        else if(isIntersect(p1, p2, linePoint1, linePoint2)){
            count++;
        }
    }

    // If the number of the intersctions is odd, the particle is inside of the area
    if(count % 2 != 0) return true;
    else return false;
}

void Rectangle::insertVertex(Point p){
    mVertices.push_back(p);
}

bool Triangle::isPointInsideArea(Point p){
    int count = 0;

    float minX = DBL_MAX;
    for(int i = 0; i < mVertices.size(); i++){
        minX = min(minX, mVertices[i].pX);
    }

    // Cast a horizontal ray from point p
    Point linePoint1 = p;
    Point linePoint2 = p;
    // The end x value of the ray should be less than the smallest x value of the area
    linePoint2.pX = minX - 100;

    for(int i = 0; i < mVertices.size(); i++){
        Point p1, p2;
        if(i <= mVertices.size() - 2){
            p1 = mVertices[i];
            p2 = mVertices[i+1];
        }
        else if(i == mVertices.size() -1){
            p1 = mVertices[i];
            p2 = mVertices[0];
        }

        // If the particle is on the line segment of p1p2, it is inside of the area
        if(isPointOnLineSegment(p, p1, p2)){   
            return true;
        }

        // If the line segment p1p2 parallels with the particle ray, they don't intersect
        if(fabs(p1.pY - p2.pY) < THRESHOLD_MIN_VAL){ 
            continue;
        }

        // If the area vertex is on the particle ray, only consider the vertex with bigger y
        if(isPointOnLineSegment(p1, linePoint1, linePoint2)){
            if(p1.pY > p2.pY) count++;
        }else if(isPointOnLineSegment(p2, linePoint1, linePoint2)){
            if(p2.pY > p1.pY) count++;
        }
        // Check if the line segment p1p2 and the particle ray intersect
        else if(isIntersect(p1, p2, linePoint1, linePoint2)){
            count++;
        }
    }

    // The particle is inside of the area if the number of the intersctions is odd
    if(count % 2 != 0) return true;
    else return false;
}

void Triangle::insertVertex(Point p){
    mVertices.push_back(p);
}

// Calculate the distance between the particle and the circle center
bool Circle::isPointInsideArea(Point p){
    float distance = sqrt(pow(mCenter.pX - p.pX,2) + pow(mCenter.pY - p.pY,2));

    // The particle is inside of the area if the distance is equal to or less than the radius
    if(distance <= mfRadius) return true;
    return false;
}

void Circle::setCenter(Point p){
    mCenter = p;
}

void Circle::setRadius(float r){
    mfRadius = r;
}

bool Polygon::isPointInsideArea(Point p){
    int count = 0;

    float minX = DBL_MAX;
    for(int i = 0; i < mVertices.size(); i++){
        minX = min(minX, mVertices[i].pX);
    }

    // Cast a horizontal ray from point p
    Point linePoint1 = p;
    Point linePoint2 = p;
    // The end x value of the ray should be less than the smallest x value of the area
    linePoint2.pX = minX - 100;

    for(int i = 0; i < mVertices.size() - 1; i++){
        Point p1, p2;
        p1 = mVertices[i];
        p2 = mVertices[i+1];

        // If the particle is on the line segment of p1p2, it is inside of the area
        if(isPointOnLineSegment(p, p1, p2)){
            return true;
        }

        // If the line segment p1p2 parallels with the particle ray, they don't intersect
        if(fabs(p1.pY - p2.pY) < THRESHOLD_MIN_VAL){  
            continue;
        } 

        // If the area vertex is on the particle ray, only consider the vertex with bigger y
        if(isPointOnLineSegment(p1, linePoint1, linePoint2)){
            if(p1.pY > p2.pY) count++;
        }else if(isPointOnLineSegment(p2, linePoint1, linePoint2)){
            if(p2.pY > p1.pY) count++;
        }
        // Check if the line segment p1p2 and the particle ray intersect
        else if(isIntersect(p1, p2, linePoint1, linePoint2)){
            count++;
        }
    }

    // If the number of the intersctions is odd, the particle is inside of the area
    if(count % 2 != 0) return true;
    else return false; 
}

void Polygon::insertVertex(Point p){
    mVertices.push_back(p);
}

bool isPointOnLineSegment(Point point, Point lineStartPoint, Point lineEndPoint)
{
    float x,y,x1,x2,y1,y2;
    float crossProduct = 0.0;
    x = point.pX;
    y = point.pY;
    x1 = lineStartPoint.pX;
    y1 = lineStartPoint.pY;
    x2 = lineEndPoint.pX;
    y2 = lineEndPoint.pY;

    // Calculate the cross product of vector pp1 and vector pp2
    crossProduct = (x1 - x)*(y2 - y) - (x2 - x)*(y1 -y);

    if(abs(crossProduct) < THRESHOLD_MIN_VAL &&      // crossproduct is 0, means the particle is on the line p1p2
                       (x - x1)*(x - x2) < 0 &&      // x is between p1.x and p2.x
                       (y - y1)*(y - y2) < 0)        // y is between p1.y and p2.y
    {
        return true;
    }

    return false;
}

bool isIntersect(Point lineAStartPoint, Point lineAEndPoint, Point lineBStartPoint, Point lineBEndPoint)
{
    float px1,py1,px2,py2,px3,py3,px4,py4;
    px1 = lineAStartPoint.pX;
    py1 = lineAStartPoint.pY;
    px2 = lineAEndPoint.pX;
    py2 = lineAEndPoint.pY;
    px3 = lineBStartPoint.pX;
    py3 = lineBStartPoint.pY;
    px4 = lineBEndPoint.pX;
    py4 = lineBEndPoint.pY;


    // p = p1 + t1*D1   Point on linesegment1   D1 = p2 - p1
    // p = p3 + t2*D2   Point on lingsegment2   D2 = p4 - p3
    // If the two line segments intersect, then t1 and t2 should be both between 0 and 1
	float d = -(px2 - px1) * (py4 - py3) + (py2 - py1) * (px4 - px3);

    if(d != 0){
        float t1 = ((py3 - py1) * (px4 - px3) - (px3 - px1) * (py4 - py3)) / d;
        float t2 = ((py3 - py1) * (px2 - px1) - (px3 - px1) * (py2 - py1)) / d;

        if ((t1 >= 0) && (t1 <= 1) && (t2 >= 0) && (t2 <= 1)){
            return true;
        }    
    } 
    
    return false;
}



