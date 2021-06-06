#pragma once

#include <thread>
#include <vector>

using namespace std;

inline auto getHardwareThreadCount()
{
	auto threads = thread::hardware_concurrency();

	return threads;
}

auto getIterationIndices(const unsigned int count, const unsigned threads = getHardwareThreadCount())
{
	const auto size = min(threads, count);
	vector<int> indices(size + 1);
	for (unsigned i = 0; i < size; i++) {
		indices[i] = count * i / size;
	}
	indices.back() = count;
	return indices;
}
