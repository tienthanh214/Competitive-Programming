class Solution:
    def stringMatching(self, words: list[str]) -> list[str]:
        answer = []
        for i in range(len(words)):
            for j in range(len(words)):
                if i != j:
                    if words[i] in words[j]:
                        answer.append(words[i])
                        break
        return answer