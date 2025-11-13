

N, W = map(int, input().split())

mills = []

for i in range(N):
	x, y = map(int, input().split())
	mills.append((y, x))



mills.sort()

time = 0
rate = 0

for t, r in mills:
	# update time and ra
	if (t-time) * rate >= W:
		time += W / rate
		W = 0
		break;
	W -= rate * (t - time)
	time = t
	rate += 2*r 
	# print(time, rate, t, r, W)
	
# print(W, time)


print(2*(time + W / rate))
	 

