#include <iostream>
#include <future>
#define _GLIBCXX_USE_NANOSLEEP
using namespace std::literals;

void main(int argc, char* argv[]) {
	std::packaged_task<void* (unsigned&&)> ptask([](unsigned&& x) { return new unsigned(x); });

	std::future<void*> fut = ptask.get_future();

	std::thread t(std::move(ptask), 'z');
	std::this_thread::sleep_for(2s);
	t.join();
	void* ptr = fut.get();
	std::cout << *(int*)ptr << std::endl;
}
