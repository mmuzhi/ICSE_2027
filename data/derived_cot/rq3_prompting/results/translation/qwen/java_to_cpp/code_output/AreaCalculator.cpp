#include <cmath>
#include <iostream>

class AreaCalculator {
private:
    double radius;
    static constexpr double PI { std::acos(0.0) * 2.0 };

public:
    explicit AreaCalculator(double radius) : radius(radius) {}

    double calculateCircleArea() const {
        return PI * std::pow(radius, 2);
    }

    double calculateSphereArea() const {
        return 4 * PI * std::pow(radius, 2);
    }

    double calculateCylinderArea(double height) const {
        return 2 * PI * radius * (radius + height);
    }

    double calculateSectorArea(double angle) const {
        return std::pow(radius, 2) * angle / 2;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) const {
        return PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);
    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << '\n';
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << '\n';
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << '\n';
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(AreaCalculator::PI) << '\n';
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << '\n';
    return 0;
}