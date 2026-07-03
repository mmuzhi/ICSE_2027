class Dish:
    def __init__(self, dish_name, price, count):
        self.dish = dish_name
        self.price = price
        self.count = count

class Order:
    def __init__(self):
        self.menu = {}  # Using dict for O(1) lookups
        self.selected_dishes = []
        self.sales = {}  # Discount factors

    def add_dish(self, dish):
        # Check if dish exists in menu and has sufficient stock
        if dish.dish in self.menu:
            menu_dish = self.menu[dish.dish]
            if menu_dish.count < dish.count:
                return False
            menu_dish.count -= dish.count
            self.selected_dishes.append(dish)
        else:
            # Dish not found in menu
            return False
        return True

    def calculate_total(self):
        total = 0
        for dish in self.selected_dishes:
            discount = self.sales.get(dish.dish, 1.0)
            total += dish.price * dish.count * discount
        return total

    def checkout(self):
        if not self.selected_dishes:
            return 0.0
        total = self.calculate_total()
        self.selected_dishes.clear()
        return total