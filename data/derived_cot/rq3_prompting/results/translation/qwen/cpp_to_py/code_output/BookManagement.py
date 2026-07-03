class BookManagement:
    def __init__(self):
        self.inventory = {}

    def add_book(self, title, quantity=1):
        if quantity <= 0:
            raise ValueError("Quantity must be positive")
        self.inventory[title] = self.inventory.get(title, 0) + quantity

    def remove_book(self, title, quantity):
        if quantity <= 0:
            raise ValueError("Quantity must be positive")
        if title not in self.inventory:
            raise KeyError(f"Book '{title}' not found")
        if self.inventory[title] < quantity:
            raise ValueError(f"Not enough books for '{title}'")
        self.inventory[title] -= quantity
        if self.inventory[title] == 0:
            del self.inventory[title]

    def view_inventory(self):
        return self.inventory.copy()

    def view_book_quantity(self, title):
        return self.inventory.get(title, 0)