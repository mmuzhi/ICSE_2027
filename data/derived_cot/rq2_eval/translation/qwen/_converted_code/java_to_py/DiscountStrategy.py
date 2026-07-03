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


class Cart:
    def __init__(self, *products):
        self.products = list(products)

    def get_products(self):
        return self.products

    def add_product(self, product):
        self.products.append(product)


class Customer:
    def __init__(self, name, fidelity):
        self.name = name
        self.fidelity = fidelity

    def get_fidelity(self):
        return self.fidelity


class Promotion:
    def __call__(self, discount_strategy):
        return type(self).apply(discount_strategy)


class FidelityPromo(Promotion):
    @staticmethod
    def apply(ds):
        if ds.customer.fidelity >= 1000:
            return ds.total() * 0.05
        return 0


class BulkItemPromo(Promotion):
    @staticmethod
    def apply(ds):
        discount = 0.0
        for item in ds.cart.get_products():
            if item.get_quantity() >= 20:
                discount += item.get_quantity() * item.get_price() * 0.1
        return discount


class LargeOrderPromo(Promotion):
    @staticmethod
    def apply(ds):
        if len(ds.cart.get_products()) >= 10:
            return ds.total() * 0.07
        return 0


class DiscountStrategy:
    def __init__(self, customer, cart, promotion=None):
        self.customer = customer
        self.cart = cart
        self.promotion = promotion
        self.total = self.total()

    def total(self):
        return sum(item.get_quantity() * item.get_price() for item in self.cart.get_products())

    def due(self):
        discount = self.promotion() if self.promotion else 0
        return self.total - discount

    def promotion(self):
        return self.due() + (self.promotion() if self.promotion else 0)