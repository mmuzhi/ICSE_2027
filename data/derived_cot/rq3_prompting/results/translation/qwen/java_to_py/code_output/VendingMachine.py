from collections import OrderedDict

class VendingMachine:
    class Product:
        def __init__(self, price, quantity):
            self.price = price
            self.quantity = quantity

        def getPrice(self):
            return self.price

        def setPrice(self, price):
            self.price = price

        def getQuantity(self):
            return self.quantity

        def setQuantity(self, quantity):
            self.quantity = quantity

    def __init__(self):
        self.inventory = OrderedDict()
        self.balance = 0.0

    def addItem(self, itemName, price, quantity):
        if not self.restockItem(itemName, quantity):
            self.inventory[itemName] = VendingMachine.Product(price, quantity)

    def insertCoin(self, amount):
        self.balance += amount
        return self.balance

    def purchaseItem(self, itemName):
        if itemName not in self.inventory:
            return None
        product = self.inventory[itemName]
        if product.quantity <= 0 or self.balance < product.price:
            return None
        self.balance -= product.price
        product.quantity -= 1
        return self.balance

    def restockItem(self, itemName, quantity):
        if itemName in self.inventory:
            product = self.inventory[itemName]
            product.quantity += quantity
            return True
        return False

    def displayItems(self):
        if not self.inventory:
            return False
        items = []
        for key, product in self.inventory.items():
            items.append(f"{key} - ${product.price:.2f} [{product.quantity}]")
        result = "\n".join(items)
        if result.endswith('\n'):
            result = result.rstrip()
        return result

    def getInventory(self):
        return self.inventory

    def setInventory(self, inventory):
        self.inventory = inventory

    def getBalance(self):
        return self.balance

    def setBalance(self, balance):
        self.balance = balance