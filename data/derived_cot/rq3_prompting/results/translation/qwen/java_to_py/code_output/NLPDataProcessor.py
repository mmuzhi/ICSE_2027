class NLPDataProcessor:

    @staticmethod
    def construct_stop_word_list():
        return ["a", "an", "the"]

    @staticmethod
    def remove_stop_words(string_list, stop_word_list):
        result = []
        for string in string_list:
            words = string.split(' ')
            filtered_words = [word for word in words if word not in stop_word_list]
            result.append(filtered_words)
        return result

    @staticmethod
    def process(string_list):
        stop_word_list = NLPDataProcessor.construct_stop_word_list()
        return NLPDataProcessor.remove_stop_words(string_list, stop_word_list)