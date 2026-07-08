class Customer:
    def __init__(self, name, fidelity):
        self.name = name
        self.fidelity = fidelity

    def getName(self):
        return self.name

    def getFidelity(self):
        return self.fidelity


class Product:
    def __init__(self, name, quantity, price):
        self.name = name
        self.quantity = quantity
        self.price = price

    def getName(self):
        return self.name

    def getQuantity(self):
        return self.quantity

    def getPrice(self):
        return self.price


class Cart:
    def __init__(self, *products):
        self.products = list(products)

    def addProduct(self, product):
        self.products.append(product)

    def getProducts(self):
        return self.products


class DiscountStrategy:
    FIDELITY_PROMO = None
    BULK_ITEM_PROMO = None
    LARGE_ORDER_PROMO = None

    def __init__(self, customer, cart, promotion):
        self.customer = customer
        self.cart = cart
        self._promotion = promotion
        self._total = self.total()

    def total(self):
        self._total = sum(p.getQuantity() * p.getPrice() for p in self.cart.getProducts())
        return self._total

    def due(self):
        discount = 0 if self._promotion is None else self._promotion(self)
        return self._total - discount

    def promotion(self, order):
        return 0 if self._promotion is None else self._promotion(self)


DiscountStrategy.FIDELITY_PROMO = lambda order: order.total() * 0.05 if order.customer.getFidelity() >= 1000 else 0

DiscountStrategy.BULK_ITEM_PROMO = lambda order: sum(
    item.getQuantity() * item.getPrice() * 0.1
    for item in order.cart.getProducts()
    if item.getQuantity() >= 20
)

DiscountStrategy.LARGE_ORDER_PROMO = lambda order: order.total() * 0.07 if len(order.cart.getProducts()) >= 10 else 0