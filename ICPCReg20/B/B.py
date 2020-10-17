from string import ascii_lowercase, ascii_uppercase

lookup = {
    ascii_lowercase[i]: i+1
    for i in range(26)
}

lookup = {**lookup, **{
    ascii_uppercase[i]: i+1
    for i in range(26)
}}

nums = list(map(int, list(input())))
pattern = list(input())

implied_length = sum([lookup[p] for p in pattern])
if implied_length != len(nums):
    print('non sequitur')
    import sys
    sys.exit(0)

digits = []
i = 0
while i < len(nums):
    p = pattern.pop(0)
    if p.isupper():
        i += lookup[p]
    else:
        for _ in range(lookup[p]):
            digits.append(nums[i])
            i += 1

ans = sum(digits)
print(ans)


