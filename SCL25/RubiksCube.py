
front = [['?' for x in range(3)] for y in range(3)]
back = [['?' for x in range(3)] for y in range(3)]
left = [['?' for x in range(3)] for y in range(3)]
right = [['?' for x in range(3)] for y in range(3)]
top = [['?' for x in range(3)] for y in range(3)]
down = [['?' for x in range(3)] for y in range(3)]

def read():
	ret = [[c for c in input()] for y in range(3)]
	return ret
	
def p():
	for i in range(3):
		print("   " + ''.join(top[i]) + "   ")
	for i in range(3):
		print(''.join(left[i]) + ''.join(front[i]) + ''.join(right[i]))
	for i in range(3):
		print("   " + ''.join(down[i]) + "   ")
	for i in range(3):
		print("   " + ''.join(back[i]) + "   ", flush=True)


def query(op):
	print(op, flush=True)
	return read()


curr = read()
for i in range(3):
	for j in range(3):
		front[i][j] = curr[i][j]

## two rings

query('U')
curr = query("D'")

for i in range(3):
	right[0][i] = curr[0][i]
	right[2][i] = curr[2][i]


query("U")
curr = query("D'")

for i in range(3):
	back[2][2-i] = curr[0][i]
	back[0][2-i] = curr[2][i]


query("U")
curr = query("D'")

for i in range(3):
	left[0][i] = curr[0][i]
	left[2][i] = curr[2][i]


query("U")
query("D'")

query("L")
curr = query("R'")

for i in range(3):
	top[i][0] = curr[i][0]
	top[i][2] = curr[i][2]

query("L")
curr = query("R'")

back[1][0] = curr[1][0]
back[1][2] = curr[1][2]


query("L")
curr = query("R'")

for i in range(3):
	down[i][0] = curr[i][0]
	down[i][2] = curr[i][2]


query("L")
query("R'")

query("U")
query("D'")

query("L")
curr = query("R'")

top[2][1] = curr[1][0]
top[0][1] = curr[1][2]


query("L")
query("R'")
query("L")
curr = query("R'")

down[0][1] = curr[1][0]
down[2][1] = curr[1][2]


query("L")
query("R'")
query("U'")
query("D")
query("L")
query("R'")
query("U")
curr = query("D'")

right[1][2] = curr[0][1]
right[1][0] = curr[2][1]


query("U")
curr = query("D'")
query("U")
curr = query("D'")

left[1][0] = curr[0][1]
left[1][2] = curr[2][1] 

print("A")
p()
