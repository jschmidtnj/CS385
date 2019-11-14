import sys

def display_coin_row_table(C, F, S):
    def display_row(row, n):
        for i in range(n):
            sys.stdout.write('|')
            sys.stdout.write(str(row[i]).rjust(max_cell_width))
        sys.stdout.write('|\n')

    n = len(C)
    max_cell_width = len(str(max(max(C), max(F), n)))
    sys.stdout.write('index ')
    for i in range(n):
        sys.stdout.write('|')
        sys.stdout.write(str(i).rjust(max_cell_width))
    sys.stdout.write('|\n')
    print('-' * (7 + n * (max_cell_width + 1)))
    sys.stdout.write('    C ')
    display_row(C, n)
    sys.stdout.write('    F ')
    display_row(F, n)
    sys.stdout.write('    S ')
    display_row(S, n)

def coin_row_rec(C):
    def coin_row_helper(n):
        # Base case
        if n <= 0:
            return 0

        # Recurse
        return max(C[n] + coin_row_helper(n - 2), coin_row_helper(n - 1))

    C = [0] + C # Used to keep indexing the same as it's described
                # in the textbook.    
    return coin_row_helper(len(C) - 1)

def coin_row_mem(C):
    def coin_row_helper(n, memo):
        # Base case
        if n <= 0:
            return 0

        # If already computed, return value
        if n in memo:
            return memo[n]

        # Do work
        value = max(C[n] + coin_row_helper(n - 2, memo),
                    coin_row_helper(n - 1, memo))

        # Store value and return
        memo[n] = value
        return value

    C = [0] + C # Used to keep indexing the same as it's described
                # in the textbook.    
    return coin_row_helper(len(C) - 1, {})

def get_solution(C, F, S):
    solution = []
    n = len(F) - 1
    while n > 0:
        if F[n] > F[n - 1]:
            solution.append(C[n])
        n = S[n]
    solution.sort()
    return solution
    
def coin_row_dp(C):
    '''Determines the maximum amount of money subject to the constraint
       that no two coins adjacent in the initial row can be picked up.

       Args:
           C: a list of positive integers indicating the coin values

       Returns:
           The maximum amount of money that can be picked up as well as
           a list of the coins that are selected to create the maximum
           sum.
    '''
    C = [0] + C # Used to keep indexing the same as it's described
                # in the textbook.
    n = len(C)
    F = [0] * n
    S = [0] * n
    F[1] = C[1]
    for i in range(2, n):
        # F[i] = max(C[i] + F[i - 2], F[i - 1])
        val1 = C[i] + F[i - 2]
        val2 = F[i - 1]
        if val1 > val2:
            F[i] = val1
            S[i] = i - 2
        else:
            F[i] = val2
            S[i] = i - 1
    display_coin_row_table(C, F, S)
    return F[n - 1], get_solution(C, F, S)

if __name__ == '__main__':
    coins = [5, 1, 2, 10, 6, 2]
    solution = coin_row_dp(coins)
    print('Total (DP):', solution[0])
    print('Coins:', solution[1])
    print()
    print('Total (recursive):', coin_row_rec(coins))
    print('Total (memoized):', coin_row_mem(coins))
