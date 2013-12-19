#ifndef base3_HH
#define base3_HH

#include "vec3.hh"

class base3
{
	private:
		vec3	direct[3];
	public:
		base3();
		base3(const vec3& u, const vec3& v, const vec3& w);
		base3(const base3& b);
													
		vec3& u();
		vec3& v();
		vec3& w();
		const vec3& u() const;
		const vec3& v() const;
		const vec3& w() const;
		
		base3 phi(const double& p) const;
		base3 theta(const double& t) const;
};


#endif
