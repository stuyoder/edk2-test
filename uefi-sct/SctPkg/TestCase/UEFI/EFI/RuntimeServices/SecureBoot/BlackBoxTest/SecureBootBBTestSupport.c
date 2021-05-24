/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SecureBootBBTestSupport.c

Abstract:

  BB test support source file for Secure Boot

--*/

#include "SctLib.h"
#include "SecureBootBBTestMain.h"
#include "SecureBootBBTestSupport.h"

//
// globals variables
//

EFI_DEVICE_PATH_PROTOCOL        *gDevicePath     = NULL;
CHAR16                          *gFilePath       = NULL;
EFI_HANDLE                      gDeviceHandle;

//
// internal helper function.
//

/*
 *  get the system device path and file path.
 *  @param ProfileLib the Profile Library Protocol instance.
 *  @return EFI_SUCCESS the system device path and file path were gotten successfully.
 */
EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  CHAR16                      *TempFilePath;
  EFI_STATUS                  Status;

  //
  // If gFilePath and gDevicePath has been assigned, return directly.
  //
  if ((gFilePath != NULL) && (gDevicePath != NULL)) {
    return EFI_SUCCESS;
  }

  //
  // Free gFilePath or gDevicePath
  //
  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
    gFilePath = NULL;
  }
  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
    gDevicePath = NULL;
  }

  //
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &TempDevicePath,
                         &TempFilePath
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //make up the file path.
  //
  gFilePath = NULL;
  gFilePath = SctPoolPrint (L"%s\\%s", TempFilePath, DEPENDECY_DIR_NAME);

  gtBS->FreePool (TempFilePath);

  if (gFilePath == NULL) {
    gtBS->FreePool (TempDevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gDevicePath = TempDevicePath;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}


/*
 *  get the device handle.
 *  @param ImageHandle the Image Handle instance.
 *  @return EFI_SUCCESS the device handle was gotten successfully.
 */
EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  )
{
  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;

  //
  // Get the image instance from the image handle
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &Image
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gDeviceHandle = Image->DeviceHandle;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}

/**
 *  Open the file and get the file size.
 *  @param FileName the file name to be opened.
 *  @param FileHandle the opened file handle.
 *  @param FileSize the opened file size.
 *  @return EFI_SUCCESS the file was opened successfully.
 */
EFI_STATUS
OpenFileAndGetSize (
  IN  CHAR16          *FileName,
  OUT EFI_FILE_HANDLE *FileHandle,
  OUT UINT32          *FileSize
  )
{
  EFI_FILE_HANDLE     RootDir;
  EFI_FILE_HANDLE     FHandle;
  CHAR16              *FileNameBuffer;
  EFI_STATUS          Status;
  EFI_FILE_INFO       *FileInfo;

  if (FileName == NULL || FileHandle == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  RootDir = NULL;
  //
  //Open the root directory.
  //
  RootDir = SctOpenRoot (gDeviceHandle);
  if (RootDir == NULL) {
    return EFI_NOT_FOUND;
  }
  //
  //make up the file name.
  //
  FileNameBuffer = SctPoolPrint (L"%s\\%s", gFilePath, FileName);
  if (FileNameBuffer == NULL) {
    RootDir->Close (RootDir);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = RootDir->Open (
                      RootDir,
                      &FHandle,
                      FileNameBuffer,
                      EFI_FILE_MODE_READ,
                      0
                      );
  RootDir->Close (RootDir);
  gtBS->FreePool (FileNameBuffer);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //get the file size.
  //
  if (FileSize != NULL) {
    FileInfo = NULL;
    Status = SctGetFileInfo (FHandle, &FileInfo);

    if (EFI_ERROR (Status)) {
      return Status;
    }
    *FileSize = (UINT32)FileInfo->FileSize;
    gtBS->FreePool (FileInfo);
  }

  *FileHandle = FHandle;
  //
  //done successfully return EFI_SUCCESS.
  //
  return EFI_SUCCESS;
}
