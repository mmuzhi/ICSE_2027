import re

class SplitSentence:
    def split_sentences(self, sentences_string):
        if not sentences_string:
            return []
        
        pattern = r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s'
        sentences = re.split(pattern, sentences_string)
        result = []
        for s in sentences:
            if s:
                s_clean = s.rstrip()
                if s_clean:
                    result.append(s_clean)
        return result

    def count_words(self, sentence):
        if not sentence:
            return 0
        
        cleaned_sentence = ''.join(c for c in sentence if c.isalpha() or c.isspace())
        words = cleaned_sentence.split()
        return len(words)

    def process_text_file(self, sentences_string):
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        for s in sentences:
            count = self.count_words(s)
            if count > max_count:
                max_count = count
        return max_count