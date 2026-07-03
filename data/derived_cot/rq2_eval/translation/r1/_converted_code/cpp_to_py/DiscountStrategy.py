from enum import Enum

class DiscountStrategy:

    class PromoType(Enum):
        FidelityPromo = 1
        BulkItemPromo = 2
        LargeOrderPromo = 3
        NoPromo = 4

    def __init__(self, customer, cart, promo=PromoType.NoPromo):
        self.customer_ = customer
        self.cart_ = cart
        self.promo_ = promo

    def total(self):
        total_val = 0.0
        for item in self.cart_:
            total_val += item['quantity'] * item['price']
        return total_val

    def due(self):
        return self.total() - self.FidelityPromo(self)

    def FidelityPromo(self, order):
        if self.promo_ == DiscountStrategy.PromoType.FidelityPromo:
            return self._fidelity_discount()
        elif self.promo_ == DiscountStrategy.PromoType.BulkItemPromo:
            return self.BulkItemPromo()
        elif self.promo_ == DiscountStrategy.PromoType.LargeOrderPromo:
            return self.LargeOrderPromo()
        else:
            return 0.0

    def _fidelity_discount(self):
        fidelity = self.customer_['fidelity']
        if fidelity >= 1000.0:
            return 0.05 * self.total()
        return 0.0

    def BulkItemPromo(self):
        discount = 0.0
        for item in self.cart_:
            if item['quantity'] >= 20:
                discount += item['quantity'] * item['price'] * 0.1
        return discount

    def LargeOrderPromo(self):
        num_items = len(self.cart_)
        if num_items >= 10:
            return 0.07 * self.total()
        return 0.0