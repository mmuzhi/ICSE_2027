#include <iostream>
#include <cmath>

namespace {
    const double PI = 3.141592653589793;
}

class AreaCalculator {
private:
    double radius;

public:
    AreaCalculator(double radius) : radius(radius) {}

    double calculate_circle_area() {
        return PI * std::pow(radius, 2);
    }

    double calculate_sphere_area() {
        return 4 * PI * std::pow(radius, 2);
    }

    double calculate_cylinder_area(double height) {
        return 2 * PI * radius * (radius + height);
    }

    double calculate_sector_area(double angle) {
        return std::pow(radius, 2) * angle / 2;
    }

    double calculate_annulus_area(double innerRadius, double outerRadius) {
        return PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    std::cout.precision(17);

    AreaCalculator areaCalculator(2);

    std::cout << "Circle Area: " << areaCalculator.calculate_circle_area() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculate_sphere_area() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculate_cylinder_area(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculate_sector_area(PI) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculate_annulus_area(2, 3) << std::endl;

    return 0;
}