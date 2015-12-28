#ifndef FALCON_BOUNDINGSPHERE
#define FALCON_BOUNDINGSPHERE

#include "FalconMath.h"

namespace falcon
{
	
	struct BoundingSphere
	{
	public:
		BoundingSphere():center(Vec3(0,0,0)),radius(0){};
		BoundingSphere(Vec3 cntr, float rds):center(cntr), radius(rds){};
		~BoundingSphere(){};

		Vec3 center;
		float radius;
	};
}

#endif //FALCON_BOUNDINGSPHERE