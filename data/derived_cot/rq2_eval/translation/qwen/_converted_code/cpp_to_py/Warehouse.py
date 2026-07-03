import types

class Warehouse:
    def __init__(self):
        self.inventory_ = {}
        self.orders_ = {}

    def add_product(self, product_id, name, quantity):
        if product_id not in self.inventory_:
            self.inventory_[product_id] = {"name": name, "quantity": quantity}
        else:
            current_quantity = self.inventory_[product_id]["quantity"]
            self.inventory_[product_id]["quantity"] = current_quantity + quantity

    def update_product_quantity(self, product_id, quantity):
        if product_id in self.inventory_:
            current_quantity = self.inventory_[product_id]["quantity"]
            self.inventory_[product_id]["quantity"] = current_quantity + quantity

    def get_product_quantity(self, product_id):
        if product_id in self.inventory_:
            return self.inventory_[product_id]["quantity"]
        return 0

    def create_order(self, order_id, product_id, quantity):
        available_quantity = self.get_product_quantity(product_id)
        if available_quantity >= quantity:
            self.update_product_quantity(product_id, -quantity)
            order_entry = {
                "product_id": str(product_id),
                "quantity": str(quantity),
                "status": "Shipped"
            }
            self.orders_[order_id] = order_entry
            return True
        return False

    def change_order_status(self, order_id, status):
        if order_id in self.orders_:
            self.orders_[order_id]["status"] = status
            return True
        return False

    def track_order(self, order_id):
        if order_id in self.orders_:
            return self.orders_[order_id]["status"]
        return ""

    def orders(self):
        return types.MappingProxyType(self.orders_)

    def inventory(self):
        return types.MappingProxyType(self.inventory_)