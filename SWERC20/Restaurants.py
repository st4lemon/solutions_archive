import heapq 

N, M = map(int, input().split())

unmatched = set()
reqs = [[] for y in range(M)] # requests per restaurant
customers = [] # preferences of customers
pref = [0 for x in range(N)] # current request of customer
restaurants = [{} for y in range(M)] # preferences of each restaurant

cap = [int(input()) for y in range(M)]

for i in range(N):
    customers.append([int(x)-1 for x in input().split()]) # list of first customer's preferences
    unmatched.add(i)

for j in range(M):
    p = [int(x)-1 for x in input().split()]
    for i in range(len(p)):
        restaurants[j][p[i]] = i # p[i] is the restaurant's i-th favorite 

while len(unmatched) > 0:
    change = False
    rqd = set()
    for x in unmatched:
        # propose to 1 restaurant
        if pref[x] >= len(customers[x]):
            continue
        i = customers[x][pref[x]] # pick the pref[x]-th request of customer x
        heapq.heappush(reqs[i], (-restaurants[i][x], x))
        rqd.add(i)
        change = True
    unmatched.clear()

    for y in rqd:
        while len(reqs[y]) > cap[y]:
            _, c = heapq.heappop(reqs[y])
            pref[c] += 1 # for the customer, go to the next preference. 
            unmatched.add(c)
    if not change:
        break

ans = []
for r in reqs:
    for c in r:
        ans.append(c[1]+1)
ans.sort()

for a in ans:
    print(a)

