
// A purely virtual function, also known as a pure virtual function, is a virtual 
// function in a base class that has no implementation and is meant to be overridden 
// by derived classes. It is declared by assigning the function the "pure virtual" 
// specifier "= 0". Classes that have one or more pure virtual functions are called 
// abstract classes and cannot be instantiated. They are meant to serve as a base 
// for other classes that derive from them and provide concrete implementations for 
// the pure virtual functions. Pure virtual functions allow for a form of "interface" 
// in C++, where a base class defines a set of functions that derived classes must 
// implement, but the base class itself does not provide any implementation.

#include <iostream>

class Animal {
public:
    virtual void makeSound() = 0; // Pure virtual function
};

class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Woof!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    animal1->makeSound(); // Output: "Woof!"
    animal2->makeSound(); // Output: "Meow!"

    return 0;
}