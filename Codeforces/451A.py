n, m = map(int, raw_input().split())
def f(n,m):
    if n == 0 or m == 0:
        return False
    return ~f(n-1,m-1)
if f(n,m):
    print 'Akshat'
else :
    print 'Malvika'
