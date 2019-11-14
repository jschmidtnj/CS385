'''
@author: Brian Borowski

Created on December 1, 2014
Last modified on June 26, 2017

Dynamic Programming - Robot Coin Collection
'''
import sys

def get_solution(F):
    '''Backtracks over the table of partial sums to determine the
       cells visited on the path from the top left to bottom right
       with the most value.

       Returns:
           A list of cell coordinates.
    '''
    solution = []
    m = len(F[0]) - 1
    n = len(F) - 1
    while m > 0 and n > 0:
        solution.append((n, m))
        if F[n-1][m] >= F[n][m-1]:
            n -= 1
        else:
            m -= 1
    while n > 0:
        solution.append((n, 0))
        n -= 1
    while m > 0:
        solution.append((0, m))
        m -= 1
    solution.append((0, 0))
    solution.reverse()
    return solution

def display_table(T, use_letters = False):
    '''Displays matrix T on the screen formatted as a table.

       Args:
           T: the matrix to display
           use_letters: whether or not to display indices as letters
               i.e., Display 'A' instead of '0'.
    '''
    m = len(T[0])
    n = len(T)
    max_val = 0
    for row in range(0, n):
        for col in range(0, m):
            if not T[row][col] is None and T[row][col] > max_val:
                    max_val = T[row][col]
    max_cell_width = len(str(max(m, n, max_val)))
    sys.stdout.write(' ' * len(str(n)))
    for col in range(0, m):
        sys.stdout.write(' ' + str(col).rjust(max_cell_width))
    sys.stdout.write('\n')
    for row in range(0, n):
        sys.stdout.write(str(row))
        for col in range(0, m):
            if T[row][col] is None:
                sys.stdout.write(' -')
            elif use_letters:
                sys.stdout.write(' ' + chr(65 + T[row][col]))
            else:
                sys.stdout.write(' ' + str(T[row][col]).rjust(max_cell_width))
        sys.stdout.write('\n')

def robot_coin_collection_dp(C):
    '''Uses dynamic programming to build a table of partial sums of the
       maximum amount of money the robot can collect by either moving right
       or down.

       Args:
           C: the initial matrix of coin values

       Returns:
           a tuple where the
           - first value is the maximum amount of money the robot can collect.
           - second value is the list of cells to visit to collect the
             maximum amount of money.
    '''
    m = len(C[0])
    n = len(C)
    F = [[0 for i in range(m)] for j in range(n)]
    
    F[0][0] = C[0][0]
    for j in range(1, m):
        F[0][j] = F[0][j-1] + C[0][j]
    for i in range(1, n):
        F[i][0] = F[i-1][0] + C[i][0]
        for j in range(1, m):
            F[i][j] = max(F[i-1][j], F[i][j-1]) + C[i][j]
    display_table(F)            
    return F[n-1][m-1], get_solution(F)

if __name__ == '__main__':
    board = [[0, 0, 0, 0, 1, 0],
             [0, 0, 1, 1, 0, 0],
             [0, 0, 0, 1, 0, 1],
             [0, 0, 1, 0, 0, 1],
             [1, 0, 0, 0, 1, 0]]
    display_table(board)
    print()
    solution = robot_coin_collection_dp(board)
    print('Max coins:', solution[0])
    print('Path from top left to bottom right:')
    for coord in solution[1]:
        print('-', coord)
