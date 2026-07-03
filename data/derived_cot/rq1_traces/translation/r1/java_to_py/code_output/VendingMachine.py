class Product:
    def __init__(self, price, quantity):
        self._price = price
        self._quantity = quantity

    @property
    def price(self):
        return self._price

    @price.setter
    def price(self, value):
        self._price = value

    @property
    def quantity(self):
        return self._quantity

    @quantity.setter
    def quantity(self, value):
        self._quantity = value


class VendingMachine:
    def __init__(self):
        self._inventory = {}
        self._balance = 0.0

    @property
    def inventory(self):
        return self._inventory

    @inventory.setter
    def inventory(self, value):
        self._inventory = value

    @property
    def balance(self):
        return self._balance

    @balance.setter
    def balance(self, value):
        self._balance = value

    def addItem(self, itemName, price, quantity):
        if not self.restockItem(itemName, quantity):
            self._inventory[itemName] = Product(price, quantity)

    def insertCoin(self, amount):
        self._balance += amount
        return self._balance

    def purchaseItem(self, itemName):
        if itemName in self._inventory:
            item = self._inventory[itemName]
            if item.quantity > 0 and self._balance >= item.price:
                self._balance -= item.price
                item.quantity = item.quantity - 1
                return self._balance
            else:
                return False
        else:
            return False

    def restockItem(self, itemName, quantity):
        if itemName in self._inventory:
            item = self._inventory[itemName]
            item.quantity += quantity
            return True
        else:
            return False

    def displayItems(self):
        if not self._inventory:
            return False
        else:
            items = []
            for name, product in self._inventory.items():
                items.append(f"{name} - ${product.price:.2f} [{product.quantity}]")
            return "\n".join(items)