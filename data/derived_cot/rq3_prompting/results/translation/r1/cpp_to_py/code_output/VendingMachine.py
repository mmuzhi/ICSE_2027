class VendingMachine:
    def __init__(self):
        self.balance = 0.0
        self.inventory = {}

    def add_item(self, item_name: str, price: float, quantity: int) -> None:
        if not self.restock_item(item_name, quantity):
            self.inventory[item_name] = {"price": price, "quantity": float(quantity)}

    def insert_coin(self, amount: float) -> float:
        self.balance += amount
        return self.balance

    def purchase_item(self, item_name: str) -> float:
        if item_name in self.inventory:
            item = self.inventory[item_name]
            if item["quantity"] > 0 and self.balance >= item["price"]:
                self.balance -= item["price"]
                item["quantity"] -= 1.0
                return self.balance
        return 0.0

    def restock_item(self, item_name: str, quantity: int) -> bool:
        if item_name in self.inventory:
            self.inventory[item_name]["quantity"] += float(quantity)
            return True
        return False

    def display_items(self) -> str:
        if not self.inventory:
            return "false"
        lines = []
        for name, data in self.inventory.items():
            lines.append(f"{name} - ${data['price']} [{int(data['quantity'])}]")
        return "\n".join(lines)

    def inventory(self):
        return self.inventory

    def set_inventory(self, x):
        self.inventory = x

    def set_balance(self, y):
        self.balance = y