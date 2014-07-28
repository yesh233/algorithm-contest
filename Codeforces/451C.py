T = int(raw_input())
for _ in range(T):
    n,k,d1,d2 = map(int, raw_input().split())
    if n % 3 != 0:
        result = 'no'
    else :
        m = n / 3
        if d1+d2 <= k and d1+d2 <= m:
            
