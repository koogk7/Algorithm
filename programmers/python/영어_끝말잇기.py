def solution(n, words):
    """
    1번 부터 순서대로 1, 2, -> 마지막 -> 1
    마지막 문자로 시작하는 단어, 이전에 등장했던 단어 x, 한글자 x
    
    n, words -> 가장 먼저 탈락 번호, 몇 번째 턴인지
    n = 10, words = 100
    단어의 길이 50
    
    이전에 등장 단어 -> dict로 저장 o(1)
    사람 번호는 -> (i % n) + 1
    턴 수는 -> (i // n) + 1
    """
    used_words = {}
    last_char = None

    for i, word in enumerate(words):
        if i > 0 and (word in used_words or word[0] != last_char):
            return [(i % n) + 1, (i // n) + 1]

        last_char = word[-1]
        used_words[word] = True

    return [0, 0]
