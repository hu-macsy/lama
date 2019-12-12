/**
 * @file MPIException.cpp
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
 * @brief MPIException.cpp
 * @author Thomas Brandes
 * @date 01.03.2011
 */

#include <mpi.h> //Intel MPI need mpi.h to be included before stdio.h so this header comes first

// hpp
#include <scai/dmemo/mpi/MPIException.hpp>

// std
#include <sstream>

namespace scai
{

namespace dmemo
{

MPIException::MPIException( const std::string& message, const int mpiStatus )
{
    std::ostringstream oss;
    oss << message << " Cause: " << mpiStatus;
    char mpiErrorString[MPI_MAX_ERROR_STRING];
    int resultlen = MPI_MAX_ERROR_STRING;
    MPI_Error_string( mpiStatus, mpiErrorString, &resultlen );
    oss << " (" << mpiErrorString << ")";
    mMessage = oss.str();
}

MPIException::~MPIException() throw ()
{
}

} /* end namespace dmemo */

} /* end namespace scai */
