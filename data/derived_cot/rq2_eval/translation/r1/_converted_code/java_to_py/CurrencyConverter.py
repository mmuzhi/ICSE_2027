class _CurrencySet:

    def __init__(self, rates_dict):
        self.rates_dict = rates_dict

    def __contains__(self, item):
        return item in self.rates_dict

    def __iter__(self):
        return iter(self.rates_dict)

    def __len__(self):
        return len(self.rates_dict)

    def remove(self, item):
        if item in self.rates_dict:
            del self.rates_dict[item]
            return True
        return False

    def add(self, item):
        raise RuntimeError('UnsupportedOperationException')

    def __repr__(self):
        return f'_CurrencySet({set(self.rates_dict.keys())})'

class CurrencyConverter:

    def __init__(self):
        self.rates = {'USD': 1.0, 'EUR': 0.85, 'GBP': 0.72, 'JPY': 110.15, 'CAD': 1.23, 'AUD': 1.34, 'CNY': 6.4}

    def convert(self, amount, from_currency, to_currency):
        if from_currency == to_currency:
            return amount
        if from_currency not in self.rates or to_currency not in self.rates:
            return -1
        from_rate = self.rates[from_currency]
        to_rate = self.rates[to_currency]
        converted_amount = amount / from_rate * to_rate
        return converted_amount

    def get_supported_currencies(self):
        return _CurrencySet(self.rates)

    def add_currency_rate(self, currency, rate):
        if currency in self.rates:
            return False
        self.rates[currency] = rate
        return True

    def update_currency_rate(self, currency, new_rate):
        if currency not in self.rates:
            return False
        self.rates[currency] = new_rate
        return True

    def getRates(self):
        return self.rates