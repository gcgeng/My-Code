def to2(x):
    ans = ''
    while x:
        ans = str(x % 2) + ans
        x = int(x / 2)
    return ans
def pow_mod(x, b, p):
    ans = 1
    while b:
        if b & 1:
            ans = ans * x % p
        x = x * x % p
        b = b >> 1
    return ans
