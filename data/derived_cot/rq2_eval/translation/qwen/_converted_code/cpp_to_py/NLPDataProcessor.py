class NLPDataProcessor:
    @staticmethod
    def construct_stop_word_list():
        return ["a", "an", "the"]

    @staticmethod
    def remove_stop_words(string_list, stop_word_list):
        return [
            [word for word in str_line.split() if word not in stop_word_list]
            for str_line in string_list
        ]

    def process(self, string_list):
        stop_word_list = self.construct_stop_word_list()
        return self.remove_stop_words(string_list, stop_word_list)