#pragma once
#include <iostream>
#include <vector>
#include <coroutine>

struct Event_base {
  virtual void operator()() = 0;
  virtual ~Event_base() {}
};

template <class Act> struct Event : Event_base {
  Event(const std::string n, Act a) : name{n}, act{std::move(a)} {}
  std::string name;
  Act act;
  void operator()() override { act(); }
};

struct task {
         void operator()() { coro.resume(); }

         struct promise_type {                                                              // mapping to the language features
                  std::suspend_always initial_suspend() { return {}; }
                  std::suspend_always final_suspend() noexcept { return {}; }            // co_return
                  std::suspend_always yield_value(int) { return {}; }                           // co_yield
                  auto get_return_object() { return task{ handle_type::from_promise(*this) }; }
                  void return_void() {}
                  void unhandled_exception() { exit(1); }
         };

         using handle_type = std::coroutine_handle<promise_type>;
         task(handle_type h) : coro(h) { }         // called by get_return_object()
         handle_type coro;                               // here is the coroutine handle
};

task char_seq(char start)
{
        auto value = start;
        while (true) {
                 std::cout << "value: " << value << '\n';    // communicate result
                 co_yield 0;
                 ++value;
        }
}


task sequencer(int start, int step =1)
{
        auto value = start;
        while (true) {
                std::cout << "value: " << value << '\n';              // communicate a result
                co_yield 0;                                                  // sleep until someone resumes this coroutine
                value += step;                                             // update state
        }
}

void test() {
  std::vector<Event_base *> events = {// create a couple of Events holding coroutines
                                 new Event{"integers ", sequencer(10)},
                                 new Event{"chars ", char_seq('a')}};

  std::vector order{0, 1, 1, 0, 1, 0, 1, 0, 0}; // choose some order

  for (int x : order) // invoke coroutines in order
    (*events[x])();

  for (auto p : events) // clean up
    delete p;
}