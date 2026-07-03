import struct
from typing import List

def _double_equals(a: float, b: float) -> bool:
    """Compare two floats using Java's Double.compare semantics (bitwise)."""
    return struct.pack('>d', a) == struct.pack('>d', b)

class StockPortfolioTracker:
    class Stock:
        def __init__(self, name: str, price: float, quantity: int):
            self._name = name
            self._price = price
            self._quantity = quantity

        def getName(self) -> str:
            return self._name

        def getPrice(self) -> float:
            return self._price

        def getQuantity(self) -> int:
            return self._quantity

        def setQuantity(self, quantity: int) -> None:
            self._quantity = quantity

        def __eq__(self, other: object) -> bool:
            if not isinstance(other, StockPortfolioTracker.Stock):
                return False
            return (self._name == other._name and
                    _double_equals(self._price, other._price) and
                    self._quantity == other._quantity)

        def __hash__(self) -> int:
            return hash((self._name,
                         struct.pack('>d', self._price),
                         self._quantity))

        def __repr__(self) -> str:
            return f"{self._name}: {self._quantity} shares at ${self._price} each"

    def __init__(self, initial_cash_balance: float):
        self._initial_cash_balance = initial_cash_balance
        self._cash_balance = initial_cash_balance
        self._portfolio: List[StockPortfolioTracker.Stock] = []

    def addStock(self, stock: 'StockPortfolioTracker.Stock') -> None:
        for s in self._portfolio:
            if (s.getName() == stock.getName() and
                    _double_equals(s.getPrice(), stock.getPrice())):
                s.setQuantity(s.getQuantity() + stock.getQuantity())
                return
        self._portfolio.append(stock)

    def removeStock(self, stock: 'StockPortfolioTracker.Stock') -> bool:
        # Iterate over a shallow copy to avoid concurrent modification issues
        for s in self._portfolio[:]:
            if (s.getName() == stock.getName() and
                    _double_equals(s.getPrice(), stock.getPrice())):
                if s.getQuantity() >= stock.getQuantity():
                    s.setQuantity(s.getQuantity() - stock.getQuantity())
                    if s.getQuantity() == 0:
                        self._portfolio.remove(s)
                    return True
        return False

    def buyStock(self, stock: 'StockPortfolioTracker.Stock') -> bool:
        cost = stock.getPrice() * stock.getQuantity()
        if self._cash_balance >= cost:
            self.addStock(stock)
            self._cash_balance -= cost
            return True
        return False

    def sellStock(self, stock: 'StockPortfolioTracker.Stock') -> bool:
        revenue = stock.getPrice() * stock.getQuantity()
        if self.removeStock(stock):
            self._cash_balance += revenue
            return True
        return False

    def getPortfolio(self) -> List['StockPortfolioTracker.Stock']:
        return list(self._portfolio)

    def getCashBalance(self) -> float:
        return self._cash_balance

    def calculatePortfolioValue(self) -> float:
        total = 0.0
        for s in self._portfolio:
            total += s.getPrice() * s.getQuantity()
        return total

    def getPortfolioSummary(self) -> str:
        lines = [str(s) for s in self._portfolio]
        lines.append(f"Total Value: ${self.calculatePortfolioValue()}")
        return "\n".join(lines) + "\n"