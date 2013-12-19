#include "tree.hh"


double rand(const double& fMin, const double& fMax)
{
	double f = (double) rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}






/*
 * ========================================================================
 * =                             CONSTRUCTOR                              =
 * ========================================================================
 */

branch::branch() : bbox()
{
	m_theta  = 0.; m_dtheta  = 0.;
	m_phi    = 0.; m_dphi    = 0.;
	m_length = 0.; m_dlength = 0.;
	m_size   = 0.;
	m_width  = 0.;
	m_father = nullptr;
	m_flag   = FLAG_VISIBLE;
}

/*
 * ========================================================================
 * =                               METHODS                                =
 * ========================================================================
 */

void branch::move(const double& size, const vec3& root, const base3& base)
{
	m_size		= size;
	m_base		= base;
	m_pts[0]	= root;
		
	compute();
}

void branch::compute()
{
	
	if (m_father)
		m_base = m_father->m_base.phi(m_phi+m_dphi).theta(m_theta+m_dtheta);
	m_pts[1]	= m_pts[0] + m_size * (m_length+m_dlength) * m_base.u();
	
	bbox::reset();
	bbox::addPoint(m_pts[0]);
	bbox::addPoint(m_pts[1]);
	
	for(branch* child : m_childs)
	{
		child->move(m_size, m_pts[1], m_base);
		bbox::addBox(*child);
	}
	
}

void branch::display(const vec3& color) const
{
	if (m_flag & FLAG_VISIBLE)
	{
		glColor3f(color.x(), color.y(), color.z());
		glLineWidth(m_width);
		glBegin(GL_LINES);
		glVertex3f(m_pts[0].x(), m_pts[0].y(), m_pts[0].z());
		glVertex3f(m_pts[1].x(), m_pts[1].y(), m_pts[1].z());
		glEnd();
		
		for(branch* child : m_childs)
			child->display(color);
	}
}

void branch::reset()
{
	m_flag = FLAG_VISIBLE;
	
	if (m_dtheta || m_dphi)
	{
		m_dtheta	= 0.;
		m_dphi		= 0.;
		m_dlength = 0.;
	}
	
	for (branch* child: m_childs)
		child->reset();
	
	if (!m_father)
		compute();
}

/*
 * ========================================================================
 * =                                STATIC                                =
 * ========================================================================
 */

branch* branch::make_branch(unsigned int age, unsigned int degre, const double& proba)
{
	if (age == 0) return nullptr;
	
	branch *result   = new branch;
	result->m_length = rand(1., 2.) * log(age + 1);
	result->m_width  = 1. + .5 * age;
	
	for (int i=0; i<degre; ++i)
		if (rand(0., 1.) < proba)
		{
			branch* child;
			if ((child = make_branch(age-1, degre)) == nullptr) continue;
			child->m_theta  = M_PI / (2. * age);
			child->m_phi    = 2. * i * M_PI / degre;
			child->m_father = result;
			result->m_childs.push_back(child);
		}
	
	return result;
}



void branch::colid(branch* a, branch* b)
{
	if (!(a->m_flag & FLAG_VISIBLE)) return;
	if (!(b->m_flag & FLAG_VISIBLE)) return;
	if (!bbox::colid(*a, *b))        return;

	if (bbox::colid(bbox(a->m_pts[0], a->m_pts[1]), bbox(b->m_pts[0], b->m_pts[1])))
	{
		if (a->m_length < b->m_length)
			a->m_flag &= !FLAG_VISIBLE;
		else
			b->m_flag &= !FLAG_VISIBLE;
	}
	else
	{
		for (branch* a_child: a->m_childs)
			for (branch* b_child: b->m_childs)
				colid(a_child, b_child);
	}
}




void branch::colid(branch* a, const bbox& wall)
{
	if (!(a->m_flag & FLAG_VISIBLE)) return;
	if (!bbox::colid(*a, wall))      return;

	if (bbox::colid(bbox(a->m_pts[0], a->m_pts[1]), wall))
	{
		a->m_flag &= !FLAG_VISIBLE;
		
		branch* r = a;
		for (int i=1; i<=3; ++i)
		{
			if (r->m_father == nullptr) break;						
			r = r->m_father;

			if (wall.distance(r->m_pts[1]) < wall.distance(r->m_pts[1] + r->m_base.v()))
				r->m_dtheta = std::max(r->m_dtheta, + 0.2 / i);
			else
				r->m_dtheta = std::min(r->m_dtheta, - 0.2 / i);

		}
		r->compute();
		colid(r, wall);
		
	}
	else
		for (branch* a_child: a->m_childs)
			colid(a_child, wall);
}




/*
 * ========================================================================
 * =                           STRUCTURE ACCESS                           =
 * ========================================================================
 */
branch* branch::root() 
{
	branch* r = this;
	while (r->m_father) r = r->m_father;
	return r;
}

const branch* branch::root() const
{
	const branch* r = this;
	while (r->m_father) r = r->m_father;
	return r;
}

int branch::flag() const
{
	return m_flag;
}
