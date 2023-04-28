#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    int a, b, c;
public:
    Triangle(int a, int b, int c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
    int getPerimeter() {
        return round(a + b + c);
    }
    double getArea() {
        double s = (a + b + c) / 2.0;
        return round(sqrt(s * (s - a) * (s - b) * (s - c)) * 100) / 100;
    }
};

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    Triangle triangle(a, b, c);
    cout << triangle.getPerimeter() << endl;
    cout.precision(2);
    cout << fixed << triangle.getArea() << endl;
    return 0;
}