import math

class Stock:
    def __init__(self, name, price, quantity):
        self._name = name
        self._price = price
        self._quantity = quantity

    @property
    def name(self):
        return self._name

    @property
    def price(self):
        return self._price

    @property
    def quantity(self):
        return self._quantity

    @quantity.setter
    def quantity(self, value):
        self._quantity = value

    def __eq__(self, other):
        if self is other:
            return True
        if type(self) is not type(other):
            return False
        if self.name != other.name:
            return False
        if self.quantity != other.quantity:
            return False
        if math.isnan(self.price) and math.isnan(other.price):
            return True
        if self.price == 0.0 and other.price == 0.0:
            return math.copysign(1, self.price) == math.copysign(1, other.price)
        return self.price == other.price

    def __hash__(self):
        if math.isnan(self.price):
            return hash((self.name, 'nan', self.quantity))
        elif self.price == 0.0:
            return hash((self.name, 0.0, math.copysign(1, self.price), self.quantity))
        else:
            return hash((self.name, self.price, self.quantity))

    def __str__(self):
        return f"{self.name}: {self.quantity} shares at ${self.price} each"

class StockPortfolioTracker:
    def __init__(self, initial_cash_balance):
        self.initial_cash_balance = initial_cash_balance
        self.cash_balance = initial_cash_balance
        self.portfolio = []

    def add_stock(self, stock):
        for s in self.portfolio:
            if s.name == stock.name and s.price == stock.price:
                s.quantity += stock.quantity
                return
        self.portfolio.append(stock)

    def remove_stock(self, stock):
        for s in self.portfolio:
            if s.name == stock.name and s.price == stock.price:
                if s.quantity >= stock.quantity:
                    s.quantity -= stock.quantity
                    if s.quantity == 0:
                        self.portfolio.remove(s)
                    return True
        return False

    def buy_stock(self, stock):
        cost = stock.price * stock.quantity
        if self.cash_balance >= cost:
            self.add_stock(stock)
            self.cash_balance -= cost
            return True
        return False

    def sell_stock(self, stock):
        revenue = stock.price * stock.quantity
        if self.remove_stock(stock):
            self.cash_balance += revenue
            return True
        return False

    def get_portfolio(self):
        return list(self.portfolio)

    def get_cash_balance(self):
        return self.cash_balance

    def calculate_portfolio_value(self):
        total_value = 0.0
        for stock in self.portfolio:
            total_value += stock.price * stock.quantity
        return total_value

    def get_portfolio_summary(self):
        summary = []
        for stock in self.portfolio:
            summary.append(str(stock))
        total_value = self.calculate_portfolio_value()
        summary.append(f"Total Value: ${total_value}")
        return "\n".join(summary) + "\n"