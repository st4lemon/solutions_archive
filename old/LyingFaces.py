"""
https://codeforces.com/gym/104479/problem/L

Adam Gasienica-Samek Contest 1 #L: Lying Faces

Problem: There are N (3 <= 10000) people numbered 1 to N, and each of them has a nose length unknown to you. Each person is either a liar or a truth teller. Truth tellers always tell the truth and liars always lie. It is known that there is at least one liar and there are more truth tellers than liars.

Your goal is to find out all the liars. To do that, you are allowed ask at most 10001 queries. In each query, you choose two distinct indices (1 <= a, b <= N), and ask the a-th person "What is the length of the b-th person's nose?". After answering the question, if the a-th person is a liar, their nose length increases by an unknown positive integer, which may be different every time.

Your program can submit queries to the jury program by printing the following line:
 - ? a b 
which asks the a-th person about the b-th person's nose length. After each query, the jury prints an integer x. Either:
 - x is a positive integer, which is the reply from the a-th person
 - x is -1, which indicates an invalid query or that you have used too many queries.

To submit, your program should send the output in the following format:
 - ! k p1 p2 ... pk
where pi represents the i-th liar.


Solution:
We initially ask all people (other than 1) about 1's nose length. This easily gives us the ground truth for 1's nose length; since there will always be more truth tellers than liars, the most frequent answer is 1's nose length (there is an exception for odd N which will be covered later). 

Then, we ask 1 about 2's nose length. If 1 is a liar, then their nose length will increase, so we find a truth-teller (any person who chose the correct nose length for 1 earlier) and ask about 1's new nose length. If it's the same, then 1 is a truth-teller; if not, 1 is a liar. This takes N+1 queries total.

In the case that N is odd, then it is possible that the number of truth-tellers and liars will be the same. However, we do know that 1 is a truth teller. Thus, we can use it to see if 2 is a truth-teller, which indicates whether the group that 2 belongs to is made of truth-tellers or liars. We ask 1 about 2, ask 2 about anyone, then ask 1 about 2 again to see if there is a change. This takes N+2 queries, which turns out to be under the limit of 10001 because N <= 9999 if N is odd. 


"""

def ask(a, b):
    print(f'? {a} {b}', flush=True)
    res = int(input())
    if res == -1:
        exit()
    return res


N = int(input())
ans = [0 for x in range(10001)]
freq = {}

for i in range(2, N+1):
    ans[i] = ask(i, 1)
    if ans[i] not in freq:
        freq[ans[i]] = 0
    freq[ans[i]] += 1

# split into odd/even cases


best = ans[2]
for k in freq:
    if freq[k] > freq[best]:
        best = k
    elif freq[k] == freq[best] == N//2 and N%2 == 1:
        best = -1
        break

if best == -1:
    # 1 is truth teller
    a = ask(1, 2)
    b = ask(2, 1)
    c = ask(1, 2)
    if a == c:
        best = ans[2]
    else:
        for i in range(3, N+1):
            if ans[i] == ans[2]:
                continue
            best = ans[i]
            break
    print(f'! {N//2}', end=' ')
    for i in range(2, N+1):
        if not ans[i] == best:
            print(i, end=' ')
    print()
    exit()

# best is the truth of 1

ask(1, 2)

liars = []
truer = -1
for i in range(2, N+1):
    if not ans[i] == best:
        liars.append(i)
    else:
        truer = i

if not ask(truer, 1) == best:
    liars.append(1)

liars.sort()

print(f'! {len(liars)}', end=' ')
for i in liars:
    print(i, end=' ')
print()


 
