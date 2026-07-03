class DiscountStrategy:
    class Customer:
        def __init__(self, name, fidelity):
            self.name = name
            self.fidelity = fidelity

        def getName(self):
            return self.name

        def getFidelity(self):
            return self.fidelity

    class Cart:
        def __init__(self, *products):
            self.products = list(products)

        def addProduct(self, product):
            self.products.append(product)

        def getProducts(self):
            return self.products

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

    @staticmethod
    def FIDELITY_PROMO(order):
        return order.total() * 0.05 if order.customer.getFidelity() >= 1000 else 0

    @staticmethod
    def BULK_ITEM_PROMO(order):
        discount = 0.0
        for item in order.cart.getProducts():
            if item.getQuantity() >= 20:
                discount += item.getQuantity() * item.getPrice() * 0.1
        return discount

    @staticmethod
    def LARGE_ORDER_PROMO(order):
        return order.total() * 0.07 if len(order.cart.getProducts()) >= 10 else 0

    def __init__(self, customer, cart, promotion):
        self.customer = customer
        self.cart = cart
        self.promotion = promotion
        self.total = self.total()

    def total(self):
        self.total = sum(p.getQuantity() * p.getPrice() for p in self.cart.getProducts())
        return self.total

    def due(self):
        discount = 0 if self.promotion is None else self.promotion(self)
        return self.total - discount

    def promotion(self, order):
        return 0 if self.promotion is None else self.promotion(self)