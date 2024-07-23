
// A virtual function is a member function in a base class that can be redefined in a derived class, 
// and when called, the actual function that gets executed depends on the type of the object being 
// used at runtime.It allows for polymorphic behavior, where objects of different types that implement 
// the same virtual function can be used interchangeably.

#include <iostream>

class Shape {
public:
    virtual void draw() {
        std::cout << "Drawing a shape" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a rectangle" << std::endl;
    }
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing a circle" << std::endl;
    }
};

int main() {
    Shape* shape1 = new Rectangle();
    Shape* shape2 = new Circle();

    shape1->draw();
    shape2->draw();

    return 0;
}