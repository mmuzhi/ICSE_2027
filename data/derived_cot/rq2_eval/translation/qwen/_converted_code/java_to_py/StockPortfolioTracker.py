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

        def __eq__(self, other):
            if not isinstance(other, Stock):
                return False
            return (self.name == other.name and 
                    self.price == other.price and 
                    self.quantity == other.quantity)

        def __hash__(self):
            return hash((self.name, self.price, self.quantity))

    def __init__(self, initial_cash_balance):
        self.initial_cash_balance = initial_cash_balance
        self.cash_balance = initial_cash_balance
        self.portfolio = []

    def add_stock(self, stock):
        for s in self.portfolio:
            if s.get_name() == stock.get_name() and s.get_price() == stock.get_price():
                s.set_quantity(s.get_quantity() + stock.get_quantity())
                return
        self.portfolio.append(stock)

    def remove_stock(self, stock):
        for s in self.portfolio:
            if s.get_name() == stock.get_name() and s.get_price() == stock.get_price():
                if s.get_quantity() >= stock.get_quantity():
                    s.set_quantity(s.get_quantity() - stock.get_quantity())
                    if s.get_quantity() == 0:
                        self.portfolio.remove(s)
                    return True
        return False

    def buy_stock(self, stock):
        cost = stock.get_price() * stock.get_quantity()
        if self.cash_balance >= cost:
            self.add_stock(stock)
            self.cash_balance -= cost
            return True
        return False

    def sell_stock(self, stock):
        revenue = stock.get_price() * stock.get_quantity()
        if self.remove_stock(stock):
            self.cash_balance += revenue
            return True
        return False

    def get_portfolio(self):
        return [Stock(s.name, s.price, s.quantity) for s in self.portfolio]

    def get_cash_balance(self):
        return self.cash_balance

    def calculate_portfolio_value(self):
        total_value = 0.0
        for stock in self.portfolio:
            total_value += stock.get_price() * stock.get_quantity()
        return total_value

    def get_portfolio_summary(self):
        summary = []
        for stock in self.portfolio:
            summary.append(f"{stock.get_name()}: {stock.get_quantity()} shares at ${stock.get_price()} each")
        total_value = self.calculate_portfolio_value()
        summary.append(f"Total Value: ${total_value}")
        return "\n".join(summary)