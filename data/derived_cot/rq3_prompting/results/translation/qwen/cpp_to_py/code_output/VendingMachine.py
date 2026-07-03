class VendingMachine:
    def __init__(self):
        self.inventory = {}
        self.balance = 0.0

    def add_item(self, item_name, price, quantity):
        if item_name in self.inventory:
            self.inventory[item_name]["quantity"] += quantity
        else:
            self.inventory[item_name] = {"price": price, "quantity": quantity}

    def insert_coin(self, amount):
        self.balance += amount
        return self.balance

    def purchase_item(self, item_name):
        if item_name in self.inventory:
            item = self.inventory[item_name]
            if item["quantity"] > 0 and self.balance >= item["price"]:
                self.balance -= item["price"]
                item["quantity"] -= 1
                return self.balance
        return 0.0

    def restock_item(self, item_name, quantity):
        if item_name in self.inventory:
            self.inventory[item_name]["quantity"] += quantity
            return True
        return False

    def display_items(self):
        if not self.inventory:
            return "false"
        output = []
        for item_name, item_data in self.inventory.items():
            output.append(f"{item_name} - ${item_data['price']} [{item_data['quantity']}]")
        result = "\n".join(output)
        if result.endswith('\n'):
            result = result[:-1]
        return result

    def inventory(self):
        return self.inventory

    def set_inventory(self, x):
        self.inventory = x

    def set_balance(self, y):
        self.balance = y