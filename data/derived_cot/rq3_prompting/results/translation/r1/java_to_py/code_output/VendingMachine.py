class VendingMachine:
    class Product:
        def __init__(self, price: float, quantity: int):
            self.price = price
            self.quantity = quantity

        def get_price(self) -> float:
            return self.price

        def set_price(self, price: float) -> None:
            self.price = price

        def get_quantity(self) -> int:
            return self.quantity

        def set_quantity(self, quantity: int) -> None:
            self.quantity = quantity

    def __init__(self):
        self.inventory = {}
        self.balance = 0.0

    def add_item(self, item_name: str, price: float, quantity: int) -> None:
        if not self.restock_item(item_name, quantity):
            self.inventory[item_name] = self.Product(price, quantity)

    def insert_coin(self, amount: float) -> float:
        self.balance += amount
        return self.balance

    def purchase_item(self, item_name: str):
        if item_name in self.inventory:
            item = self.inventory[item_name]
            if item.get_quantity() > 0 and self.balance >= item.get_price():
                self.balance -= item.get_price()
                item.set_quantity(item.get_quantity() - 1)
                return self.balance
            else:
                return False
        else:
            return False

    def restock_item(self, item_name: str, quantity: int) -> bool:
        if item_name in self.inventory:
            item = self.inventory[item_name]
            item.set_quantity(item.get_quantity() + quantity)
            return True
        else:
            return False

    def display_items(self):
        if not self.inventory:
            return False
        lines = []
        for name, prod in self.inventory.items():
            lines.append(f"{name} - ${prod.get_price():.2f} [{prod.get_quantity()}]")
        return "\n".join(lines)

    def get_inventory(self):
        return self.inventory

    def set_inventory(self, inventory):
        self.inventory = inventory

    def get_balance(self) -> float:
        return self.balance

    def set_balance(self, balance: float) -> None:
        self.balance = balance