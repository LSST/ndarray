/* 
 * LSST Data Management System
 * Copyright 2008, 2009, 2010 LSST Corporation.
 * 
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the LSST License Statement and 
 * the GNU General Public License along with this program.  If not, 
 * see <http://www.lsstcorp.org/LegalNotices/>.
 */

#ifndef NDARRAY_pybind11_h_INCLUDED
#define NDARRAY_pybind11_h_INCLUDED

/**
 *  @file ndarray/pybind11.h
 *  @brief Public header file for pybind11-based Python support.
 *
 *  \warning Both the Numpy C-API headers "arrayobject.h" and
 *  "ufuncobject.h" must be included before ndarray/python.hpp
 *  or any of the files in ndarray/python.
 *
 *  \note This file is not included by the main "ndarray.h" header file.
 */

/** \defgroup ndarrayPythonGroup Python Support
 *
 *  The ndarray Python support module provides conversion
 *  functions between ndarray objects, notably Array and
 *  Vector, and Python Numpy objects.
 */

#include "pybind11.h"

#include "ndarray/converter.h"
#include "ndarray/converter/eigen.h"

NAMESPACE_BEGIN(pybind11)
NAMESPACE_BEGIN(detail)

template <typename T, int N, int C>
class type_caster< ndarray::Array<T,N,C> > {
public:
    bool load(handle src, bool) {
        ndarray::PyPtr tmp(src.ptr(), true);
        if (!ndarray::PyConverter< ndarray::Array<T,N,C> >::fromPythonStage1(tmp)) {
            PyErr_Clear();
            return false;
        }
        if (!ndarray::PyConverter< ndarray::Array<T,N,C> >::fromPythonStage2(tmp, value)) {
            PyErr_Clear();
            return false;
        }
        return true;
    }
    static handle cast(const ndarray::Array<T,N,C> &src, return_value_policy /* policy */, handle /* parent */) {
        return ndarray::PyConverter< ndarray::Array<T,N,C> >::toPython(src);
    }
/* This part is normally created by the PYBIND11_TYPE_CASTER macro, which
 * can't be used here due to the partial specialization
 */
protected:
    ndarray::Array<T,N,C> value;
public:
    static PYBIND11_DESCR name() { return type_descr(_<ndarray::Array<T,N,C>>()); }
    static handle cast(const ndarray::Array<T,N,C> *src, return_value_policy policy, handle parent) {
        return cast(*src, policy, parent);
    }
    operator ndarray::Array<T,N,C> * () { return &value; }
    operator ndarray::Array<T,N,C> & () { return value; }
    template <typename _T> using cast_op_type = pybind11::detail::cast_op_type<_T>;
};

NAMESPACE_END(detail)
NAMESPACE_END(pybind11)

#endif // !NDARRAY_pybind11_h_INCLUDED
