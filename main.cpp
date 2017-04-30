#include <iostream>
#include <thread>

// C++14
auto f() noexcept 
{
  return "Hello world\n";
}

void DoCountDown(const int id)
{
  for (int i=0; i!=10; ++i)
  {
    std::cout << "#" << id << ": " << (10-i) << '\n';
  }
}

int main()
{
  std::cout << f() << '\n';
  std::thread t1(DoCountDown,1);
  std::thread t2(DoCountDown,2);
  t1.join();
  t2.join();
}
