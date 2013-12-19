#include "base3.hh"

base3::base3()
{
	direct[0] = vec3(1., 0., 0.);
	direct[1] = vec3(0., 1., 0.);
	direct[2] = vec3(0., 0., 1.);
}
base3::base3(const vec3& u, const vec3& v, const vec3& w)
{	
	direct[0] = u;
	direct[1] = v;
	direct[2] = w;
}
base3::base3(const base3& b)
{
	direct[0] = b.u();
	direct[1] = b.v();
	direct[2] = b.w();
}


vec3& base3::u() { return direct[0]; }
vec3& base3::v() { return direct[1]; }
vec3& base3::w() { return direct[2]; }
const vec3& base3::u() const { return direct[0]; }
const vec3& base3::v() const { return direct[1]; }
const vec3& base3::w() const { return direct[2]; }

base3 base3::phi(const double& p) const
{
	vec3 nu = u();
	vec3 nv = v().rotate(u(), p); 
	vec3 nw = w().rotate(u(), p);
	return base3(nu, nv, nw);
}

base3 base3::theta(const double& t) const
{
	vec3 nu = u().rotate(v(), t);
	vec3 nv = v(); 
	vec3 nw = w().rotate(v(), t);
	return base3(nu, nv, nw);	
}