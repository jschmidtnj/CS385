using namespace std;

/**
 * sequential search
 * assume the probability of a successful
 * search is equal to p(0 <= p <= 1)
 * probability of the first match occuring in the ith position is
 * the same for every i
 * 
 * with a successful search, the probability of the first match occuring in
 * the ith position is p/n for every i
 * 
 * number of comparisons: i
 * with an unsuccessful search, the number of comparisons will be n, with
 * the probability of such a search being 1-p
 * p is probability of successful search
 * 
 * average cost:
 * Cavg(n) = [1*p/n + 2*p/n + ... + i*p/n + n*p/n] + n*(1-p)
 *         = p/n(1 + 2 + ... + n) + n*(1-p)
 * S = 1 + 2 + 3 + ... + n-1 + n
 *   = n + n-1 + n-2 + ... + 2 + 1
 * 2S = (n+1) + (n+1) + (n+1) ...
 * S = n(n+1)/2
 * >>>>>>>>>>>>>>>>>>>>>>>
 * Cavg = p*(n+1)/2 + n*(1-p)
 * if p = 1, search is successful, number of probes is (n+1)/2
 * if p = 0, search is gaurunteed to be unsuccessful -> n elements
 */
int sequential_search(int array[], const int size, int key)
{
  for (int i = 0; i < size; i++)
    if (array[i] == key)
      return i;
  return -1;
}
