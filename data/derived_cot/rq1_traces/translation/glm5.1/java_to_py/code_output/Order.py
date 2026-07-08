class Order:
    def __init__(self):
        self.menu = []
        self.selected_dishes = []
        self.sales = {}

    def add_dish(self, dish):
        if dish is None or "dish" not in dish or "price" not in dish or "count" not in dish:
            return False

        for menu_dish in self.menu:
            if dish.get("dish") == menu_dish.get("dish"):
                dish_count = int(dish.get("count"))
                menu_dish_count = int(menu_dish.get("count"))

                if menu_dish_count < dish_count:
                    return False
                else:
                    menu_dish["count"] = menu_dish_count - dish_count
                    self.selected_dishes.append(dish)
                    return True
        return False

    def calculate_total(self):
        total = 0.0
        for dish in self.selected_dishes:
            dish_name = dish.get("dish")
            price = float(dish.get("price"))
            count = int(dish.get("count"))
            sale = self.sales.get(dish_name, 1.0)
            total += price * count * sale
        return total

    def checkout(self):
        if not self.selected_dishes:
            return False
        total = self.calculate_total()
        self.selected_dishes.clear()
        return total