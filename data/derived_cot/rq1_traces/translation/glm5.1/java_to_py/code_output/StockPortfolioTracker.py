class StockPortfolioTracker:
    class Stock:
        def __init__(self, name, price, quantity):
            self.name = name
            self.price = price
            self.quantity = quantity

        def get_name(self):
            return self.name

        def get_price(self):
            return self.price

        def get_quantity(self):
            return self.quantity

        def set_quantity(self, quantity):
            self.quantity = quantity

        def __eq__(self, obj):
            if self is obj:
                return True
            if obj is None or type(self) is not type(obj):
                return False
            stock = obj
            return (stock.price == self.price and
                    self.quantity == stock.quantity and
                    self.name == stock.name)

        def __hash__(self):
            return hash((self.name, self.price, self.quantity))

        def __str__(self):
            return self.name + ": " + str(self.quantity) + " shares at $" + str(self.price) + " each"

    def __init__(self, initial_cash_balance):
        self._initial_cash_balance = initial_cash_balance
        self._cash_balance = initial_cash_balance
        self._portfolio = []

    def add_stock(self, stock):
        for s in self._portfolio:
            if s.get_name() == stock.get_name() and s.get_price() == stock.get_price():
                s.set_quantity(s.get_quantity() + stock.get_quantity())
                return
        self._portfolio.append(stock)

    def remove_stock(self, stock):
        for s in self._portfolio:
            if s.get_name() == stock.get_name() and s.get_price() == stock.get_price():
                if s.get_quantity() >= stock.get_quantity():
                    s.set_quantity(s.get_quantity() - stock.get_quantity())
                    if s.get_quantity() == 0:
                        self._portfolio.remove(s)
                    return True
        return False

    def buy_stock(self, stock):
        cost = stock.get_price() * stock.get_quantity()
        if self._cash_balance >= cost:
            self.add_stock(stock)
            self._cash_balance -= cost
            return True
        return False

    def sell_stock(self, stock):
        revenue = stock.get_price() * stock.get_quantity()
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
            total_value += stock.get_price() * stock.get_quantity()
        return total_value

    def get_portfolio_summary(self):
        summary = ""
        for stock in self._portfolio:
            summary += str(stock) + "\n"
        summary += "Total Value: $" + str(self.calculate_portfolio_value()) + "\n"
        return summary