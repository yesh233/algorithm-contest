n, m = map(int, raw_input().split())


def f(nn, mm):
    if nn == 0 or mm == 0:
        return False
    return ~f(nn - 1, mm - 1)


if f(n, m):
    print 'Akshat'
else:
    print 'Malvika'