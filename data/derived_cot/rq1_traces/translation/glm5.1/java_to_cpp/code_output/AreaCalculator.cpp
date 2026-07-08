#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

class AreaCalculator {
private:
    // Match Java's Math.PI exact value
    static constexpr double PI = 3.141592653589793;
    double radius;

public:
    AreaCalculator(double radius) : radius(radius) {}

    double calculateCircleArea() const {
        return PI * std::pow(this->radius, 2);
    }

    double calculateSphereArea() const {
        return 4 * PI * std::pow(this->radius, 2);
    }

    double calculateCylinderArea(double height) const {
        return 2 * PI * this->radius * (this->radius + height);
    }

    double calculateSectorArea(double angle) const {
        return std::pow(this->radius, 2) * angle / 2;
    }

    double calculateAnnulusArea(double innerRadius, double outerRadius) const {
        return PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);

    // Set precision to match Java's Double.toString() output precision
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
    
    std::cout << "Circle Area: " << areaCalculator.calculateCircleArea() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculateSphereArea() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculateCylinderArea(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculateSectorArea(AreaCalculator::PI) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculateAnnulusArea(2, 3) << std::endl;

    return 0;
}