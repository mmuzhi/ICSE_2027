class StockPortfolioTracker:

    class Stock:
        def __init__(self, name, price, quantity):
            self.name = name
            self.price = price
            self.quantity = quantity

        def __eq__(self, other):
            if not isinstance(other, Stock):
                return False
            return (self.name == other.name and 
                    self.price == other.price and 
                    self.quantity == other.quantity)

        def __hash__(self):
            return hash((self.name, self.price, self.quantity))

        def __str__(self):
            return f"{self.name}: {self.quantity} shares at ${self.price} each"

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
        for i, s in enumerate(self.portfolio):
            if s.name == stock.name and s.price == stock.price:
                if s.quantity >= stock.quantity:
                    s.quantity -= stock.quantity
                    if s.quantity == 0:
                        del self.portfolio[i]
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
        return self.portfolio.copy()

    def get_cash_balance(self):
        return self.cash_balance

    def calculate_portfolio_value(self):
        total_value = 0.0
        for stock in self.portfolio:
            total_value += stock.price * stock.quantity
        return total_value

    def get_portfolio_summary(self):
        lines = []
        for stock in self.portfolio:
            lines.append(str(stock))
        lines.append(f"Total Value: ${self.calculate_portfolio_value()}")
        return "\n".join(lines)