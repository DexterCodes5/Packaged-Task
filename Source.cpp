#include <iostream>
#include <future>
using namespace std::literals;

int main() {
	std::packaged_task<void* (unsigned&&)> ptask([](unsigned&& x) { return new unsigned(x); });

	std::future<void*> fut = ptask.get_future();

	std::thread t(std::move(ptask), 6);
	std::this_thread::sleep_for(2s);
	t.join();
	void* ptr = fut.get();
	std::cout << *(int*)ptr << std::endl;
}
