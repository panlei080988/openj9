/*******************************************************************************
 * Copyright (c) 2000, 2016 IBM Corp. and others
 *
 * This program and the accompanying materials are made available under
 * the terms of the Eclipse Public License 2.0 which accompanies this
 * distribution and is available at https://www.eclipse.org/legal/epl-2.0/
 * or the Apache License, Version 2.0 which accompanies this distribution and
 * is available at https://www.apache.org/licenses/LICENSE-2.0.
 *
 * This Source Code may also be made available under the following
 * Secondary Licenses when the conditions for such availability set
 * forth in the Eclipse Public License, v. 2.0 are satisfied: GNU
 * General Public License, version 2 with the GNU Classpath
 * Exception [1] and GNU General Public License, version 2 with the
 * OpenJDK Assembly Exception [2].
 *
 * [1] https://www.gnu.org/software/classpath/license.html
 * [2] http://openjdk.java.net/legal/assembly-exception.html
 *
 * SPDX-License-Identifier: EPL-2.0 OR Apache-2.0
 *******************************************************************************/

#include "env/CompilerEnv.hpp"
#include "env/RawAllocator.hpp"
#include "j9.h"

bool initializeJIT(J9JavaVM *vm)
   {

   // Create a bootstrap raw allocator.
   //
   TR::RawAllocator rawAllocator(vm);

   try
      {
      // Allocate the host environment structure
      //
      TR::Compiler = new (rawAllocator)
         TR::CompilerEnv(
            vm,
            rawAllocator,
            (TR::PersistentAllocatorKit( 1 << 20, *vm))
            );
      }
   catch (const std::bad_alloc& ba)
      {
      return false;
      }

   TR::Compiler->initialize();

   return true;
   }