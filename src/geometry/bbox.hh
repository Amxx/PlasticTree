#ifndef BBOX_HH
#define BBOX_HH

#include <cstdlib>
#include <algorithm>
#include <GL/glut.h>

#include "vec3.hh"

class bbox
{
	protected:
		vec3 m_pts[2];
	public:
		bbox();
		bbox(const vec3&, const vec3&);
		
		const 	vec3& min() const;
		const 	vec3& max() const;
	
		void 		display(const vec3&, GLenum = GL_LINE) const;
		
		void 		addPoint(const vec3&);
		void 		addBox(const bbox&);
		void 		reset();
		
		double	distance(const vec3&) const;
		bool		inside(const vec3&) const;
	
		static bool colid(const bbox&, const bbox&);
};



#endif