import types
from collections.abc import Mapping

class ReadOnlyNestedMap(Mapping):
    def __init__(self, data):
        self._data = data
    
    def __getitem__(self, key):
        inner_dict = self._data[key]
        return types.MappingProxyType(inner_dict)
    
    def __len__(self):
        return len(self._data)
    
    def __iter__(self):
        return iter(sorted(self._data.keys()))

class Warehouse:
    def __init__(self):
        self.inventory_ = {}
        self.orders_ = {}
    
    def add_product(self, product_id, name, quantity):
        if product_id in self.inventory_:
            current_quantity = int(self.inventory_[product_id]['quantity'])
            new_quantity = current_quantity + quantity
            self.inventory_[product_id]['quantity'] = str(new_quantity)
        else:
            self.inventory_[product_id] = {
                'name': name,
                'quantity': str(quantity)
            }
    
    def update_product_quantity(self, product_id, quantity):
        if product_id in self.inventory_:
            current_quantity = int(self.inventory_[product_id]['quantity'])
            new_quantity = current_quantity + quantity
            self.inventory_[product_id]['quantity'] = str(new_quantity)
    
    def get_product_quantity(self, product_id):
        if product_id in self.inventory_:
            return int(self.inventory_[product_id]['quantity'])
        return 0
    
    def create_order(self, order_id, product_id, quantity):
        available_quantity = self.get_product_quantity(product_id)
        if available_quantity >= quantity:
            self.update_product_quantity(product_id, -quantity)
            self.orders_[order_id] = {
                'product_id': str(product_id),
                'quantity': str(quantity),
                'status': 'Shipped'
            }
            return True
        return False
    
    def change_order_status(self, order_id, status):
        if order_id in self.orders_:
            self.orders_[order_id]['status'] = status
            return True
        return False
    
    def track_order(self, order_id):
        if order_id in self.orders_:
            return self.orders_[order_id]['status']
        return ""
    
    def orders(self):
        return ReadOnlyNestedMap(self.orders_)
    
    def inventory(self):
        return ReadOnlyNestedMap(self.inventory_)