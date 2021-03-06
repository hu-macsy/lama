###
 # @file CMakeLists.txt
 #
 # @license
 # Copyright (c) 2009-2018
 # Fraunhofer Institute for Algorithms and Scientific Computing SCAI
 # for Fraunhofer-Gesellschaft
 #
 # This file is part of the SCAI framework LAMA.
 #
 # LAMA is free software: you can redistribute it and/or modify it under the
 # terms of the GNU Lesser General Public License as published by the Free
 # Software Foundation, either version 3 of the License, or (at your option)
 # any later version.
 #
 # LAMA is distributed in the hope that it will be useful, but WITHOUT ANY
 # WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 # FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
 # more details.
 #
 # You should have received a copy of the GNU Lesser General Public License
 # along with LAMA. If not, see <http://www.gnu.org/licenses/>.
 # @endlicense
 #
 # @brief sparsekernel/cuda/CMakeLists.txt
 # @author Eric Schricker
 # @date 18.02.2016
###

### Add classes and header files ###

add_subdirectory ( cusolver )
add_subdirectory ( cusparse )

scai_project(

    CLASSES      # .cpp, .hpp

    CUDA_CLASSES  # .cu, .hpp

       CUDACOOUtils
       CUDACSRUtils
       CUDADIAUtils
       CUDAELLUtils
       CUDAJDSUtils
       CUDAStencilKernel

    CUDA_SOURCES   # .cu

    HEADERS        # .hpp

    ADD_PARENT_SCOPE
)


#  cuSPARSE, cuSOLVER come always with CUDA so no additional tests here


