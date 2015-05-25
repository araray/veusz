// -*-c++-*-

//    Copyright (C) 2015 Jeremy S. Sanders
//    Email: Jeremy Sanders <jeremy@jeremysanders.net>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this program; if not, write to the Free Software Foundation, Inc.,
//    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
/////////////////////////////////////////////////////////////////////////////

#ifndef PROPERTIES_H
#define PROPERTIES_H

struct SurfaceProp
{
  SurfaceProp(double _r=0.5f, double _g=0.5f, double _b=0.5f,
	      double _specular=0.5f, double _diffuse=0.5f, double _trans=0,
	      bool _hide=0)
    : r(_r), g(_g), b(_b),
      specular(_specular), diffuse(_diffuse), trans(_trans),
      hide(_hide), _ref_cnt(0)
  {
  }

  double r, g, b;
  double specular, diffuse, trans;
  bool hide;

  // used to reference count usages by Object() instances
  mutable unsigned _ref_cnt;
};

struct LineProp
{
  LineProp(double _r=0, double _g=0, double _b=0,
	   double _specular=0.5f, double _diffuse=0.5f, double _trans=0,
	   double _width=1, bool _hide=0)
    : r(_r), g(_g), b(_b),
      specular(_specular), diffuse(_diffuse), trans(_trans),
      width(_width), hide(_hide), _ref_cnt(0)
  {
  }

  double r, g, b;
  double specular, diffuse, trans;
  double width;
  bool hide;

  // used to reference count usages by Object() instances
  mutable unsigned _ref_cnt;
};

//#include <stdio.h>

// this class is for automatically deleting the Surface/LineProp
// instances when the reference count drops back to 0
template<class T>
class PropSmartPtr
{
public:
  PropSmartPtr(T* p)
    : p_(p)
  {
    if(p_ != 0)
      {
	++p_->_ref_cnt;
	//printf("prop: %p +1 -> %i\n", p_, p_->_ref_cnt);
      }
  }

  ~PropSmartPtr()
  {
    if(p_ != 0)
      {
	--p_->_ref_cnt;
	//printf("prop: %p -1 -> %i\n", p_, p_->_ref_cnt);
	if(p_->_ref_cnt == 0)
	  delete p_;
      }
  }

  PropSmartPtr(const PropSmartPtr<T> &r)
    : p_(r.p_)
  {
    if(p_ != 0)
      {
	++p_->_ref_cnt;
	//printf("prop: %p +1 -> %i\n", p_, p_->_ref_cnt);
      }
  }

  T* operator->() { return p_; }
  const T* ptr() const { return p_; }

private:
  T* p_;
};

#endif