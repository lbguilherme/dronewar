#include <geometry/RayHitSet>
#include <algorithm>

using namespace geometry;

void RayHitSet::removeDuplicates() {
	auto cmp = [](const RayHit& a, const RayHit& b){
		auto dist = std::abs(a.distance() - b.distance());
		return dist < 0.000001; // TODO
	};

	auto it = begin();
	while ((it = std::adjacent_find(it, end(), cmp)) != end()) {
		erase(it);
	}
}
