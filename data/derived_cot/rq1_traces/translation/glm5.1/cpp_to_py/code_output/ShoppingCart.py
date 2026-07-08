class ShoppingCart:
    def __init__(self):
        self.items = {}

    def add_item(self, item: str, price: float, quantity: int = 1) -> None:
        # The original C++ code has an if/else block that does the exact same thing in both branches.
        # We simplify it to the single assignment.
        self.items[item] = (price, quantity)

    def remove_item(self, item: str, quantity: int = 1) -> None:
        if item in self.items:
            price, current_quantity = self.items[item]
            current_quantity -= quantity
            if current_quantity <= 0:
                del self.items[item]
            else:
                self.items[item] = (price, current_quantity)

    def view_items(self) -> dict:
        # Returning a copy to match C++ return-by-value behavior (preventing external mutation)
        return self.items.copy()

    def total_price(self) -> float:
        return sum(price * quantity for price, quantity in self.items.values())