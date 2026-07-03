class PromoType:
    FidelityPromo = "FidelityPromo"
    BulkItemPromo = "BulkItemPromo"
    LargeOrderPromo = "LargeOrderPromo"
    NoPromo = "NoPromo"

class DiscountStrategy:
    def __init__(self, customer, cart, promo_type=PromoType.NoPromo):
        self.customer = customer
        self.cart = cart
        self.promo_type = promo_type

    def total(self):
        total = 0.0
        for item in self.cart:
            total += item["quantity"] * item["price"]
        return total

    def due(self):
        return self.total() - self.promotion(self)

    def promotion(self, order):
        if order.promo_type == PromoType.FidelityPromo:
            return order.fidelity_discount()
        elif order.promo_type == PromoType.BulkItemPromo:
            return order.bulk_item_discount()
        elif order.promo_type == PromoType.LargeOrderPromo:
            return order.large_order_discount()
        else:
            return 0.0

    def fidelity_discount(self):
        fidelity = self.customer["fidelity"]
        if fidelity >= 1000.0:
            return 0.05 * self.total()
        return 0.0

    def bulk_item_discount(self):
        discount = 0.0
        for item in self.cart:
            if item["quantity"] >= 20:
                discount += item["quantity"] * item["price"] * 0.1
        return discount

    def large_order_discount(self):
        num_items = len(self.cart)
        if num_items >= 10:
            return 0.07 * self.total()
        return 0.0