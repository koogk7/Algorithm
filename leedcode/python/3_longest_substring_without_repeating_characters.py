class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        if len(s) == 0:
            return 0

        start_idx, end_idx = 0, 1
        ans = 0
        collector = {s[0]: True}

        is_end = start_idx == len(s) or end_idx >= len(s)

        while not is_end:
            """중복되면 start ++, 아니면 end를 ++"""
            cur_char = s[end_idx]

            if collector.get(cur_char):
                first_char = s[start_idx]
                collector.pop(first_char)
                ans = max(ans, end_idx - start_idx)
                start_idx += 1
            else:
                collector[cur_char] = True
                end_idx += 1

            is_end = start_idx == len(s) or end_idx >= len(s)

        return max(ans, end_idx - start_idx)