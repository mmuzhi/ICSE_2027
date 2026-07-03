from enum import Enum, auto

class PromoType(Enum):
    FidelityPromo = auto()
    BulkItemPromo = auto()
    LargeOrderPromo = auto()
    NoPromo = auto()

class DiscountStrategy:
    def __init__(self, customer, cart, promo=PromoType.NoPromo):
        self.customer_ = customer
        self.cart_ = cart
        self.promo_ = promo

    def total(self):
        total = 0.0
        for item in self.cart_:
            total += item["quantity"] * item["price"]
        return total

    def due(self):
        return self.total() - self.promotion(self)

    def promotion(self, order):
        if self.promo_ == PromoType.FidelityPromo:
            return self.fidelity_discount()
        elif self.promo_ == PromoType.BulkItemPromo:
            return self.bulk_item_discount()
        elif self.promo_ == PromoType.LargeOrderPromo:
            return self.large_order_discount()
        else:
            return 0.0

    def fidelity_discount(self):
        if self.customer_["fidelity"] >= 1000.0:
            return 0.05 * self.total()
        return 0.0

    def bulk_item_discount(self):
        discount = 0.0
        for item in self.cart_:
            if item["quantity"] >= 20:
                discount += item["quantity"] * item["price"] * 0.1
        return discount

    def large_order_discount(self):
        if len(self.cart_) >= 10:
            return 0.07 * self.total()
        return 0.0