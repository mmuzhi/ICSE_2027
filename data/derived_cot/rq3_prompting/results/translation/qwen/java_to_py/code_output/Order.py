from typing import List, Dict, Any, Union

class Order:
    def __init__(self):
        self.menu: List[Dict[str, Any]] = []
        self.selected_dishes: List[Dict[str, Any]] = []
        self.sales: Dict[str, float] = {}

    def add_dish(self, dish: Dict[str, Any]) -> bool:
        if dish is None or "dish" not in dish or "price" not in dish or "count" not in dish:
            return False
            
        dish_name = dish["dish"]
        dish_price = dish["price"]
        dish_count = dish["count"]
        
        for menu_dish in self.menu:
            if menu_dish["dish"] == dish_name:
                menu_dish_count = menu_dish["count"]
                if menu_dish_count < dish_count:
                    return False
                else:
                    menu_dish["count"] = menu_dish_count - dish_count
                    self.selected_dishes.append(dish)
                    return True
                    
        return False

    def calculate_total(self) -> float:
        total = 0.0
        for dish in self.selected_dishes:
            dish_name = dish["dish"]
            price = dish["price"]
            count = dish["count"]
            sale_multiplier = self.sales.get(dish_name, 1.0)
            total += price * count * sale_multiplier
        return total

    def checkout(self) -> Union[float, bool]:
        if not self.selected_dishes:
            return False
        total = self.calculate_total()
        self.selected_dishes.clear()
        return total