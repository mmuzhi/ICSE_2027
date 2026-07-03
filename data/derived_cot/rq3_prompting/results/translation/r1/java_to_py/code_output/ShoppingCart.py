class ShoppingCart:
    class Item:
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

        def __eq__(self, other):
            if self is other:
                return True
            if other is None or type(self) != type(other):
                return False
            return self.price == other.price and self.quantity == other.quantity

        def __hash__(self):
            return hash((self.price, self.quantity))

    def __init__(self):
        self.items = {}

    def add_item(self, item: str, price: float, quantity: int) -> None:
        if item in self.items:
            existing = self.items[item]
            existing.set_price(price)
            existing.set_quantity(existing.get_quantity() + quantity)
        else:
            self.items[item] = self.Item(price, quantity)

    def remove_item(self, item: str, quantity: int) -> None:
        if item in self.items:
            existing = self.items[item]
            new_qty = existing.get_quantity() - quantity
            if new_qty <= 0:
                del self.items[item]
            else:
                existing.set_quantity(new_qty)

    def view_items(self):
        return dict(self.items)

    def total_price(self) -> float:
        total = 0.0
        for it in self.items.values():
            total += it.get_price() * it.get_quantity()
        return total