class BookManagement:
    def __init__(self):
        self._inventory = {}

    def add_book(self, title: str, quantity: int = 1) -> None:
        if title in self._inventory:
            self._inventory[title] += quantity
        else:
            self._inventory[title] = quantity

    def remove_book(self, title: str, quantity: int) -> None:
        if title not in self._inventory or self._inventory[title] < quantity:
            raise RuntimeError("Insufficient quantity or book not found")
        self._inventory[title] -= quantity
        if self._inventory[title] == 0:
            del self._inventory[title]

    def view_inventory(self):
        # Return a copy to mimic C++ return-by-value behavior
        return dict(self._inventory)

    def view_book_quantity(self, title: str) -> int:
        return self._inventory.get(title, 0)