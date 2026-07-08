class NLPDataProcessor:

    def construct_stop_word_list(self):
        return ["a", "an", "the"]

    def remove_stop_words(self, string_list, stop_word_list):
        result = []
        # Convert to a set for O(1) lookups, which matches Java's removeAll behavior 
        # without changing the outcome, only improving performance.
        stop_word_set = set(stop_word_list)
        
        for string in string_list:
            words = self._java_split_on_space(string)
            # List comprehension acts identantly to Java's removeAll
            filtered_words = [word for word in words if word not in stop_word_set]
            result.append(filtered_words)
            
        return result

    def process(self, string_list):
        stop_word_list = self.construct_stop_word_list()
        return self.remove_stop_words(string_list, stop_word_list)

    @staticmethod
    def _java_split_on_space(s):
        """
        Helper to exactly match Java's String.split(" ") behavior.
        Java's split removes trailing empty strings, but returns an array 
        containing the original string if no matching delimiter is found.
        Python's split(" ") keeps trailing empty strings.
        """
        if " " not in s:
            return [s]
        
        parts = s.split(" ")
        # Remove trailing empty strings to emulate Java's split regex behavior
        while parts and parts[-1] == "":
            parts.pop()
            
        return parts