/**
 * @file lamaStorageTest.cpp
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
 * @brief Main program for test of LAMA storage classes. Due to file I/O
 *        this test must not be executed by multiple processors.
 * @author Thomas Brandes
 * @date 16.03.2016
 */

#ifndef BOOST_TEST_DYN_LINK
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE lamaStorageTest
#define BOOST_TEST_NO_MAIN

#include <scai/testsupport/dmemoTestMain.hpp>
#include <scai/hmemo/test/ContextFix.hpp>

BOOST_GLOBAL_FIXTURE( ContextFix );

/** Static variables of ContextFix are defined here */

scai::hmemo::ContextPtr ContextFix::testContext;

int main( int argc, char* argv[] )
{
    return scai::testsupport::dmemoTestMain(argc, argv);
}
