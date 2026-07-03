class DiscountStrategy:
    class PromoType:
        FidelityPromo = 'FIDELITY_PROMO'
        BulkItemPromo = 'BULK_ITEM_PROMO'
        LargeOrderPromo = 'LARGE_ORDER_PROMO'
        NoPromo = 'NO_PROMO'

    def __init__(self, customer, cart, promo=None):
        self.customer = customer
        self.cart = cart
        self.promo = promo if promo is not None else self.PromoType.NoPromo

    def total(self):
        return sum(qty * price for item in self.cart for qty, price in item.items() if 'quantity' in item and 'price' in item)

    def due(self):
        return self.total() - self.promotion(self)

    def promotion(self, order):
        promotions = {
            self.PromoType.FidelityPromo: order.fidelity_discount,
            self.PromoType.BulkItemPromo: order.bulk_item_discount,
            self.PromoType.LargeOrderPromo: order.large_order_discount
        }
        return promotions.get(self.promo, lambda: 0.0)()

    def fidelity_discount(self):
        fidelity = self.customer.get('fidelity', 0)
        if fidelity >= 1000:
            return 0.05 * self.total()
        return 0.0

    def bulk_item_discount(self):
        discount = 0.0
        for item in self.cart:
            qty = item.get('quantity')
            price = item.get('price')
            if qty is not None and price is not None and qty >= 20:
                discount += qty * price * 0.1
        return discount

    def large_order_discount(self):
        num_items = len(self.cart)
        if num_items >= 10:
            return 0.07 * self.total()
        return 0.0