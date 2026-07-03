#include <iostream>
#include <cmath>

class AreaCalculator {
private:
    double radius;

public:
    AreaCalculator(double radius) : radius(radius) {}

    double calculateCircleArea() {
        return M_PI * std::pow(this->radius, 2);
    }

    double calculateSphereArea() {
        return 4 * M_PI * std::pow(this->radius, 2);
    }

    double calculateCylinderArea(double height) {
        return 2 * M_PI * this->radius * (this->radius + height);
    }

    double calculateSectorArea(double angle) {
        return std::pow(this->radius, 2) * angle / 2;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) {
        return M_PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);

    // Match Java's Double.toString() precision for identical output
    std::cout.precision(17);

    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << '\n';
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << '\n';
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << '\n';
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(M_PI) << '\n';
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << '\n';

    return 0;
}