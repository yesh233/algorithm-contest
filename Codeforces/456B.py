n = raw_input()
n = int(n[-2:])%4
a = [[1,1,1,1],[1,2,4,3],[1,3,4,2],[1,4,1,4]] 
print (a[0][n]+a[1][n]+a[2][n]+a[3][n])%5