class ShoppingCart:
    def __init__(self):
        self._items = {}  # maps item name -> (price: float, quantity: int)

    def add_item(self, item: str, price: float, quantity: int = 1) -> None:
        # Exactly replicate the original C++ logic (both branches do the same thing)
        if item in self._items:
            self._items[item] = (price, quantity)
        else:
            self._items[item] = (price, quantity)

    def remove_item(self, item: str, quantity: int = 1) -> None:
        if item in self._items:
            price, qty = self._items[item]
            qty -= quantity
            if qty <= 0:
                del self._items[item]
            else:
                self._items[item] = (price, qty)

    def view_items(self):
        # Return a shallow copy to preserve encapsulation, matching C++ return-by-value
        return dict(self._items)

    def total_price(self) -> float:
        total = 0.0
        for price, qty in self._items.values():
            total += price * qty
        return total