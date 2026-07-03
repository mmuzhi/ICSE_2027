class NLPDataProcessor:
    def construct_stop_word_list(self):
        return ["a", "an", "the"]

    def remove_stop_words(self, string_list, stop_word_list):
        answer = []
        for s in string_list:
            words = s.split()  # splits on any whitespace, matching istringstream >> behavior
            filtered = [w for w in words if w not in stop_word_list]
            answer.append(filtered)
        return answer

    def process(self, string_list):
        stop_word_list = self.construct_stop_word_list()
        return self.remove_stop_words(string_list, stop_word_list)