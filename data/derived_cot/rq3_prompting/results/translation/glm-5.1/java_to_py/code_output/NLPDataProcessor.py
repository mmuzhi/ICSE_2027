class NLPDataProcessor:

    def construct_stop_word_list(self):
        return ["a", "an", "the"]

    def remove_stop_words(self, string_list, stop_word_list):
        result = []
        for string in string_list:
            words = [w for w in string.split(" ") if w not in stop_word_list]
            result.append(words)
        return result

    def process(self, string_list):
        stop_word_list = self.construct_stop_word_list()
        return self.remove_stop_words(string_list, stop_word_list)