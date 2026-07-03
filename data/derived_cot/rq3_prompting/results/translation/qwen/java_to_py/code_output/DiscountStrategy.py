class Customer:
    def __init__(self, name, fidelity):
        self.name = name
        self.fidelity = fidelity

    def get_name(self):
        return self.name

    def get_fidelity(self):
        return self.fidelity

class Cart:
    def __init__(self, *products):
        self.products = list(products)

    def add_product(self, product):
        self.products.append(product)

    def get_products(self):
        return self.products

class Product:
    def __init__(self, name, quantity, price):
        self.name = name
        self.quantity = quantity
        self.price = price

    def get_name(self):
        return self.name

    def get_quantity(self):
        return self.quantity

    def get_price(self):
        return self.price

class DiscountStrategy:
    FIDELITY_PROMO = lambda order: order.total() * 0.05 if order.customer.get_fidelity() >= 1000 else 0
    BULK_ITEM_PROMO = lambda order: sum(
        item.get_quantity() * item.get_price() * 0.1 
        for item in order.cart.get_products() 
        if item.get_quantity() >= 20
    )
    LARGE_ORDER_PROMO = lambda order: order.total() * 0.07 if len(order.cart.get_products()) >= 10 else 0

    def __init__(self, customer, cart, promotion=None):
        self.customer = customer
        self.cart = cart
        self.promotion = promotion
        self.total = self.total()

    def total(self):
        self.total = sum(
            item.get_quantity() * item.get_price() 
            for item in self.cart.get_products()
        )
        return self.total

    def due(self):
        discount = self.promotion() if self.promotion is not None else 0
        return self.total - discount

    def promotion(self, order):
        return self.promotion() if self.promotion is not None else 0