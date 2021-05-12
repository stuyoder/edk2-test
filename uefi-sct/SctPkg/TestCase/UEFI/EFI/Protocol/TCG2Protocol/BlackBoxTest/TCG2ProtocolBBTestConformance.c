/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2021, Arm Inc. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

    TCG2BBTestConformance.c

Abstract:

    for EFI Driver TCG2 Protocol's Basic Test

--*/

#include "TCG2ProtocolBBTest.h"

/**
 *  @brief Entrypoint for GetCapability() Function Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetCapabilityConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TCG2_PROTOCOL                     *TCG2;
  //
  // init
  //
  TCG2 = (EFI_TCG2_PROTOCOL*)ClientInterface;

  //

  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Test Using NULL BootCapablity Pointer
  BBTestGetCapabilityConformanceTestCheckpoint1 (StandardLib, TCG2);

  // Test Using Capability struct with struct size less than full size
  BBTestGetCapabilityConformanceTestCheckpoint2 (StandardLib, TCG2);

  // Test with full size field
  BBTestGetCapabilityConformanceTestCheckpoint3 (StandardLib, TCG2);

  return EFI_SUCCESS;
}


EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;

  EFI_TCG2_BOOT_SERVICE_CAPABILITY *BootServiceCapPtr = NULL;
  Status = TCG2->GetCapability (
                           TCG2,
                           BootServiceCapPtr);

  // Ensure GetCapablity returns Invalid Parameter when passing in NULL pointer
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid001,
                 L"TCG2_PROTOCOL.GetCapability - GetCapability() returns EFI_INVALID_PARAMETER with NULL pointer Capability Struct Passed in",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


}

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  char StructureVersionMajor;
  char StructureVersionMinor;
  char ProtocolVersionMajor;
  char ProtocolVersionMinor;

  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;
  BootServiceCap.Size = sizeof(UINT8) + (sizeof(EFI_TCG2_VERSION) * 2);

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  StructureVersionMajor = BootServiceCap.StructureVersion.Major;
  StructureVersionMinor = BootServiceCap.StructureVersion.Minor;

  // If the input ProtocolCapability.Size < sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY)
  // the function will initialize the fields included in ProtocolCapability.Size.

  if ((StructureVersionMajor != 1) | (StructureVersionMinor != 1)) {
     StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: Unexpected struct version numbers returned"
                     );

     AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  ProtocolVersionMajor = BootServiceCap.ProtocolVersion.Major;
  ProtocolVersionMinor = BootServiceCap.ProtocolVersion.Minor;

  if ((ProtocolVersionMajor != 1) | (ProtocolVersionMinor != 1)) {
     StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: Unexpected protocol version numbers returned."
                     );

     AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid002,
                 L"TCG2_PROTOCOL.GetCapability protocol version check failed.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetCapabilityConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  char StructureVersionMajor;
  char StructureVersionMinor;
  char ProtocolVersionMajor;
  char ProtocolVersionMinor;

  EFI_TCG2_BOOT_SERVICE_CAPABILITY      BootServiceCap;
  BootServiceCap.Size = sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY);

  Status = TCG2->GetCapability (
                           TCG2,
                           &BootServiceCap);

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  StructureVersionMajor = BootServiceCap.StructureVersion.Major;
  StructureVersionMinor = BootServiceCap.StructureVersion.Minor;

  // TCG EFI Protocol spec 6.4.4 #4
  if ((StructureVersionMajor != 1) | (StructureVersionMinor != 1)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: GetCapabilty should have StructureVersion 1.1"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // TCG EFI Protocol spec 6.4.4 #4
  ProtocolVersionMajor = BootServiceCap.ProtocolVersion.Major;
  ProtocolVersionMinor = BootServiceCap.ProtocolVersion.Minor;

  if ((ProtocolVersionMajor != 1) | (ProtocolVersionMinor != 1)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: protocol version must be 1.1"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (!(BootServiceCap.SupportedEventLogs &  EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: GetCapabilty must support TCG2 event log format"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (BootServiceCap.NumberOfPcrBanks < 1 ) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: expect at least 1 PCR bank"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  EFI_TCG2_EVENT_ALGORITHM_BITMAP HashBitMapAlgos =  EFI_TCG2_BOOT_HASH_ALG_SHA256 | EFI_TCG2_BOOT_HASH_ALG_SHA384 | EFI_TCG2_BOOT_HASH_ALG_SHA512;

  if (!(BootServiceCap.HashAlgorithmBitmap & HashBitMapAlgos)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: unexpected hash algorithms reported = %x",
                     BootServiceCap.HashAlgorithmBitmap
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  if (!(BootServiceCap.ActivePcrBanks & HashBitMapAlgos)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetCapablity Test: unexpected active PCR banks reported = %x",
                     BootServiceCap.ActivePcrBanks
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid003,
                 L"TCG2_PROTOCOL.GetCapability - GetCapability checks failed",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

