#pragma once

#include <geometry/RayHit>
#include <set>

namespace geometry {

class RayHitSet : public std::set<RayHit> {
public:

	void removeDuplicates();

};

} // namespace geometry
