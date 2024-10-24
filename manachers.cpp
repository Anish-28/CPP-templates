// ref : https://github.com/mission-peace/interview/blob/master/src/com/interview/string/LongestPalindromeSubstring.java

// input = abcde
// newInput = $a$b$c$d$e$
// ind = 4 will indicate max palindrome length with center b (in abcd b is center)

void manachers(string input)
{
    int index = 0, siz = 2 * input.size() + 1;

    char newInput[siz];
    for (int i = 0; i < siz; i++)
    {
        if (i & 1)
        {
            newInput[i] = input[index++];
        }
        else
        {
            newInput[i] = '$';
        }
    }

    T.resize(siz, 0);
    int start = 0;
    int end = 0;

    for (int i = 0; i < siz;)
    {
        while (start > 0 && end < siz - 1 &&
               newInput[start - 1] == newInput[end + 1])
        {
            start--;
            end++;
        }

        T[i] = end - start + 1;

        if (end == T.size() - 1)
        {
            // remove next 3 lines if you only need the longest palindrome
            // as we won't get a longer palindrome anymore
            for (int j = i + 1; j <= end; j++)
            {
                T[j] = min(T[i - (j - i)], 2 * (end - j) + 1);
            }
            break;
        }

        int newCenter = end + (i % 2 == 0 ? 1 : 0);

        for (int j = i + 1; j <= end; j++)
        {
            T[j] = min(T[i - (j - i)], 2 * (end - j) + 1);
            if (j + T[i - (j - i)] / 2 == end)
            {
                newCenter = j;
                break;
            }
        }

        i = newCenter;
        end = i + T[i] / 2;
        start = i - T[i] / 2;
    }

    // T[i] / 2 will be length of palindrom with center i
}