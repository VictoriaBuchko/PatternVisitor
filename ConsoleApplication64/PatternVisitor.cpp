#include <iostream>
#include <vector>
using namespace std;

class Square;
class Circle;
class Rectangle;


class Visitor {
public:
    virtual void visit(Square& square) = 0;
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
};


class Shape {
public:
    virtual void accept(Visitor& visitor) = 0;
};


class Square : public Shape {
public:
    Square(double side) : m_side(side) {}

    double area() const { return m_side * m_side; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    double getSide() const { return m_side; }

private:
    double m_side;
};

class Circle : public Shape {
public:
    Circle(double radius) : m_radius(radius) {}

    double area() const { return 3.14159265359 * m_radius * m_radius; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    double getRadius() const { return m_radius; }

private:
    double m_radius;
};

class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    double area() const { return m_width * m_height; }

    void accept(Visitor& visitor) override {
        visitor.visit(*this);
    }

    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }

private:
    double m_width;
    double m_height;
};


class PerimeterVisitor : public Visitor {
public:
    void visit(Square& square) override {
        m_perimeter += 4 * square.getSide();
    }

    void visit(Circle& circle) override {
        m_perimeter += 2 * 3.14159265359 * circle.getRadius();
    }

    void visit(Rectangle& rectangle) override {
        m_perimeter += 2 * (rectangle.getWidth() + rectangle.getHeight());
    }

    double perimeter() const { return m_perimeter; }

private:
    double m_perimeter = 0.0;
};


class DrawVisitor : public Visitor {
public:
    void visit(Square& square) override {
        int side = (int)square.getSide();

        cout << "Drawing square" << endl;
        for (int i = 0; i < side; i++) {
            for (int j = 0; j < side; j++) {
                cout << '*';
            }
            cout << endl;
        }
        cout << endl;
    }

    void visit(Circle& circle) override {
        cout << "Drawing circle\n" << endl;
    }

    void visit(Rectangle& rectangle) override {
        int width = (int)rectangle.getWidth();
        int height = (int)rectangle.getHeight();

        cout << "Drawing rectangle" << endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << '*';
            }
            cout << endl;
        }
        cout << endl;
    }

};


int main() {
    vector<Shape*> shapes = { new Square(3), new Circle(2), new Rectangle(4, 5) };

    PerimeterVisitor perimeterVisitor;
    for (auto shape : shapes) {
        shape->accept(perimeterVisitor);
    }

    cout << "Total perimeter: " << perimeterVisitor.perimeter() << endl;

    DrawVisitor drawVisitor;
    for (auto shape : shapes) {
        shape->accept(drawVisitor);
    }
    for (auto shape : shapes) {
        delete shape;
    }

    return 0;
}
