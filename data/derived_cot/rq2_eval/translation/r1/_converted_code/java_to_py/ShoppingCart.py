class ShoppingCart:

    class Item:
        __slots__ = ('price', 'quantity')

        def __init__(self, price, quantity):
            self.price = price
            self.quantity = quantity

        def __eq__(self, other):
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return self.price == other.price and self.quantity == other.quantity

        def __hash__(self):
            return hash((self.price, self.quantity))

    def __init__(self):
        self.items = {}

    def add_item(self, item_name, price, quantity):
        if item_name in self.items:
            existing_item = self.items[item_name]
            existing_item.price = price
            existing_item.quantity += quantity
        else:
            self.items[item_name] = ShoppingCart.Item(price, quantity)

    def remove_item(self, item_name, quantity):
        if item_name in self.items:
            existing_item = self.items[item_name]
            new_quantity = existing_item.quantity - quantity
            if new_quantity <= 0:
                del self.items[item_name]
            else:
                existing_item.quantity = new_quantity

    def view_items(self):
        return self.items.copy()

    def total_price(self):
        total = 0.0
        for item in self.items.values():
            total += item.price * item.quantity
        return total