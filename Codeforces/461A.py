n = int(raw_input())
a = map(int, raw_input().split())
a.sort()
if n == 1:
    b = [1]
else :
    b = range(2,n)+[n,n]
print sum([a[i]*b[i] for i in range(n)])