from typing import Dict

class ShoppingCart:
    class Item:
        def __init__(self, price: float, quantity: int):
            self.price = price
            self.quantity = quantity

        def __eq__(self, other: object) -> bool:
            if self is other:
                return True
            if type(other) is not type(self):
                return False
            return self.price == other.price and self.quantity == other.quantity

        def __hash__(self) -> int:
            return hash((self.price, self.quantity))

    def __init__(self):
        self.items: Dict[str, ShoppingCart.Item] = {}

    def addItem(self, item: str, price: float, quantity: int) -> None:
        if item in self.items:
            existing_item = self.items[item]
            existing_item.price = price
            existing_item.quantity += quantity
        else:
            self.items[item] = self.Item(price, quantity)

    def removeItem(self, item: str, quantity: int) -> None:
        if item in self.items:
            existing_item = self.items[item]
            new_quantity = existing_item.quantity - quantity
            if new_quantity <= 0:
                del self.items[item]
            else:
                existing_item.quantity = new_quantity

    def viewItems(self) -> Dict[str, 'ShoppingCart.Item']:
        # Returns a shallow copy, identically to `new HashMap<>(items)` in Java
        return dict(self.items)

    def totalPrice(self) -> float:
        return sum(item.price * item.quantity for item in self.items.values())