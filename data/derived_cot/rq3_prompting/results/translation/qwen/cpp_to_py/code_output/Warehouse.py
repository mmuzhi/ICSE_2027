from typing import Dict

class Warehouse:
    def __init__(self):
        self.inventory: Dict[int, Dict[str, str]] = {}
        self.orders: Dict[int, Dict[str, str]] = {}

    def add_product(self, product_id: int, name: str, quantity: int) -> None:
        if product_id not in self.inventory:
            self.inventory[product_id] = {"name": name, "quantity": str(quantity)}
        else:
            current_quantity = int(self.inventory[product_id]["quantity"])
            self.inventory[product_id]["quantity"] = str(current_quantity + quantity)

    def update_product_quantity(self, product_id: int, quantity: int) -> None:
        if product_id in self.inventory:
            current_quantity = int(self.inventory[product_id]["quantity"])
            self.inventory[product_id]["quantity"] = str(current_quantity + quantity)

    def get_product_quantity(self, product_id: int) -> int:
        if product_id in self.inventory:
            return int(self.inventory[product_id]["quantity"])
        return 0

    def create_order(self, order_id: int, product_id: int, quantity: int) -> bool:
        available_quantity = self.get_product_quantity(product_id)
        if available_quantity >= quantity:
            self.update_product_quantity(product_id, -quantity)
            self.orders[order_id] = {
                "product_id": str(product_id),
                "quantity": str(quantity),
                "status": "Shipped"
            }
            return True
        return False

    def change_order_status(self, order_id: int, status: str) -> bool:
        if order_id in self.orders:
            self.orders[order_id]["status"] = status
            return True
        return False

    def track_order(self, order_id: int) -> str:
        if order_id in self.orders:
            return self.orders[order_id]["status"]
        return ""

    def orders(self) -> Dict[int, Dict[str, str]]:
        return {id: dict(inner) for id, inner in self.orders.items()}

    def inventory(self) -> Dict[int, Dict[str, str]]:
        return {id: dict(inner) for id, inner in self.inventory.items()}