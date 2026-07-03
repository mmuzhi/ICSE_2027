import math

class AreaCalculator:

    def __init__(self, radius):
        self.radius = radius

    def calculate_circle_area(self):
        return math.pi * math.pow(self.radius, 2)

    def calculate_sphere_area(self):
        return 4 * math.pi * math.pow(self.radius, 2)

    def calculate_cylinder_area(self, height):
        return 2 * math.pi * self.radius * (self.radius + height)

    def calculate_sector_area(self, angle):
        return math.pow(self.radius, 2) * angle / 2

    def calculate_annulus_area(self, innerRadius, outerRadius):
        return math.pi * (math.pow(outerRadius, 2) - math.pow(innerRadius, 2))

def main():
    area_calculator = AreaCalculator(2.0)
    print('Circle Area:', area_calculator.calculateCircleArea())
    print('Sphere Area:', area_calculator.calculateSphereArea())
    print('Cylinder Area:', area_calculator.calculateCylinderArea(3.0))
    print('Sector Area:', area_calculator.calculateSectorArea(math.pi))
    print('Annulus Area:', area_calculator.calculateAnnulusArea(2.0, 3.0))
if __name__ == '__main__':
    main()