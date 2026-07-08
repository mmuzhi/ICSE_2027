class VendingMachine:
    def __init__(self):
        self._inventory = {}
        self._balance = 0.0

    def add_item(self, item_name, price, quantity):
        if not self.restock_item(item_name, quantity):
            self._inventory[item_name] = {"price": price, "quantity": float(quantity)}

    def insert_coin(self, amount):
        self._balance += amount
        return self._balance

    def purchase_item(self, item_name):
        if item_name in self._inventory:
            item = self._inventory[item_name]
            if item["quantity"] > 0 and self._balance >= item["price"]:
                self._balance -= item["price"]
                item["quantity"] -= 1
                return self._balance
        return 0.0  # C++ returns false, implicitly converted to 0.0

    def restock_item(self, item_name, quantity):
        if item_name in self._inventory:
            self._inventory[item_name]["quantity"] += float(quantity)
            return True
        return False

    def display_items(self):
        if not self._inventory:
            return "false"
        lines = []
        for name, item in self._inventory.items():
            # Match C++ ostringstream default formatting (precision 6, %g-style)
            price_str = f"{item['price']:.6g}"
            qty_str = f"{item['quantity']:.6g}"
            lines.append(f"{name} - ${price_str} [{qty_str}]")
        return "\n".join(lines)

    def inventory(self):
        return self._inventory

    def set_inventory(self, x):
        self._inventory = x

    def set_balance(self, y):
        self._balance = y