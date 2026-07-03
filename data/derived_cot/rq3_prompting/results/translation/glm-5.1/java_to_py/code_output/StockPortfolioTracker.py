class StockPortfolioTracker:
    class Stock:
        def __init__(self, name, price, quantity):
            self.name = name
            self.price = price
            self.quantity = quantity

        def __eq__(self, obj):
            if not isinstance(obj, StockPortfolioTracker.Stock):
                return NotImplemented
            return (self.name == obj.name and
                    self.price == obj.price and
                    self.quantity == obj.quantity)

        def __hash__(self):
            return hash((self.name, self.price, self.quantity))

        def __str__(self):
            return f"{self.name}: {self.quantity} shares at ${self.price} each"

        def __repr__(self):
            return f"{self.name}: {self.quantity} shares at ${self.price} each"

    def __init__(self, initial_cash_balance):
        self._initial_cash_balance = initial_cash_balance
        self._cash_balance = initial_cash_balance
        self._portfolio = []

    def add_stock(self, stock):
        for s in self._portfolio:
            if s.name == stock.name and s.price == stock.price:
                s.quantity += stock.quantity
                return
        self._portfolio.append(stock)

    def remove_stock(self, stock):
        for s in self._portfolio:
            if s.name == stock.name and s.price == stock.price:
                if s.quantity >= stock.quantity:
                    s.quantity -= stock.quantity
                    if s.quantity == 0:
                        self._portfolio.remove(s)
                    return True
        return False

    def buy_stock(self, stock):
        cost = stock.price * stock.quantity
        if self._cash_balance >= cost:
            self.add_stock(stock)
            self._cash_balance -= cost
            return True
        return False

    def sell_stock(self, stock):
        revenue = stock.price * stock.quantity
        if self.remove_stock(stock):
            self._cash_balance += revenue
            return True
        return False

    def get_portfolio(self):
        return list(self._portfolio)

    def get_cash_balance(self):
        return self._cash_balance

    def calculate_portfolio_value(self):
        total_value = 0.0
        for stock in self._portfolio:
            total_value += stock.price * stock.quantity
        return total_value

    def get_portfolio_summary(self):
        summary = ""
        for stock in self._portfolio:
            summary += str(stock) + "\n"
        summary += f"Total Value: ${self.calculate_portfolio_value()}\n"
        return summary