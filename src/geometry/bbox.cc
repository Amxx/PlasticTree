#include "bbox.hh"

bbox::bbox()
{
	m_pts[0] = vec3();
	m_pts[1] = vec3();
}
bbox::bbox(const vec3& pt1, const vec3& pt2)
{
	
	m_pts[0] = vec3(std::min(pt1.x(), pt2.x()),
									std::min(pt1.y(), pt2.y()),
									std::min(pt1.z(), pt2.z()));
	m_pts[1] = vec3(std::max(pt1.x(), pt2.x()),
									std::max(pt1.y(), pt2.y()),
									std::max(pt1.z(), pt2.z()));
	
}

const vec3& bbox::min() const
{
	return m_pts[0];
}

const vec3& bbox::max() const
{
	return m_pts[1];
}


void bbox::display(const vec3& color, GLenum display_type) const
{
	glPolygonMode(GL_FRONT_AND_BACK, display_type);
	glColor3f(color.x(), color.y(), color.z());		
	glBegin(GL_QUADS);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[0].z() + .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[0].x() + .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[1].y() - .1, m_pts[1].z() - .1);
	glVertex3f(m_pts[1].x() - .1, m_pts[0].y() + .1, m_pts[1].z() - .1);
	glEnd();
}



void bbox::addPoint(const vec3& pt)
{
	
	m_pts[0] = vec3(std::min(m_pts[0].x(), pt.x()),
									std::min(m_pts[0].y(), pt.y()),
									std::min(m_pts[0].z(), pt.z()));
	m_pts[1] = vec3(std::max(m_pts[1].x(), pt.x()),
									std::max(m_pts[1].y(), pt.y()),
									std::max(m_pts[1].z(), pt.z()));
	
}

void bbox::addBox(const bbox& b)
{
	addPoint(b.m_pts[0]);
	addPoint(b.m_pts[1]);
}
void bbox::reset()
{
	m_pts[0] = vec3();
	m_pts[1] = vec3();
}

double	bbox::distance(const vec3& pt) const
{
	double dx, dy, dz;
	
	dx =	(pt.x() < m_pts[0].x())?(pt.x() - m_pts[0].x()) :
				(pt.x() > m_pts[1].x())?(pt.x() - m_pts[1].x()) :
	      0.;
	
	dy =	(pt.y() < m_pts[0].y())?(pt.y() - m_pts[0].y()) :
				(pt.y() > m_pts[1].y())?(pt.y() - m_pts[1].y()) :
	      0.;
	
	dz =	(pt.z() < m_pts[0].z())?(pt.z() - m_pts[0].z()) :
				(pt.z() > m_pts[1].z())?(pt.z() - m_pts[1].z()) :
	      0.;
	
	return sqrt(dx*dx + dy*dy + dz*dz);
}
		

bool bbox::inside(const vec3& pt) const
{
	return (	 pt.x() > m_pts[0].x() && pt.x() < m_pts[1].x()
					&& pt.y() > m_pts[0].y() && pt.y() < m_pts[1].y()
					&& pt.z() > m_pts[0].z() && pt.z() < m_pts[1].z() );
}

bool bbox::colid(const bbox& bb1, const bbox& bb2)
{
	if (	 bb1.m_pts[0].x() < bb2.m_pts[1].x() && bb1.m_pts[1].x() > bb2.m_pts[0].x()
			&& bb1.m_pts[0].y() < bb2.m_pts[1].y() && bb1.m_pts[1].y() > bb2.m_pts[0].y()
			&& bb1.m_pts[0].z() < bb2.m_pts[1].z() && bb1.m_pts[1].z() > bb2.m_pts[0].z() ) return true;
	
	if (	 bb1.m_pts[0].x() < bb2.m_pts[1].x() && bb1.m_pts[1].x() > bb1.m_pts[1].x()
			&& bb1.m_pts[0].y() < bb2.m_pts[1].y() && bb1.m_pts[1].y() > bb1.m_pts[1].y()
			&& bb1.m_pts[0].z() < bb2.m_pts[1].z() && bb1.m_pts[1].z() > bb1.m_pts[1].z() ) return true;	
	
	return false;
}





