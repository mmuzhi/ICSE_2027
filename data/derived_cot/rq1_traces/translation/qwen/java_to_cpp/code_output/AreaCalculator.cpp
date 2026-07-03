#include <cmath>
#include <iostream>

class AreaCalculator {
private:
    double radius;

public:
    explicit AreaCalculator(double radius) : radius(radius) {}

    double calculateCircleArea() const {
        return M_PI * std::pow(radius, 2);
    }

    double calculateSphereArea() const {
        return 4 * M_PI * std::pow(radius, 2);
    }

    double calculateCylinderArea(double height) const {
        return 2 * M_PI * radius * (radius + height);
    }

    double calculateSectorArea(double angle) const {
        return std::pow(radius, 2) * angle / 2;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) const {
        return M_PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);

    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(M_PI) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << std::endl;

    return 0;
}