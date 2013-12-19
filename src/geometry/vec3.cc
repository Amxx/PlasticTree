#include "vec3.hh"

vec3::vec3()
{
	m_value[0] = 0;
	m_value[1] = 0;
	m_value[2] = 0;
}
vec3::vec3(const double& x, const double& y, const double& z)
{
	m_value[0] = x;
	m_value[1] = y;
	m_value[2] = z;
}
vec3::vec3(const vec3& cpy)
{
	m_value[0] = cpy.m_value[0];
	m_value[1] = cpy.m_value[1];
	m_value[2] = cpy.m_value[2];
}


double& vec3::x() { return m_value[0]; }
double& vec3::y() { return m_value[1]; }
double& vec3::z() { return m_value[2]; }
const double vec3::x() const { return m_value[0]; }
const double vec3::y() const { return m_value[1]; }
const double vec3::z() const { return m_value[2]; }



vec3 vec3::rotate(const vec3& axe, const double& angle) const
{
	double c = cos(angle);
	double s = sin(angle);
  double nx = x() * (       axe.x()*axe.x()	+ (1-axe.x()*axe.x())*c ) \
						+ y() * ( (1-c)*axe.x()*axe.y()	-            axe.z() *s ) \
						+ z() * ( (1-c)*axe.x()*axe.z() +            axe.y() *s );
  double ny = x() * ( (1-c)*axe.x()*axe.y()	+            axe.z() *s ) \
						+ y() * (       axe.y()*axe.y()	+ (1-axe.y()*axe.y())*c ) \
						+ z() * ( (1-c)*axe.y()*axe.z() -            axe.x() *s );
  double nz = x() * ( (1-c)*axe.x()*axe.z()	-            axe.y() *s ) \
						+ y() * ( (1-c)*axe.y()*axe.z()	+            axe.x() *s ) \
						+ z() * (       axe.z()*axe.z() + (1-axe.z()*axe.z())*c );
	
	return vec3(nx, ny, nz);
}




