#include <stdio.h>
#include <time.h>

int main(void) {
  // Stores the total number of seconds remaining to countdown
  int seconds = 9;

  // Continue the loop so long as there are seconds remaining, the loop
  // will output the time remaining and pause for a second each time...
  while (seconds > 0) {
    int s = seconds % 60;
    // Because the call to printf() does not ouput a \n newline the stdout
    // buffer will not automatically flush and cause the time to output,
    // so we flush it 'manually' using fflush(stdout)
    printf("\r%02d", s);

    fflush(stdout);

    // Get the current number of clock ticks that have occurred since the
    // program started running with clock() and add the number of clock tics
    // that occur in one second, store the result into stop.
    clock_t stop = clock() + CLOCKS_PER_SEC;

    // When clock() DOES return the number of clock tics greater than or
    // equal to the expected number one second in the future, stop this
    // loop.  This loop will thus cause the program to pause for one second.
    while (clock() < stop) {}
    // Decrement seconds as another second has elapsed
    seconds--;
  }
  return 0;
}
