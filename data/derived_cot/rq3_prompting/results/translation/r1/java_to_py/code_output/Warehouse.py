class Warehouse:
    class Product:
        def __init__(self, name: str, quantity: int):
            self.name = name
            self.quantity = quantity

        def addQuantity(self, quantity: int):
            self.quantity += quantity

        def getQuantity(self) -> int:
            return self.quantity

    class Order:
        def __init__(self, productId: int, quantity: int, status: str):
            self.productId = productId
            self.quantity = quantity
            self.status = status

        def getStatus(self) -> str:
            return self.status

        def setStatus(self, status: str):
            self.status = status

    def __init__(self):
        self.inventory = {}
        self.orders = {}

    def addProduct(self, productId: int, name: str, quantity: int):
        if productId in self.inventory:
            self.inventory[productId].addQuantity(quantity)
        else:
            self.inventory[productId] = self.Product(name, quantity)

    def updateProductQuantity(self, productId: int, quantity: int):
        if productId in self.inventory:
            self.inventory[productId].addQuantity(quantity)

    def getProductQuantity(self, productId: int) -> int:
        if productId in self.inventory:
            return self.inventory[productId].getQuantity()
        else:
            return -1

    def createOrder(self, orderId: int, productId: int, quantity: int) -> bool:
        if productId in self.inventory and self.inventory[productId].getQuantity() >= quantity:
            self.inventory[productId].addQuantity(-quantity)
            self.orders[orderId] = self.Order(productId, quantity, "Shipped")
            return True
        else:
            return False

    def changeOrderStatus(self, orderId: int, status: str) -> bool:
        if orderId in self.orders:
            self.orders[orderId].setStatus(status)
            return True
        else:
            return False

    def trackOrder(self, orderId: int) -> str:
        if orderId in self.orders:
            return self.orders[orderId].getStatus()
        else:
            return None