/**
 * @file MKLCSRTrait.hpp
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
 * @brief Definitions for MKL sparse interface
 * @author Eric Stricker
 * @date 09.02.2016
 */

#pragma once

// macros
#define MKLCSR_BLAS_NAME( name, prefix ) mkl_##prefix##name

// external

namespace scai
{

namespace sparsekernel
{

class COMMON_DLL_IMPORTEXPORT MKLCSRTrait
{
public:
    typedef int  BLASIndexType;
    typedef char BLASTrans;
    typedef char BLASMatrix[6];
};

} /* end namespace sparsekernel */

} /* end namespace scai */
