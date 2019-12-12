/**
 * @file CUDAELLUtils.hpp
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
 * @brief General conversion routines for ELL sparse matrices.
 * @author Thomas Brandes
 * @date 03.07.2012
 */

#pragma once

// for dll_import
#include <scai/common/config.hpp>

// internal scai library
#include <scai/kregistry/mepr/Registrator.hpp>

#include <scai/logging.hpp>

#include <scai/common/SCAITypes.hpp>
#include <scai/common/TypeTraits.hpp>
#include <scai/common/MatrixOp.hpp>
#include <scai/common/BinaryOp.hpp>

namespace scai
{

namespace sparsekernel
{

/** This class provides routines to converse ELL storage data to CSR storage data and vice versa.
 *
 *  All routines work on already allocated data and utilize CUDA for their parallelization.
 */

class COMMON_DLL_IMPORTEXPORT CUDAELLUtils
{
public:

    /** Addressing function for the arrays ia and ja: column-wise */

    static inline IndexType ellindex( const IndexType i, const IndexType jj, const IndexType numRows )
    {
        return jj * numRows + i;
    }

    static void check(
        const IndexType mNumRows,
        const IndexType mNumValuesPerRow,
        const IndexType mNumColumns,
        const IndexType* ia,
        const IndexType* ja,
        const char* msg );

    /** Returns one row of the matrix */

    template<typename ValueType>
    static void getRow(
        ValueType row[],
        const IndexType i,
        const IndexType numRows,
        const IndexType numColumns,
        const IndexType numValuesPerRow,
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[] );

    /** Returns one value of the matrix */

    template<typename ValueType>
    static ValueType getValue(
        const IndexType i,
        const IndexType j,
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[] );

    /** Implemenation of ELLKernelTrait::setRows for CUDA device */

    template<typename ValueType>
    static void setRows(
        ValueType ellValues[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const IndexType ellSizes[],
        const ValueType rowValues[],
        const common::BinaryOp op );

    /** Implementation for ELLKernelTrait::compressIA */

    template<typename ValueType>
    static void compressIA(
        IndexType newIA[],
        const IndexType ellIA[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const RealType<ValueType> eps );

    /** Implementation for ELLKernelTrait::compressValues */

    template<typename ValueType>
    static void compressValues(
        IndexType newJA[],
        ValueType newValues[],
        const IndexType newNumValuesPerRow,
        const IndexType ellIA[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const RealType<ValueType> eps );

    /** Implementation for ELLKernelTrait::Conversions::getCSRValues */

    template<typename ValueType>
    static void getCSRValues(
        IndexType csrJA[],
        ValueType csrValues[],
        const IndexType csrIA[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[] );

    template<typename ValueType>
    static void fillELLValues(
        IndexType ellJA[],
        ValueType ellValues[],
        const IndexType ellSizes[],
        const IndexType numRows,
        const IndexType numValuesPerRow );

    /** Helper routine for conversion CSR to ELL format.  */

    template<typename ValueType>
    static void setCSRValues(
        IndexType ellJA[],
        ValueType ellValues[],
        const IndexType ellSizes[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const IndexType csrIA[],
        const IndexType csrJA[],
        const ValueType csrValues[] );

    /** Implementation for ELLKernelTrait::normalGEMV on CUDA devices. */

    template<typename ValueType>
    static void normalGEMV(
        ValueType result[],
        const ValueType alpha,
        const ValueType x[],
        const ValueType beta,
        const ValueType y[],
        const IndexType numRows,
        const IndexType numColumns,
        const IndexType numValuesPerRow,
        const IndexType ellIA[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const common::MatrixOp op );

    /** Implementation for ELLKernelTrait::sparseGEMV  */

    template<typename ValueType>
    static void sparseGEMV(
        ValueType result[],
        const ValueType alpha,
        const ValueType x[],
        const IndexType numRows,
        const IndexType numValuesPerRow,
        const IndexType numNonZeroRows,
        const IndexType rowIndexes[],
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const common::MatrixOp op );

    /** Implementation for ELLKernelTrait::jacobi  */

    template<typename ValueType>
    static void jacobi(
        ValueType solution[],
        const IndexType numRows,
        const IndexType ellNumValuesPerRow,
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const ValueType oldSolution[],
        const ValueType rhs[],
        const ValueType omega );

    /** Implementation for ELLKernelTrait::Solver::jacobiHalo  */

    template<typename ValueType>
    static void jacobiHalo(
        ValueType solution[],
        const IndexType numRows,
        const ValueType diagonal[],
        const IndexType ellNumValuesPerRow,
        const IndexType ellSizes[],
        const IndexType ellJA[],
        const ValueType ellValues[],
        const IndexType rowIndexes[],
        const IndexType numNonEmptyRows,
        const ValueType oldSolution[],
        const ValueType omega );

private:

    SCAI_LOG_DECL_STATIC_LOGGER( logger )

    /** Struct for registration of methods without template arguments */

    struct Registrator
    {
        static void registerKernels( const kregistry::KernelRegistry::KernelRegistryFlag flag );
    };

    /** Struct for registration of methods with one template argument.
     *
     *  Registration function is wrapped in struct/class that can be used as template
     *  argument for metaprogramming classes to expand for each supported type
     */

    template<typename ValueType>
    struct RegistratorV
    {
        static void registerKernels( const kregistry::KernelRegistry::KernelRegistryFlag flag );
    };

    /** Constructor for registration. */

    CUDAELLUtils();

    /** Destructor for unregistration. */

    ~CUDAELLUtils();

    /** Static variable for registration at static initialization. */

    static CUDAELLUtils guard;
};

/* --------------------------------------------------------------------------- */

} /* end namespace sparsekernel */

} /* end namespace scai */
