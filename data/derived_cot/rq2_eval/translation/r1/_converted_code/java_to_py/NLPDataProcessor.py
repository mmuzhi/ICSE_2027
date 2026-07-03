class NLPDataProcessor:

    def construct_stop_word_list(self):
        return ['a', 'an', 'the']

    def remove_stop_words(self, stringList, stopWordList):
        result = []
        for s in stringList:
            words = s.split(' ')
            filtered_words = [word for word in words if word not in stopWordList]
            result.append(filtered_words)
        return result

    def process(self, stringList):
        stopWordList = self.construct_stop_word_list()
        return self.remove_stop_words(stringList, stopWordList)