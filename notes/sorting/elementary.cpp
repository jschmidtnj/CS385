using namespace std;

static void swap(int array[], const int a, const int b)
{
  int temp = array[a];
  array[a] = array[b];
  array[b] = temp;
}

// think of it as a can of soda, bubbles float up. you keep swapping neighbors
// best case is theta(n)
// worst is theta(n^2) - it's actually n*(n-1)/2
// average case is theta(n^2)
// overall is O(n^2)
void bubble_sort(int array[], const int length)
{
  int len = length;
  while (len > 1)
  {
    int n = 0; // n represents the highest index where a swap occurred
    for (int i = 1; i < len; ++i)
    {
      if (array[i - 1] > array[i])
      {
        swap(array, i - 1, i);
        n = i;
      }
    }
    len = n;
  }
}

// principle operator is array[j] < min
// always nakes n(n-1)/2 comparisons, at most n-1 swaps
// best case is theta(n^2)
// worst is theta(n^2)
// average case is theta(n^2)
// overall is theta(n^2)
void selection_sort(int array[], const int length)
{
  for (int i = 0, i_bound = length - 1; i < i_bound; ++i)
  {
    int min_index = i, min = array[i];
    for (int j = i + 1; j < length; ++j)
    {
      if (array[j] < min)
      {
        min_index = j;
        min = array[j];
      }
    }
    if (min_index != i)
    {
      swap(array, i, min_index);
    }
  }
}

// where should I insert a number?
// principle operator is array[j] < min
// always nakes n(n-1)/2 comparisons, at most n-1 swaps
// best case is theta(n)
// worst is theta(n^2)
// average case is theta(n^2)
// overall is O(n^2)
void insertion_sort(int array[], const int length)
{
  for (int i = 1; i < length; ++i)
  {
    int k, current = array[i];
    for (k = i - 1; k >= 0 && array[k] > current; --k)
    {
      array[k + 1] = array[k];
    }
    array[k + 1] = current;
  }
}
