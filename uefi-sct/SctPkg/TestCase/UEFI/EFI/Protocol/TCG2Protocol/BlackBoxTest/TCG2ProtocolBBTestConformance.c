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

/**
 *  @brief Entrypoint for GetActivePcrBanks() Function Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestGetActivePcrBanksConformanceTest (
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

  //Test Using NULL Pointer
  BBTestGetActivePcrBanksConformanceTestCheckpoint1 (StandardLib, TCG2);

  //Test with correct size field
 BBTestGetActivePcrBanksConformanceTestCheckpoint2 (StandardLib, TCG2);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for HashLogExtendEvent() Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */

EFI_STATUS
BBTestHashLogExtendEventConformanceTest (
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

  //Test Using NULL Pointer
  BBTestHashLogExtendEventConformanceTestCheckpoint1 (StandardLib, TCG2);

  //Test with correct size field
  BBTestHashLogExtendEventConformanceTestCheckpoint2 (StandardLib, TCG2);

  // Test GetEventLog using invalid EventLog Format
  BBTestHashLogExtendEventConformanceTestCheckpoint3 (StandardLib, TCG2);

  // Test GetEventLog using valid EventLog Format
  BBTestHashLogExtendEventConformanceTestCheckpoint4 (StandardLib, TCG2);

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

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;

  EFI_TCG2_EVENT_ALGORITHM_BITMAP *ActivePcrBanks = NULL;
  Status = TCG2->GetActivePcrBanks (
                           TCG2,
                           ActivePcrBanks);

  // Ensure GetCapablity returns Invalid Parameter when passing in NULL pointer
  if (EFI_INVALID_PARAMETER == Status) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid004,
                 L"TCG2_PROTOCOL.GetActivePcrBanks - GetActivePcrBanks() returns EFI_INVALID_PARAMETER with NULL pointer Passed in",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestGetActivePcrBanksConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;

  EFI_TCG2_EVENT_ALGORITHM_BITMAP ActivePcrBanks;
  Status = TCG2->GetActivePcrBanks (
                           TCG2,
                           &ActivePcrBanks);

  // Ensure GetActivePcrBanks returns EFI_SUCCESS
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetActivePcrBanks Test: GetActivePcrBanks should return EFI_SUCCESS",
                     ActivePcrBanks
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  EFI_TCG2_EVENT_ALGORITHM_BITMAP BitMapAlgos =  EFI_TCG2_BOOT_HASH_ALG_SHA256 | EFI_TCG2_BOOT_HASH_ALG_SHA384 | EFI_TCG2_BOOT_HASH_ALG_SHA512;

  // Ensure ActivePcrBanks has SHA256/384/512 in its Bitmap
  if (!(ActivePcrBanks & BitMapAlgos)) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetActivePcrBanks Test: GetActiVePcrBanks should have SHA256/384/512 Algorithm in its Bitmap. ActivePcrBanks = %x",
                     ActivePcrBanks
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid005,
                 L"TCG2_PROTOCOL.GetActivePcrBanks - GetActivePcrBanks should return with EFI_SUCCESS and have SHA256/384/512 Algoritms in its Bitmap",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  UINT64                                Flags = 0;
  EFI_PHYSICAL_ADDRESS                  DataToHash;
  UINT64                                DataToHashLen;
  EFI_TCG2_EVENT                        *EfiTcgEvent;
  const CHAR16                          *EventData = L"TCG2 Protocol Test";
  const CHAR16                          *Str = L"The quick brown fox jumps over the lazy dog";
  UINT32                                EfiTcgEventSize = sizeof(EFI_TCG2_EVENT) + SctStrSize(EventData);
  
  DataToHash =  Str;
  DataToHashLen = SctStrLen(Str);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   EfiTcgEventSize,
                   (VOID **)&EfiTcgEvent
                   );

  EfiTcgEvent->Header.HeaderSize = sizeof(EFI_TCG2_EVENT_HEADER);
  EfiTcgEvent->Header.EventType = EV_POST_CODE;
  EfiTcgEvent->Header.PCRIndex = 16;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctStrSize(EventData);

  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in NULL DataToHash pointer
  // EFI Protocol Spec Section 6.6.5 #1
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           NULL,
                           0,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid004,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with NULL DataToHash Pointer should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in NULL EfiTcgEvent pointer
  // EFI Protocol Spec Section 6.6.5 #1
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           NULL);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
   } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
   }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid005,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with NULL EfiTcgEvent Pointer should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  
  // Ensure HashLogExtendEvent returns Invalid Parameter when passed in EventSize < HeaderSize + sizeof(UINT32)
  // EFI Protocol Spec Section 6.6.5 #2
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + sizeof(UINT32) - 1;
  
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid006,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with Event.Size < Event.Header.HeaderSize + sizeof(UINT32) should return EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
 
  // Ensure HashLogExtendEvent returns Invalid Parameter when passing in PCR Index > 23
  // EFI Protocol Spec Section 6.6.5 #3
  EfiTcgEvent->Header.PCRIndex = 24;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctStrSize(EventData);
  
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
 
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid007,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - Test with PCRIndex > 23 should return  EFI_INVALID_PARAMETER",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{

  EFI_TCG2_EVENT                        *EfiTcgEvent;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  UINT64                                Flags;
  EFI_PHYSICAL_ADDRESS                  DataToHash;
  UINT64                                DataToHashLen;
  const CHAR16 *Str = L"The quick brown fox jumps over the lazy dog";
  const CHAR16 *EventData = L"TCG2 Protocol Test";
  UINT32 EfiTcgEventSize = sizeof(EFI_TCG2_EVENT) + SctStrSize(EventData);

  DataToHash = Str;
  DataToHashLen = SctStrLen(Str);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   EfiTcgEventSize,
                   (VOID **)&EfiTcgEvent
                   );

  EfiTcgEvent->Header.HeaderSize = sizeof(EFI_TCG2_EVENT_HEADER);
  EfiTcgEvent->Header.EventType = EV_POST_CODE;
  EfiTcgEvent->Header.PCRIndex = 16;
  EfiTcgEvent->Size = EfiTcgEvent->Header.HeaderSize + SctStrSize(EventData);

  // Ensure HashLogExtendEvent returns EFI_SUCCESS with valid parameters
  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (Status != EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid008,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - HashLogExtendEvent() Test: HashLogExtendEvent should return EFI_SUCCESS",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Test with valid Parameters but with Flags = PE_COFF_IMAGE
  // EFI Protocol Spec Section 6.6.5 #4
  Flags = PE_COFF_IMAGE;

  Status = TCG2->HashLogExtendEvent (
                           TCG2,
                           Flags,
                           DataToHash,
                           DataToHashLen,
                           EfiTcgEvent);

  if (Status != EFI_UNSUPPORTED) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid009,
                 L"TCG2_PROTOCOL.HashLogExtendEvent - HashLogExtendEvent() Test Handling of PE_COFF_IMAGE flag",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (EfiTcgEvent);
  
  return EFI_SUCCESS;
}

#define EFI_TCG2_INVALID_EVENT_LOG_FORMAT 0x20
EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_EVENT_LOG_FORMAT             EventLogFormat;
  EFI_PHYSICAL_ADDRESS                  *EventLogLocation;
  EFI_PHYSICAL_ADDRESS                  *EventLogLastEntry;
  BOOLEAN                               *EventLogTruncated;

  // Ensure Get EventLog returns Invalid Parameter when passed invalid format
  EventLogFormat = EFI_TCG2_INVALID_EVENT_LOG_FORMAT;

  Status = TCG2->GetEventLog (
                           TCG2,
                           EventLogFormat,
                           EventLogLocation,
                           EventLogLastEntry,
                           EventLogTruncated);

  if (EFI_INVALID_PARAMETER != Status) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid010,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return EFI_INVALID_PARAMETER when passed in invalid EventLog Format",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
BBTestHashLogExtendEventConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TCG2_PROTOCOL                     *TCG2
  )
{
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_STATUS                            Status;
  EFI_TCG2_EVENT_LOG_FORMAT             EventLogFormat;
  EFI_PHYSICAL_ADDRESS                  EventLogLocation;
  EFI_PHYSICAL_ADDRESS                  EventLogLastEntry;
  BOOLEAN                               EventLogTruncated;
  TCG_PCR_EVENT                         *EventLogHeader;
  TCG_EfiSpecIDEventStruct              *EventLogHeaderSpecEvent;
  TCG_PCR_EVENT2                        *LastEvent;
  UINT8 *data = "Spec ID Event03\0\0";

  EventLogFormat = EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;

  // Call GetEventLog with valid EventLogFormat
  Status = TCG2->GetEventLog (
                           TCG2,
                           EventLogFormat,
                           &EventLogLocation,
                           &EventLogLastEntry,
                           &EventLogTruncated);


  AssertionType = EFI_TEST_ASSERTION_PASSED;

  // Verify GetEventLog returns EFI_SUCCESS
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: GetEventLog should return EFI_SUCCESS with valid EventLogFormat, Status = %r",
                     Status
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;

  }


  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid011,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return EFI_SUCCESS",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // If GetEventLog doesn't return EFI_SUCCESS abort test
  if (Status != EFI_SUCCESS) {
    return Status;
  }

  EventLogHeader = (TCG_PCR_EVENT *) EventLogLocation;
  EventLogHeaderSpecEvent = (TCG_EfiSpecIDEventStruct *) EventLogHeader->Event;

  AssertionType = EFI_TEST_ASSERTION_PASSED;

  // Verify EventLogHeader PCR index = 0
  if (EventLogHeader->PCRIndex != 0) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader should have PCR index = 0"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify EventLogHeader event type = EV_NO_ACTION
  if (EventLogHeader->EventType != EV_NO_ACTION) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader should be EventType = EV_NO_ACTION"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  Status = SctStrCmp(EventLogHeaderSpecEvent->signature, data);
  // Verify EventLog Signature
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: EventLogHeader Signature did not match \'Spec ID Event03\'"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid012,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should return correct EventLogHeader",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  LastEvent = (TCG_PCR_EVENT2 *) EventLogLastEntry;

  // Verify Last Event PCR = 16
  if (LastEvent->PCRIndex != 16) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: PCR Index of Last event should be 16"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  // Verify last event type = EV_POST_CODE
  if (LastEvent->EventType != EV_POST_CODE) {
    StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nTCG2 Protocol GetEventLog Test: PCR Index of last event should be type EV_POST_CODE"
                     );

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTcg2ConformanceTestAssertionGuid013,
                 L"TCG2_PROTOCOL.GetEventLog - GetEventLog() should record Event from Checkpoint2 as last EventLogEntry",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}
