class VendingMachine:

    class Product:

        def __init__(self, price, quantity):
            self.price = price
            self.quantity = quantity

        def get_price(self):
            return self.price

        def set_price(self, price):
            self.price = price

        def get_quantity(self):
            return self.quantity

        def set_quantity(self, quantity):
            self.quantity = quantity

    def __init__(self):
        self.inventory = {}
        self.balance = 0.0

    def add_item(self, itemName, price, quantity):
        if self.restock_item(itemName, quantity):
            pass
        else:
            self.inventory[itemName] = self.Product(price, quantity)

    def insert_coin(self, amount):
        self.balance += amount
        return self.balance

    def purchase_item(self, itemName):
        if itemName not in self.inventory:
            return False
        product = self.inventory[itemName]
        if product.get_quantity() <= 0 or self.balance < product.get_price():
            return False
        self.balance -= product.get_price()
        product.set_quantity(product.get_quantity() - 1)
        return self.balance

    def restock_item(self, itemName, quantity):
        if itemName in self.inventory:
            product = self.inventory[itemName]
            product.set_quantity(product.get_quantity() + quantity)
            return True
        return False

    def display_items(self):
        if not self.inventory:
            return False
        output = []
        for itemName, product in self.inventory.items():
            output.append(f'{itemName} - ${product.get_price():.2f} [{product.get_quantity()}]')
        return '\n'.join(output)