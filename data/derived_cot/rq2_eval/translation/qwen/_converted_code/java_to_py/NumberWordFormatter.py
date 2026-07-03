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
        if lstr == '':
            lstr = '0'
        lstrrev = lstr[::-1]
        if len(lstrrev) % 3 == 1:
            lstrrev += '00'
        elif len(lstrrev) % 3 == 2:
            lstrrev += '0'
        chunks = [lstrrev[i:i + 3] for i in range(0, len(lstrrev), 3)]
        a = [chunk[::-1] for chunk in chunks]
        lm = []
        for i in range(len(a)):
            if a[i] != '000':
                s = self.trans_three(a[i]) + ' ' + self.parse_more(i) + ' '
                lm.insert(0, s)
            else:
                s = self.trans_three(a[i])
                lm.insert(0, s)
        left_part = ''.join(lm).strip()
        if left_part == '':
            return 'ZERO ONLY'
        else:
            if rstr:
                xs = 'AND CENTS ' + self.trans_two(rstr) + ' '
            else:
                xs = ''
            return left_part + ' ' + xs + 'ONLY'

    def parse_more(self, i):
        return self.NUMBER_MORE[i]

    def trans_two(self, s):
        s = s.zfill(2)
        if s[0] == '0':
            return self.NUMBER[int(s[1])] if s[1] != '0' else ''
        elif s[0] == '1':
            return self.NUMBER_TEEN[int(s) - 10]
        elif s[1] == '0':
            return self.NUMBER_TEN[int(s[0]) - 1]
        else:
            return self.NUMBER_TEN[int(s[0]) - 1] + ' ' + self.NUMBER[int(s[1])]

    def trans_three(self, s):
        if s[0] == '0':
            return self.trans_two(s[1:])
        elif s[1:] == '00':
            return self.NUMBER[int(s[0])] + ' HUNDRED'
        else:
            return self.NUMBER[int(s[0])] + ' HUNDRED AND ' + self.trans_two(s[1:])