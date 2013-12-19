#ifndef TREE_HH
#define TREE_HH

#include <cstdlib>
#include <vector>
#include <GL/glut.h>

#include "../geometry/vec3.hh"
#include "../geometry/base3.hh"
#include "../geometry/bbox.hh"


#define FLAG_VISIBLE	0x00000001
#define FLAG_EDITED		0x00000002




class branch : public bbox
{
	private:
		
		vec3									m_pts[2];
	
		base3									m_base;
	
		double								m_theta,	m_dtheta;
		double								m_phi,		m_dphi;
		double								m_length, m_dlength;
	
		double								m_width;
		double								m_size;
	
		std::vector<branch*>	m_childs;
		branch								*m_father;
		int										m_flag;
	

	public:
	
		branch();
	
		branch* 				root();
		const branch*		root() const;
		int							flag() const;
		
		void						move(const double& = 1., const vec3& = vec3(), const base3& = base3());
		void						compute();
		void						display(const vec3& = vec3(1., 1., 1.)) const;
		void						reset();
		

		static branch*	make_branch(unsigned int, unsigned int = 3, const double& = 0.8);
		
		static void			colid(branch*, branch*);
		static void			colid(branch*, const bbox&);
		

		
};







#endif