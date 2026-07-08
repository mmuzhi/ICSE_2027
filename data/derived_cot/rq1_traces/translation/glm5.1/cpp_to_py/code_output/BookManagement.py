class BookManagement:
    def __init__(self):
        self.inventory = {}

    def add_book(self, title: str, quantity: int = 1):
        self.inventory[title] = self.inventory.get(title, 0) + quantity

    def remove_book(self, title: str, quantity: int):
        if title not in self.inventory or self.inventory[title] < quantity:
            raise RuntimeError("Insufficient quantity or book not found")
        
        self.inventory[title] -= quantity
        if self.inventory[title] == 0:
            del self.inventory[title]

    def view_inventory(self) -> dict:
        # Return a copy to mimic C++ returning by value (preventing external modification)
        return self.inventory.copy()

    def view_book_quantity(self, title: str) -> int:
        return self.inventory.get(title, 0)