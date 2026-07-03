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
    FIDELITY_PROMO = None
    BULK_ITEM_PROMO = None
    LARGE_ORDER_PROMO = None

    def __init__(self, customer, cart, promotion):
        self.customer = customer
        self.cart = cart
        self.promotion = promotion
        self.total = self.total()

    def total(self):
        total_val = 0.0
        for product in self.cart.get_products():
            total_val += product.get_quantity() * product.get_price()
        self.total = total_val
        return total_val

    def due(self):
        discount = 0.0
        if self.promotion is not None:
            discount = self.promotion(self)
        return self.total - discount

    def promotion(self, order):
        if self.promotion is None:
            return 0.0
        else:
            return self.promotion(self)

def fidelity_promo(order):
    if order.customer.get_fidelity() >= 1000:
        return order.total() * 0.05
    else:
        return 0.0

def bulk_item_promo(order):
    discount = 0.0
    for product in order.cart.get_products():
        if product.get_quantity() >= 20:
            discount += product.get_quantity() * product.get_price() * 0.1
    return discount

def large_order_promo(order):
    if len(order.cart.get_products()) >= 10:
        return order.total() * 0.07
    else:
        return 0.0

DiscountStrategy.FIDELITY_PROMO = fidelity_promo
DiscountStrategy.BULK_ITEM_PROMO = bulk_item_promo
DiscountStrategy.LARGE_ORDER_PROMO = large_order_promo