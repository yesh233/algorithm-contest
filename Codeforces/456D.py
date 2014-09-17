class tree(object):
    def __init__(self, c=''):
	self.c = c 
	self.sons = {}
    
    def insert(self,s):
	if s == '':
	    return
	if self.sons.has_key(s[0]) == False:
	    self.sons[s[0]] = tree(s[0])
        self.sons[s[0]].insert(s[1:])

    def cal(self):
	if self.sons == {}:
	    return 1
	flag = 1
	for i in self.sons.keys():
	    if self.sons[i].cal() == 1: 
		flag = 0
        return flag

n, k = map(int, raw_input().split())
s = [raw_input() for i in range(n)]
r = tree()
for i in s:
    r.insert(i)

flag = 0
for i in r.sons.keys():
    if r.sons[i].cal() == 1:
	flag = 1
if flag == 1 and k % 2 == 0:
    flag = 0
if flag == 1:
    print 'First'
else :
    print 'Second'
