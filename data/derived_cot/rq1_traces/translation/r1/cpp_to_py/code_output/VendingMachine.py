class VendingMachine:
    def __init__(self):
        self.balance_ = 0.0
        self.inventory_ = {}
    
    def add_item(self, item_name, price, quantity):
        if not self.restock_item(item_name, quantity):
            self.inventory_[item_name] = {"price": float(price), "quantity": float(quantity)}
    
    def insert_coin(self, amount):
        self.balance_ += amount
        return self.balance_
    
    def purchase_item(self, item_name):
        if item_name in self.inventory_:
            item = self.inventory_[item_name]
            if item["quantity"] > 0 and self.balance_ >= item["price"]:
                self.balance_ -= item["price"]
                item["quantity"] -= 1.0
                return self.balance_
        return 0.0
    
    def restock_item(self, item_name, quantity):
        if item_name in self.inventory_:
            self.inventory_[item_name]["quantity"] += float(quantity)
            return True
        return False
    
    def display_items(self):
        if not self.inventory_:
            return "false"
        lines = []
        for item_name, details in self.inventory_.items():
            price_str = self._format_double(details["price"])
            quantity_str = self._format_double(details["quantity"])
            lines.append(f"{item_name} - ${price_str} [{quantity_str}]")
        return "\n".join(lines)
    
    def _format_double(self, x):
        s = f"{x:.6g}"
        return s
    
    def inventory(self):
        return {k: v.copy() for k, v in self.inventory_.items()}
    
    def set_inventory(self, x):
        self.inventory_ = {k: v.copy() for k, v in x.items()}
    
    def set_balance(self, y):
        self.balance_ = y