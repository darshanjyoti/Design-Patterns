/******************************************************************************
The Factory pattern is a creational pattern that provides an interface for 
creating objects without exposing the exact creation logic to the client. 

Instead of calling new directly, you delegate object creation to a factory 
function/class that decides which concrete class to instantiate.
Eg we have an inteface shape and many concrete classes like Circle
rectangle, square. Now client will not create new Circle(), instead 
it will call a factory class (often static) which will return an 
instance of circle.

*******************************************************************************/

#include <iostream>
#include <memory>
#include <string>

//interface
class Shape{
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};

//concrete classes

class Circle: public Shape{
public:
    void draw() const override 
    {
        std::cout<<"Circle"<<std::endl;
    }
    
};

class Square: public Shape{
public:
    void draw() const override 
    {
        std::cout<<"Square"<<std::endl;
    }
    
};

class Rectangle: public Shape{
public:
    void draw() const override 
    {
        std::cout<<"Rectangle"<<std::endl;
    }
    
};

//fcatory class

class shapeFactory{
public:
    static std::unique_ptr<Shape> createShape(const std::string& type)
    {
        if(type == "circle"){
            return std::make_unique<Circle>();
        }
        else if(type == "square"){
            return std::make_unique<Square>();
        }
        else if(type == "rectangle"){
            return std::make_unique<Rectangle>();
        }
        else{
            return nullptr;
        }
    }
};


int main()
{
    auto shape1 = shapeFactory::createShape("circle");
    auto shape2 = shapeFactory::createShape("square");
    auto shape3 = shapeFactory::createShape("triangle");
    
    if(shape1)
        shape1->draw();
    
    if(shape2)
        shape2->draw();
        
    if(shape3)
        shape3->draw();

    return 0;
}
