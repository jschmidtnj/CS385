/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 9/6/2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * PrimeSieve class
 * 
 * used to calculate the prime numbers up to a given input limit
 * using the sieve algorithm
 */
class PrimesSieve
{
public:
  /**
   * PrimesSieve constructor
   * takes input int limit, which is up to which the prime numbers
   * are calculated
   */
  PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit}
  {
    // run sieve algorithm on init
    sieve();
  }

  /**
   * PrimesSieve deconstructor
   * deconstructs the PrimesSieve object by freeing the is_prime_
   * array of pointers from the heap
   */
  ~PrimesSieve()
  {
    delete[] is_prime_;
  }

  /**
   * accessor for the number
   * of primes found up to input limit
   */
  inline int num_primes() const
  {
    return num_primes_;
  }

  /**
   * returns the max prime number
   * from sieve method
   */
  inline int max_prime() const
  {
    return max_prime_;
  }

  /**
   * display_primes
   * 
   * displayes the prime numbers found from the sieve algorithm in
   * a specific format, defined in guidelines for project
   */
  void display_primes() const
  {
    // write code to display the primes in the format specified in the
    // requirements document.
    cout << endl
         << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":";
    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);
    int i, j, prime_count = 0;
    for (i = 2; i <= max_prime_; i++)
      if (is_prime_[i])
      {
        // newline if last in row was before
        if (prime_count % primes_per_row == 0)
          cout << endl;
        prime_count++;
        // add spaces n multirow
        if (num_primes_ > primes_per_row)
          for (j = 0; j < max_prime_width - num_digits(i); j++)
            cout << ' ';
        cout << i;
        // space if not last prime and not last in row
        if (i != max_prime_ && prime_count % primes_per_row != 0)
          cout << ' ';
      }
  }

private:
  bool *const is_prime_;
  const int limit_;
  int num_primes_, max_prime_;

  /**
   * count_primes populates the num_primes_
   * and max_primes_ with the correct values
   * for each respectively
   */
  void count_primes()
  {
    // write code to count the number of primes found
    num_primes_ = 0;
    for (int i = 2; i <= limit_; i++)
      if (is_prime_[i])
      {
        num_primes_++;
        max_prime_ = i;
      }
  }

  /**
   * num_digits gets the number of digits
   * in a given int
   */
  int num_digits(int num) const
  {
    // write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count;
    for (count = 0; num > 0; count++)
      num /= 10;
    return count;
  }

  /**
   * main sieve algorithm, implemented to count
   * primes at the end of execution (see above)
   */
  void sieve()
  {
    // write sieve algorithm
    int i, j;
    for (i = 2; i <= limit_; i++)
      is_prime_[i] = true;
    for (i = 2; i <= sqrt(limit_); i++)
      if (is_prime_[i])
        for (j = i * i; j <= limit_; j += i)
          is_prime_[j] = false;
    count_primes();
  }
};

/**
 * main function for getting prime limit input,
 * and creating a PrimesSieve object to process
 * that input
 */
int main()
{
  cout << "**************************** "
       << "Sieve of Eratosthenes"
       << " ****************************" << endl;
  cout << "Search for primes up to: ";
  string limit_str;
  cin >> limit_str;
  int limit;
  // Use stringstream for conversion. Don't forget to #include <sstream>
  istringstream iss(limit_str);
  // Check for error.
  if (!(iss >> limit))
  {
    cerr << "Error: Input is not an integer." << endl;
    return 1;
  }
  if (limit < 2)
  {
    cerr << "Error: Input must be an integer >= 2." << endl;
    return 1;
  }
  // write code that uses your class to produce the desired output.
  PrimesSieve(limit).display_primes();
  return 0;
}
