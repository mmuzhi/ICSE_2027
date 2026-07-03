#include <cmath>
#include <iostream>

class AreaCalculator {
private:
    double radius;

public:
    explicit AreaCalculator(double radius) : radius(radius) {}

    double calculate_circle_area() const {
        return M_PI * std::pow(radius, 2);
    }

    double calculate_sphere_area() const {
        return 4 * M_PI * std::pow(radius, 2);
    }

    double calculate_cylinder_area(double height) const {
        return 2 * M_PI * radius * (radius + height);
    }

    double calculate_sector_area(double angle) const {
        return std::pow(radius, 2) * angle / 2;
    }

    double calculate_annulus_area(double innerRadius, double outerRadius) const {
        return M_PI * (std::pow(outerRadius, 2) - std::pow(innerRadius, 2));
    }
};

int main() {
    AreaCalculator areaCalculator(2);

    std::cout << "Circle Area: " << areaCalculator.calculate_circle_area() << std::endl;
    std::cout << "Sphere Area: " << areaCalculator.calculate_sphere_area() << std::endl;
    std::cout << "Cylinder Area: " << areaCalculator.calculate_cylinder_area(3) << std::endl;
    std::cout << "Sector Area: " << areaCalculator.calculate_sector_area(M_PI) << std::endl;
    std::cout << "Annulus Area: " << areaCalculator.calculate_annulus_area(2, 3) << std::endl;

    return 0;
}