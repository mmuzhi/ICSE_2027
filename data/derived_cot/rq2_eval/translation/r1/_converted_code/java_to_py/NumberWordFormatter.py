class NumberWordFormatter:
    NUMBER = ['', 'ONE', 'TWO', 'THREE', 'FOUR', 'FIVE', 'SIX', 'SEVEN', 'EIGHT', 'NINE']
    NUMBER_TEEN = ['TEN', 'ELEVEN', 'TWELVE', 'THIRTEEN', 'FOURTEEN', 'FIFTEEN', 'SIXTEEN', 'SEVENTEEN', 'EIGHTEEN', 'NINETEEN']
    NUMBER_TEN = ['TEN', 'TWENTY', 'THIRTY', 'FORTY', 'FIFTY', 'SIXTY', 'SEVENTY', 'EIGHTY', 'NINETY']
    NUMBER_MORE = ['', 'THOUSAND', 'MILLION', 'BILLION']
    NUMBER_SUFFIX = ['k', 'w', '', 'm', '', '', 'b', '', '', 't', '', '', 'p', '', '', 'e']

    def format(self, x):
        if x is None:
            return ''
        return self.format_string(str(x))

    def format_string(self, x):
        parts = x.split('.', 1)
        lstr = parts[0]
        rstr = parts[1] if len(parts) > 1 else ''
        lstrrev = lstr[::-1]
        mod = len(lstrrev) % 3
        if mod == 1:
            lstrrev += '00'
        elif mod == 2:
            lstrrev += '0'
        num_chunks = len(lstrrev) // 3
        a = [None] * num_chunks
        word_parts = []
        for i in range(num_chunks):
            start_index = 3 * i
            end_index = 3 * i + 3
            chunk_rev = lstrrev[start_index:end_index]
            chunk = chunk_rev[::-1]
            a[i] = chunk
            if chunk != '000':
                words_chunk = self.trans_three(chunk)
                magnitude = self.parse_more(i)
                if magnitude:
                    word_part = words_chunk + ' ' + magnitude
                else:
                    word_part = words_chunk
                word_parts.append(word_part)
        word_parts.reverse()
        lm_str = ' '.join(word_parts).strip()
        xs = ''
        if rstr != '':
            xs = 'AND CENTS ' + self.trans_two(rstr) + ' '
        if lm_str == '':
            return 'ZERO ONLY'
        else:
            return lm_str + ' ' + xs + 'ONLY'

    def trans_two(self, s):
        s_padded = s.rjust(2).replace(' ', '0')
        if s_padded[0] == '0':
            num = int(s_padded[1])
            return self.NUMBER[num]
        elif s_padded[0] == '1':
            num = int(s_padded)
            return self.NUMBER_TEEN[num - 10]
        elif s_padded[1] == '0':
            num_ten = int(s_padded[0])
            return self.NUMBER_TEN[num_ten - 1]
        else:
            ten_part = int(s_padded[0])
            unit_part = int(s_padded[1])
            return self.NUMBER_TEN[ten_part - 1] + ' ' + self.NUMBER[unit_part]

    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == '00':
            return self.NUMBER[int(s[0])] + ' HUNDRED'
        else:
            return self.NUMBER[int(s[0])] + ' HUNDRED AND ' + self.trans_two(s[1:])

    def parse_more(self, i):
        return self.NUMBER_MORE[i]