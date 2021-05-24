/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  SecureBootBBTestMain.h

Abstract:
  Header file for Secure Boot Black-Box Test.

--*/

#ifndef _SECURE_BOOT_BB_TEST_MAIN_H
#define _SECURE_BOOT_BB_TEST_MAIN_H

//
// Includes
//
#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

//
// Definitions
//

#define SECURE_BOOT_BB_TEST_REVISION    0x00010000

#define SECURE_BOOT_BB_TEST_GUID        \
  { 0xCBADA58E, 0xA1AA, 0x45DF, {0xBD, 0xDF, 0xF9, 0xBA, 0x12, 0x92, 0xF8, 0x87 }}

#define MAX_BUFFER_SIZE                       256

//
// Prototypes
//

//
// Support functions
//
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL   **ProfileLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  );

#endif
