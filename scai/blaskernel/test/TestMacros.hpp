/**
 * @file scai/blaskernel/test/TestMacros.hpp
 *
 * @license
 * Copyright (c) 2009-2018
 * Fraunhofer Institute for Algorithms and Scientific Computing SCAI
 * for Fraunhofer-Gesellschaft
 *
 * This file is part of the SCAI framework LAMA.
 *
 * LAMA is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * LAMA is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LAMA. If not, see <http://www.gnu.org/licenses/>.
 * @endlicense
 *
 * @brief Additional Macros used for testing of blaskernel with Boost Test.
 * @author Eric Schricker
 * @date 20.11.2015
 */

#pragma once

#include <scai/common/test/TestMacros.hpp>
#include <scai/hmemo/test/ContextFix.hpp>

/* --------------------------------------------------------------------- */
/*     test types for BLAS ( S, D, C, Z )                                */
/* --------------------------------------------------------------------- */

typedef boost::mpl::list<SCAI_NUMERIC_TYPES_EXT_HOST> blas_test_types;

/* --------------------------------------------------------------------- */

