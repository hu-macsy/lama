/**
 * @file lama/matrix/ELLSparseMatrix.hpp
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
 * @brief Definition of matrix class for distributed sparse matrixes in ELL format.
 * @author Jiri Kraus, Thomas Brandes
 * @date 22.02.2011
 */
#pragma once

// for dll_import
#include <scai/common/config.hpp>

// base classes
#include <scai/lama/matrix/SparseMatrix.hpp>

// local library
#include <scai/lama/storage/ELLStorage.hpp>

namespace scai
{

namespace lama
{

/** Definition of a derived class for SparseMatrix that uses the ELL storage
 *  format for the local and halo data of the distributed sparse matrix.
 *
 *  As the storage format is known here this class can offer more advanced
 *  constructors that do not exist for SparseMatrix as there the storage
 *  format is not fixed.
 */

template<typename ValueType>
class COMMON_DLL_IMPORTEXPORT ELLSparseMatrix:

    public SparseMatrix<ValueType>,
    public _Matrix::Register<ELLSparseMatrix<ValueType> >    // register at factory
{

public:

    /** @brief Type definition of the storage type for this sparse matrix. 
     * 
     *  \code
     *     template<typename MatrixClass>
     *     void setup( MatrixClass& matrix )
     *     {
     *         typename MatrixClass::StorageType storage;
     *         storage.allocate( .. )
     *         ...
     *         matrix = MatrixClass( std::move( storage ) );
     *     }
     *  \endcode
     */

    typedef ELLStorage<ValueType> StorageType;

    /** Static method that returns the name of the matrix class. */

    static const char* typeName();

    /** Default constructor, creates a replicated matrix of size 0 x 0 */

    ELLSparseMatrix( hmemo::ContextPtr ctx = hmemo::Context::getContextPtr() );

    /** Override default constructor, make sure that deep copies are created. */

    ELLSparseMatrix( const ELLSparseMatrix<ValueType>& other );

    /** Rewriting move constructor, leaves the other matrix as zero matrix */

    ELLSparseMatrix( ELLSparseMatrix<ValueType>&& other ) noexcept;

    /** Most general copy constrcuctor with possibility of transpose. */

    explicit ELLSparseMatrix( const Matrix<ValueType>& other);

    /** Constructor of a (replicated) sparse matrix by global storage.
     *
     *  @param[in] globalStorage  contains the full storage, must be of same format and type
     */
    explicit ELLSparseMatrix( ELLStorage<ValueType> globalStorage );

    /** Constructor of a sparse matrix by local storage
     *
     *  @param[in] localStorage  contains local rows of the distributed matrix
     *  @param[in] rowDist       is distribution of localData
     *
     *  The number of rows for the local storage must be rowDist->getLocalSize(), and the 
     *  number of columns must be the same on all processors.
     */
    ELLSparseMatrix( dmemo::DistributionPtr rowDist, ELLStorage<ValueType> localStorage );

    /**
     * @brief Destructor. Releases all allocated resources.
     */
    ~ELLSparseMatrix();

    /** Override the default assignment operator that would not make deep copies. */

    ELLSparseMatrix& operator=( const ELLSparseMatrix& matrix );

    /** Override the default move assignment operator */

    ELLSparseMatrix& operator=( ELLSparseMatrix&& matrix );

    /** Override MatrixStorage<ValueType>::getLocalStorage with covariant return type. */

    virtual const StorageType& getLocalStorage() const;

    /** @todo this getter should be removed as write access to local strage is dangerous */

    virtual StorageType& getLocalStorage();

    /** Override MatrixStorage<ValueType>::getHaloStorage with covariant return type. */

    virtual const StorageType& getHaloStorage() const;

    /* Implementation of pure method _Matrix::newMatrix with covariant return type */

    virtual ELLSparseMatrix<ValueType>* newMatrix() const;

    /* Implementation of pure method _Matrix::copy with covariant return type */

    virtual ELLSparseMatrix<ValueType>* copy() const;

    /* Implementation of pure method _Matrix::getFormat */

    virtual Format getFormat() const;

    /* Implementation of pure method of class _Matrix. */

    virtual const char* getTypeName() const;

    using _Matrix::getNumRows;
    using _Matrix::getNumColumns;
    using _Matrix::setIdentity;

    using _Matrix::getRowDistribution;
    using _Matrix::getRowDistributionPtr;
    using _Matrix::getColDistribution;
    using _Matrix::getColDistributionPtr;


    using Matrix<ValueType>::getValueType;
    using SparseMatrix<ValueType>::operator=;
    using SparseMatrix<ValueType>::operator-=;
    using SparseMatrix<ValueType>::operator+=;

    using SparseMatrix<ValueType>::setContextPtr;
    using SparseMatrix<ValueType>::redistribute;

protected:

    using SparseMatrix<ValueType>::mLocalData;
    using SparseMatrix<ValueType>::mHaloData;
    using SparseMatrix<ValueType>::mHaloExchangePlan;

private:

    /** This private routine provides empty ELL storage for a ELLSparseMatrix. */

    std::shared_ptr<ELLStorage<ValueType> > createStorage( hmemo::ContextPtr ctx );

    /** This private routine provides empty ELL storage for a ELLSparseMatrix. */

    std::shared_ptr<ELLStorage<ValueType> > createStorage( ELLStorage<ValueType>&&  );

    static std::string initTypeName();

    SCAI_LOG_DECL_STATIC_LOGGER( logger )

public:

    // static create method that will be used to register at _Matrix factory

    static _Matrix* create();

    // key for factory

    static MatrixCreateKeyType createValue();
};

/* ================================================================================ */
/*   Implementation of inline methods                                               */
/* ================================================================================ */

template<typename ValueType>
Format ELLSparseMatrix<ValueType>::getFormat() const
{
    return Format::ELL;
}

} /* end namespace lama */

} /* end namespace scai */
