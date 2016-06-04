# You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.
# For example, given:
# s: "barfoothefoobarman"
# words: ["foo", "bar"]
# You should return the indices: [0,9].
# (order does not matter).

class Solution(object):
    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """
        word_num = len(words)
        if word_num == 0:
            return []
        dict = {}
        for i in words:
            if i in dict:
                dict[i] += 1
            else:
                dict[i] = 1
        word_len = len(words[0])
        res = []
        for i in range(len(s) - word_len * word_num + 1):
            curr = {}
            count = 0
            while count < word_num:
                word = s[i + count * word_len:i + (count + 1) * word_len]
                if word not in dict:
                    break
                if word not in curr:
                    curr[word] = 1
                else:
                    curr[word] += 1
                if curr[word] > dict[word]:
                    break
                count += 1
            if count == word_num:
                res.append(i)
        return res
            
