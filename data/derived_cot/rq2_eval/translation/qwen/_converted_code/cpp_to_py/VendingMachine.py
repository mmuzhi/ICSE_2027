class VendingMachine:
    def __init__(self):
        self.balance_ = 0.0
        self.inventory_ = {}

    def add_item(self, item_name, price, quantity):
        if self.inventory_.get(item_name):
            self.inventory_[item_name]["quantity"] += float(quantity)
        else:
            self.inventory_[item_name] = {"price": float(price), "quantity": float(quantity)}

    def insert_coin(self, amount):
        self.balance_ += amount
        return self.balance_

    def purchase_item(self, item_name):
        if item_name in self.inventory_:
            item = self.inventory_[item_name]
            if item["quantity"] > 0 and self.balance_ >= item["price"]:
                self.balance_ -= item["price"]
                item["quantity"] -= 1
                return self.balance_
        return 0.0  # False in C++ is represented as 0.0

    def restock_item(self, item_name, quantity):
        if item_name in self.inventory_:
            self.inventory_[item_name]["quantity"] += float(quantity)
            return True
        return False

    def display_items(self):
        if not self.inventory_:
            return "false"
        result = []
        for item_name, details in self.inventory_.items():
            result.append(f"{item_name} - ${details['price']} [{details['quantity']}]")
        return "\n".join(result).rstrip('\n')

    def inventory_(self):
        return self.inventory_

    def set_inventory(self, x):
        self.inventory_ = x

    def set_balance(self, y):
        self.balance_ = y