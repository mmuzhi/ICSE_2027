#include <cmath>

class AreaCalculator {
private:
    double radius;

public:
    AreaCalculator(double radius) : radius(radius) {}

    double calculate_circle_area() {
        return M_PI * radius * radius;
    }

    double calculate_sphere_area() {
        return 4 * M_PI * radius * radius;
    }

    double calculate_cylinder_area(double height) {
        return 2 * M_PI * radius * (radius + height);
    }

    double calculate_sector_area(double angle) {
        return radius * radius * angle / 2.0;
    }

    double calculate_annulus_area(double inner_radius, double outer_radius) {
        return M_PI * (outer_radius * outer_radius - inner_radius * inner_radius);
    }
};