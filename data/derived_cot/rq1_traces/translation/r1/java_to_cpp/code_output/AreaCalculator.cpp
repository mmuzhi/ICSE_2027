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

    double calculateCircleArea() {
        return PI * std::pow(radius, 2);
    }

    double calculateSphereArea() {
        return 4 * PI * std::pow(radius, 2);
    }

    double calculateCylinderArea(double height) {
        return 2 * PI * radius * (radius + height);
    }

    double calculateSectorArea(double angle) {
        return std::pow(radius, 2) * angle / 2;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) {
        return PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    std::cout.precision(17);

    AreaCalculator areaCalculator(2);

    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(PI) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << std::endl;

    return 0;
}