#include <iostream>
#include <mutex>
#include <list>
#include <thread>
#include <chrono>


std::list<int> my_list;
std::mutex m;

void add_to_list(int const &x)
{
  // m.lock();
  // RAII style auto lock/unlock - deprecated in C++17
  // use scoped_lock or shared_lock ->
  // std::lock_guard<std::mutex> lg(m);
  std::scoped_lock<std::mutex> sl(m);
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  my_list.push_front(x);

  // m.unlock();
}

void size()
{
  // m.lock();
  // std::lock_guard<std::mutex> lg(m);
  std::scoped_lock<std::mutex> sl(m);
  int size = my_list.size();
  // m.unlock();
  std::cout << "Size of list is: " << size << std::endl;
}

std::list<int>* get_data()
{
  return &my_list;
}



int main()
{
  std::thread thread_1(add_to_list, 4);
  std::thread thread_2(add_to_list, 11);
  std::thread thread_3(size);

  thread_1.join();
  thread_2.join();
  thread_3.join();

  return 0;
}

