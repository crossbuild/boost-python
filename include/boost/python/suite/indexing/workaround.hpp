// Header file workaround.hpp
//
// Indexing-specific workarounds for compiler problems.
//
// Copyright (c) 2003 Raoul M. Gough
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy
// at http://www.boost.org/LICENSE_1_0.txt)
//
// History
// =======
// 2003/10/21   rmg     File creation
//
// $Id$
//

#ifndef BOOST_PYTHON_INDEXING_WORKAROUND_HPP
#define BOOST_PYTHON_INDEXING_WORKAROUND_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

# if (BOOST_WORKAROUND (__GNUC__, < 3))
#   // gcc versions before 3 (like 2.95.3) don't have the "at" member
#   // function in std::vector or std::deque
#   define BOOST_PYTHON_INDEXING_AT operator[]
# else
#   define BOOST_PYTHON_INDEXING_AT at
# endif

# if BOOST_WORKAROUND (BOOST_MSVC, <= 1300)
// visualc.hpp never seems to define BOOST_NO_MEMBER_TEMPLATE_KEYWORD
// so BOOST_NESTED_TEMPLATE ends up expanding to "template" instead of
// being empty. This causes some compile errors with MSVC[67]
#   define BOOST_PYTHON_INDEXING_NESTED_TEMPLATE

// Workaround the lack of a reset member function in std::auto_ptr
namespace boost { namespace python { namespace indexing {
template<typename T> void reset_auto_ptr (T &aptr, T::element_type *pptr) {
 aptr = T (pptr);
}
} } }
#   define BOOST_PYTHON_INDEXING_RESET_AUTO_PTR \
        ::boost::python::indexing::reset_auto_ptr
# else
#   define BOOST_PYTHON_INDEXING_NESTED_TEMPLATE BOOST_NESTED_TEMPLATE
#   define BOOST_PYTHON_INDEXING_RESET_AUTO_PTR( aptr, pptr ) \
        (aptr).reset(pptr)
# endif

#endif // BOOST_PYTHON_INDEXING_WORKAROUND_HPP