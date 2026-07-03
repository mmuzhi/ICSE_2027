class Warehouse:
    def __init__(self):
        self._inventory = {}   # int -> dict[str, str]  keys: "name", "quantity"
        self._orders = {}      # int -> dict[str, str]  keys: "product_id", "quantity", "status"

    def add_product(self, product_id: int, name: str, quantity: int) -> None:
        if product_id not in self._inventory:
            self._inventory[product_id] = {
                "name": name,
                "quantity": str(quantity)
            }
        else:
            product = self._inventory[product_id]
            current_qty = int(product["quantity"])
            product["quantity"] = str(current_qty + quantity)

    def update_product_quantity(self, product_id: int, quantity: int) -> None:
        if product_id in self._inventory:
            product = self._inventory[product_id]
            current_qty = int(product["quantity"])
            product["quantity"] = str(current_qty + quantity)

    def get_product_quantity(self, product_id: int) -> int:
        if product_id in self._inventory:
            return int(self._inventory[product_id]["quantity"])
        return 0  # matches C++ returning false (implicit int 0)

    def create_order(self, order_id: int, product_id: int, quantity: int) -> bool:
        available = self.get_product_quantity(product_id)
        if available >= quantity:
            self.update_product_quantity(product_id, -quantity)
            self._orders[order_id] = {
                "product_id": str(product_id),
                "quantity": str(quantity),
                "status": "Shipped"
            }
            return True
        return False

    def change_order_status(self, order_id: int, status: str) -> bool:
        if order_id in self._orders:
            self._orders[order_id]["status"] = status
            return True
        return False

    def track_order(self, order_id: int) -> str:
        if order_id in self._orders:
            return self._orders[order_id]["status"]
        return ""

    # Note: In C++ these return const references, so the caller cannot modify.
    # Here we return the actual dicts for simplicity (common Python practice).
    def orders(self):
        return self._orders

    def inventory(self):
        return self._inventory