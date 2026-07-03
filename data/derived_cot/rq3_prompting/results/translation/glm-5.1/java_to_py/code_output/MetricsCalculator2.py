class MetricsCalculator2:

    class Tuple:
        def __init__(self, lst, total_num):
            self.list = lst
            self.total_num = total_num

        def get_list(self):
            return self.list

        def get_total_num(self):
            return self.total_num

    @staticmethod
    def mrr(data):
        if not isinstance(data, (list, MetricsCalculator2.Tuple)):
            raise IllegalArgumentException("the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple")

        if isinstance(data, MetricsCalculator2.Tuple):
            sub_list = data.get_list()
            total_num = data.get_total_num()

            if total_num == 0:
                return 0.0

            mr = 0.0
            for i, val in enumerate(sub_list):
                if val == 1:
                    mr = 1.0 / (i + 1)
                    break
            return mr
        else:
            tuple_list = data
            separate_result = []

            for tup in tuple_list:
                sub_list = tup.get_list()
                total_num = tup.get_total_num()

                if total_num == 0:
                    separate_result.append(0.0)
                else:
                    mr = 0.0
                    for i, val in enumerate(sub_list):
                        if val == 1:
                            mr = 1.0 / (i + 1)
                            break
                    separate_result.append(mr)

            if not separate_result:
                return 0.0
            return sum(separate_result) / len(separate_result)

    @staticmethod
    def map(data):
        if not isinstance(data, (list, MetricsCalculator2.Tuple)):
            raise IllegalArgumentException("the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple")

        if isinstance(data, MetricsCalculator2.Tuple):
            sub_list = data.get_list()
            total_num = data.get_total_num()

            if total_num == 0:
                return 0.0

            ap = 0.0
            count = 0
            for i, val in enumerate(sub_list):
                if val == 1:
                    count += 1
                    ap += count / (i + 1.0)
            return ap / total_num
        else:
            tuple_list = data
            separate_result = []

            for tup in tuple_list:
                sub_list = tup.get_list()
                total_num = tup.get_total_num()

                if total_num == 0:
                    separate_result.append(0.0)
                else:
                    ap = 0.0
                    count = 0
                    for i, val in enumerate(sub_list):
                        if val == 1:
                            count += 1
                            ap += count / (i + 1.0)
                    separate_result.append(ap / total_num)

            if not separate_result:
                return 0.0
            return sum(separate_result) / len(separate_result)


class IllegalArgumentException(Exception):
    pass