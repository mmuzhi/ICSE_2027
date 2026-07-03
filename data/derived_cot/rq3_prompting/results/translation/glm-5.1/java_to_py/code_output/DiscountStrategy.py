from typing import Callable, List, Optional


class DiscountStrategy:

    FIDELITY_PROMO = staticmethod(
        lambda order: order.total() * 0.05 if order.customer.get_fidelity() >= 1000 else 0
    )

    BULK_ITEM_PROMO = staticmethod(lambda order: sum(
        item.get_quantity() * item.get_price() * 0.1
        for item in order.cart.get_products()
        if item.get_quantity() >= 20
    ))

    LARGE_ORDER_PROMO = staticmethod(
        lambda order: order.total() * 0.07 if len(order.cart.get_products()) >= 10 else 0
    )

    def __init__(self, customer: 'DiscountStrategy.Customer', cart: 'DiscountStrategy.Cart',
                 promotion: Optional[Callable[['DiscountStrategy'], float]] = None):
        self.customer = customer
        self.cart = cart
        self._promotion = promotion
        self._total = self.total()

    def total(self) -> float:
        self._total = sum(p.get_quantity() * p.get_price() for p in self.cart.get_products())
        return self._total

    def due(self) -> float:
        discount = 0 if self._promotion is None else self._promotion(self)
        return self._total - discount

    def promotion(self, order: 'DiscountStrategy') -> float:
        return 0 if self._promotion is None else self._promotion(self)

    class Customer:
        def __init__(self, name: str, fidelity: int):
            self.name = name
            self.fidelity = fidelity

        def get_name(self) -> str:
            return self.name

        def get_fidelity(self) -> int:
            return self.fidelity

    class Cart:
        def __init__(self, *products):
            self.products: List['DiscountStrategy.Product'] = list(products)

        def add_product(self, product: 'DiscountStrategy.Product'):
            self.products.append(product)

        def get_products(self) -> list:
            return self.products

    class Product:
        def __init__(self, name: str, quantity: int, price: float):
            self.name = name
            self.quantity = quantity
            self.price = price

        def get_name(self) -> str:
            return self.name

        def get_quantity(self) -> int:
            return self.quantity

        def get_price(self) -> float:
            return self.price