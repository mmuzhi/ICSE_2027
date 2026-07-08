class NumericEntityUnescaper:
    def __init__(self):
        pass

    def replace(self, input_str: str) -> str:
        out = []
        pos = 0
        length = len(input_str)
        
        if not input_str:
            return ""
        
        # Using `pos + 2 < length` avoids the unsigned integer underflow bug 
        # present in the C++ code (`pos < length - 2` for length < 2) while 
        # preserving the exact same logical behavior for valid string lengths.
        while pos + 2 < length:
            if input_str[pos] == '&' and input_str[pos + 1] == '#':
                start = pos + 2
                is_hex = False

                if start < length and (input_str[start] == 'x' or input_str[start] == 'X'):
                    start += 1
                    is_hex = True

                if start == length:
                    return "".join(out)

                end = start
                while end < length and self.is_hex_char(input_str[end]):
                    end += 1

                if end < length and input_str[end] == ';':
                    try:
                        number_str = input_str[start:end]
                        if is_hex:
                            # number_str is guaranteed to only contain valid hex characters
                            entity_value = int(number_str, 16)
                        else:
                            # C++'s stringstream >> int reads as many consecutive decimal digits as possible.
                            # It stops at the first non-digit and succeeds if at least one digit was read.
                            i = 0
                            while i < len(number_str) and '0' <= number_str[i] <= '9':
                                i += 1
                            if i == 0:
                                return "".join(out)  # Equivalent to ss.fail()
                            entity_value = int(number_str[:i])

                        # static_cast<char> truncates to 8 bits. 
                        # chr(... & 0xFF) perfectly mimics this behavior in Python.
                        out.append(chr(entity_value & 0xFF))
                        pos = end + 1
                        continue
                    except ValueError:
                        # Catches conversion failures (e.g., empty string for hex),
                        # equivalent to the C++ catching std::exception or ss.fail()
                        return "".join(out)

            out.append(input_str[pos])
            pos += 1

        return "".join(out)

    @staticmethod
    def is_hex_char(c: str) -> bool:
        # Replicates C++ std::isdigit and std::tolower logic for ASCII
        return ('0' <= c <= '9') or ('a' <= c <= 'f') or ('A' <= c <= 'F')