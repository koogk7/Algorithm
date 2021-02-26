class Solution:
    def decodeString(self, s: str) -> str:
        """
        - 괄호는 항상 stack을 생각하자!

        1. 여는 괄호를 만나면 스택에 현재 가지고 있는 number와 ''를 추가하고 number 초기화
        2. 닫는 괄호를 만나면 스택의 top을 pop하고 다음 top의 값을 +
        3. 숫자를 만나면 number를 업데이트
        4. 다른 문자열이면 현재 탑의 +
        """
        st = [{'number': '', 'value': ''}]
        number = ''
        numbers = [str(i) for i in range(0, 10)]

        for char in s:
            if char == '[':
                st.append({'number': self.parse_number(number), 'value': ''})
                number = ''
            elif char == ']':
                top = st.pop()
                st[-1]['value'] += top['value'] * top['number']
            elif char in numbers:
                number = number + char
            else:
                st[-1]['value'] += char

        return st[-1]['value']

    def parse_number(self, c: str) -> int:
        return int(c) if c else 1