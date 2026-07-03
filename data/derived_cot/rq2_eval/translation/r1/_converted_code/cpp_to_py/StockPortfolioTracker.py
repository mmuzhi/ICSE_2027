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

class StockSummary:
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def __eq__(self, other):
        if not isinstance(other, StockSummary):
            return False
        return (self.name == other.name and 
                self.value == other.value)

class StockPortfolioTracker:
    def __init__(self, cash_balance):
        self.portfolio = []
        self.cash_balance = cash_balance

    def add_stock(self, stock):
        for s in self.portfolio:
            if s.name == stock.name:
                s.quantity += stock.quantity
                return
        self.portfolio.append(Stock(stock.name, stock.price, stock.quantity))

    def remove_stock(self, stock):
        for i, s in enumerate(self.portfolio):
            if s.name == stock.name:
                if s.quantity >= stock.quantity:
                    s.quantity -= stock.quantity
                    if s.quantity == 0:
                        del self.portfolio[i]
                    return True
        return False

    def buy_stock(self, stock):
        total_cost = stock.price * stock.quantity
        if total_cost > self.cash_balance:
            return False
        self.add_stock(stock)
        self.cash_balance -= total_cost
        return True

    def sell_stock(self, stock):
        if not self.remove_stock(stock):
            return False
        self.cash_balance += stock.price * stock.quantity
        return True

    def calculate_portfolio_value(self):
        total_value = self.cash_balance
        for stock in self.portfolio:
            total_value += stock.price * stock.quantity
        return total_value

    def get_portfolio_summary(self):
        summary = []
        for stock in self.portfolio:
            summary.append(StockSummary(stock.name, self.get_stock_value(stock)))
        total_value = self.calculate_portfolio_value()
        return (total_value, summary)

    def get_stock_value(self, stock):
        return stock.price * stock.quantity

    def get_portfolio(self):
        return list(self.portfolio)

    def get_cash_balance(self):
        return self.cash_balance

    def set_portfolio(self, portfolio):
        self.portfolio = [Stock(s.name, s.price, s.quantity) for s in portfolio]