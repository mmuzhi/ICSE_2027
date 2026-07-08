class BookManagement:
    def __init__(self):
        self.inventory = {}

    def add_book(self, title, quantity):
        # Equivalent to Java's containsKey/get/put logic, using dict.get for idiomatic Python
        self.inventory[title] = self.inventory.get(title, 0) + quantity

    def remove_book(self, title, quantity):
        if title not in self.inventory or self.inventory[title] < quantity:
            raise Exception("Invalid operation")
        
        new_quantity = self.inventory[title] - quantity
        if new_quantity == 0:
            del self.inventory[title]
        else:
            self.inventory[title] = new_quantity

    def view_inventory(self):
        # Returns a shallow copy of the dictionary, identical to new HashMap<>(inventory)
        return self.inventory.copy()

    def view_book_quantity(self, title):
        # Equivalent to Java's getOrDefault
        return self.inventory.get(title, 0)