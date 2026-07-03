class BitStatusUtil:
    @staticmethod
    def add(states, stat):
        BitStatusUtil.check_two_args(states, stat)
        return states | stat

    @staticmethod
    def has(states, stat):
        BitStatusUtil.check_two_args(states, stat)
        return (states & stat) == stat

    @staticmethod
    def remove(states, stat):
        BitStatusUtil.check_two_args(states, stat)
        if BitStatusUtil.has(states, stat):
            return states ^ stat
        return states

    @staticmethod
    def check_two_args(a, b):
        for num in (a, b):
            if num < 0:
                raise ValueError(f"{num} must be greater than or equal to 0")
            if num % 2 != 0:
                raise ValueError(f"{num} not even")