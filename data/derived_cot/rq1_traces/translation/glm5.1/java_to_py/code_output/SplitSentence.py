import re

class SplitSentence:

    def split_sentences(self, sentences_string):
        sentences = []
        pattern = re.compile(r'(?<!\w\.\w.)(?<![A-Z][a-z]\.)(?<=\.|\?)\s')
        last_end = 0
        
        for match in pattern.finditer(sentences_string):
            sentences.append(sentences_string[last_end:match.end() - 1])
            last_end = match.end()
            
        if last_end < len(sentences_string):
            sentences.append(sentences_string[last_end:])
            
        return sentences

    def _java_split_on_whitespace(self, s):
        # Java's split() by default removes trailing empty strings, 
        # but returns an array containing one empty string for an empty input.
        if not s:
            return [""]
        
        parts = re.split(r'\s+', s)
        # Remove trailing empty strings to match Java's split("\\s+") behavior
        while parts and parts[-1] == "":
            parts.pop()
            
        return parts

    def count_words(self, sentence):
        cleaned_sentence = re.sub(r'[^a-zA-Z\s]', '', sentence)
        words = self._java_split_on_whitespace(cleaned_sentence)
        return len(words)

    def process_text_file(self, sentences_string):
        sentences = self.split_sentences(sentences_string)
        max_count = 0
        
        for sentence in sentences:
            count = self.count_words(sentence)
            if count > max_count:
                max_count = count
                
        return max_count