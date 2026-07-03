class Stock:
    def __init__(self, name: str, price: float, quantity: int):
        self.name = name
        self.price = price
        self.quantity = quantity

    def __eq__(self, other):
        if not isinstance(other, Stock):
            return NotImplemented
        return (self.name == other.name and
                self.price == other.price and
                self.quantity == other.quantity)


class StockSummary:
    def __init__(self, name: str, value: float):
        self.name = name
        self.value = value

    def __eq__(self, other):
        if not isinstance(other, StockSummary):
            return NotImplemented
        return self.name == other.name and self.value == other.value


class StockPortfolioTracker:
    def __init__(self, cash_balance: float):
        self.cash_balance = cash_balance
        self.portfolio = []

    def add_stock(self, stock: Stock) -> None:
        for pf in self.portfolio:
            if pf.name == stock.name:
                pf.quantity += stock.quantity
                return
        self.portfolio.append(stock)

    def remove_stock(self, stock: Stock) -> bool:
        for i, pf in enumerate(self.portfolio):
            if pf.name == stock.name and pf.quantity >= stock.quantity:
                pf.quantity -= stock.quantity
                if pf.quantity == 0:
                    del self.portfolio[i]
                return True
        return False

    def buy_stock(self, stock: Stock) -> bool:
        cost = stock.price * stock.quantity
        if cost > self.cash_balance:
            return False
        self.add_stock(stock)
        self.cash_balance -= cost
        return True

    def sell_stock(self, stock: Stock) -> bool:
        if not self.remove_stock(stock):
            return False
        self.cash_balance += stock.price * stock.quantity
        return True

    def calculate_portfolio_value(self) -> float:
        total = self.cash_balance
        for stock in self.portfolio:
            total += stock.price * stock.quantity
        return total

    def get_portfolio_summary(self):
        summary = []
        for stock in self.portfolio:
            summary.append(StockSummary(stock.name, self.get_stock_value(stock)))
        return (self.calculate_portfolio_value(), summary)

    def get_stock_value(self, stock: Stock) -> float:
        return stock.price * stock.quantity

    def get_portfolio(self):
        return self.portfolio

    def get_cash_balance(self) -> float:
        return self.cash_balance

    def set_portfolio(self, portfolio):
        self.portfolio = portfolio