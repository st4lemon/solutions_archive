front = input()
side = [input() for i in range(4)]
bot = input()

N = 16

dp = [[100000 for y in range(26)] for x in range(17)]
dp[0][0] = 0

for i in range(16):
	# place dice as is
	c = ord(front[i]) - ord('A')
	targ = c
	if front[i] == 'Q':
		targ = ord('U') - ord('A')
	for k in range(c+1):
		dp[i+1][targ] = min(dp[i+1][targ], dp[i][k])
	for j in range(4):
		c = ord(side[j][i]) - ord('A')
		targ = c
		if side[j][i] == 'Q':
			targ = ord('U') - ord('A')
		for k in range(c+1):
			dp[i+1][targ] = min(dp[i+1][targ], dp[i][k]+1)
	c = ord(bot[i]) - ord('A')
	targ = c
	if bot[i] == 'Q':
		targ = ord('U') - ord('A')
	for k in range(c+1):
		dp[i+1][targ] = min(dp[i+1][targ], dp[i][k]+2)


ans = min(dp[N])
if ans >= 100000:
	print("impossible")
else:
	print(ans)

	
