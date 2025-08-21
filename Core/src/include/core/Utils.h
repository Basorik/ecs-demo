#pragma once
#include <random>
#include <chrono>
#include <limits>

namespace Utils
{
	class Random
	{
	public:
		static void Init()
		{
			s_RandomEngine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
		}
		static float Float()
		{
			return s_Distribution(s_RandomEngine);
		}
	private:
		static std::mt19937 s_RandomEngine;
		static std::uniform_real_distribution<float> s_Distribution;
	};
}
