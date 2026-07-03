#include <iostream>
#include <cmath>

class AreaCalculator {
private:
    double radius;

public:
    AreaCalculator(double radius) : radius(radius) {}

    double calculateCircleArea() const {
        const double PI = std::acos(-1.0);
        return PI * std::pow(radius, 2);
    }

    double calculateSphereArea() const {
        const double PI = std::acos(-1.0);
        return 4 * PI * std::pow(radius, 2);
    }

    double calculateCylinderArea(double height) const {
        const double PI = std::acos(-1.0);
        return 2 * PI * radius * (radius + height);
    }

    double calculateSectorArea(double angle) const {
        return std::pow(radius, 2) * angle / 2.0;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) const {
        const double PI = std::acos(-1.0);
        return PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);

    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(std::acos(-1.0)) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << std::endl;

    return 0;
}