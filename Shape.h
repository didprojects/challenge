/**
 * @file Shape.h
 * @author Didi Liu
 * @date 09-12-2023
 * @brief This file contains the definition of the Shape class, Rectangle class, Circle class and Polygon class.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <string>

enum ShapeType{
    RECTANGLE = 1,
    CIRCLE,
    TRIANGLE,
    POLYGON
};

struct Point{
    float pX;
    float pY;
};

/**
 * @brief This class represents a Shape interface.
 * A shape has a type, a name, and can check if a particle is inside of the area.
 */
class Shape{
 public:
    virtual bool isPointInsideArea(Point p) = 0;
    ShapeType mType;
    std::string msAreaName;
};

/**
 * @brief This class is derived from Shape, represents a Rectangle.
 * A Rectangle has four vertices, can insert vertex.
 * Contains the implementation of function isPointInsideArea.
 */
class Rectangle : public Shape{
 public:
    bool isPointInsideArea(Point p);
    void insertVertex(Point p);
 private:
    std::vector<Point> mVertices;
};

/**
 * @brief This class is derived from Shape, represents a Triangle.
 * A Triangle has three vertices, can insert vertex.
 * Contains the implementation of function isPointInsideArea.
 */
class Triangle : public Shape{
 public:
    bool isPointInsideArea(Point p);
    void insertVertex(Point p);
 private:
    std::vector<Point> mVertices;
};

/**
 * @brief This class is derived from Shape, represents a Circle.
 * A circle has a center vertex and a radius.
 * Contains the implementation of function isPointInsideArea.
 */
class Circle : public Shape{
 public:
    bool isPointInsideArea(Point p);
    void setCenter(Point p);
    void setRadius(float r);
 private:
    Point mCenter;
    float mfRadius;
};

/**
 * @brief This class is derived from Shape, represents a Polygon.
 * A polygon has multiple vertices, can insert vertex.
 * Contains the implementation of function isPointInsideArea.
 */
class Polygon : public Shape{
 public:
    bool isPointInsideArea(Point p);
    void insertVertex(Point p);
 private:
    std::vector<Point> mVertices;
};

#endif
