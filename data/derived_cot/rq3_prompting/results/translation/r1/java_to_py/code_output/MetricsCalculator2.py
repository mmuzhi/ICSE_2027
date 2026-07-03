from typing import List, Union


class Tuple:
    def __init__(self, lst: List[int], total_num: int):
        self.list = lst
        self.totalNum = total_num


class MetricsCalculator2:

    @staticmethod
    def mrr(data: Union[Tuple, List[Tuple]]) -> float:
        if not isinstance(data, (list, Tuple)):
            raise ValueError("the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple")

        if isinstance(data, Tuple):
            sub_list = data.list
            total_num = data.totalNum
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
                sub_list = tup.list
                total_num = tup.totalNum
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
    def map(data: Union[Tuple, List[Tuple]]) -> float:
        if not isinstance(data, (list, Tuple)):
            raise ValueError("the input must be a tuple([0,...,1,...],int) or a iteration of list of tuple")

        if isinstance(data, Tuple):
            sub_list = data.list
            total_num = data.totalNum
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
                sub_list = tup.list
                total_num = tup.totalNum
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