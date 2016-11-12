#include <base/printf.h>
#include <timer_session/connection.h>

int fib(int n)
{
  int first = 0;
  int second = 1;
  int result;

  if (n == 1)
  {
    result = 0;
  }
  else if (n == 2)
  {
    result = 1;
  }
  else
  {
    for (int i = 2; i < n; i++)
    {
      result = first + second;
      first = second;
      second = result;
      Genode::printf("INTERMEDIATE RESULT: %i\n", result);
    }

    return result;
  }
}

int main(void)
{
	while(true)
	{
		fib(1000);
	}

	return 0;
}

// int main(void)
// {
// 	PINF("hey: Hello!\n");
// 	Timer::Connection timer;
//
// 	int i = 0;
// 	while (true)
// 	{
// 		timer.msleep(500);
// 		PINF("Process is running %d!\n", i++);
// 	}
// }
