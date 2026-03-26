N = int(input())

ones = 0
twos = 0
impr = 0

arr = [int(x) for x in input().split()]
for v in arr:
    v = v%5 
    if v >= 3:
        v -= 5 
    impr += v 
    if v == -1:
        ones += 1
    if v == -2:
        twos += 1
    # print(v)

while ones >= 2 and ones > twos:
    ones -= 2 
    twos += 1
# print(ones, twos, impr)
tot = min(ones, twos) 
impr += tot * 5 
ones -= tot
twos -= tot 

impr += (twos // 2) * 5 

print(impr)