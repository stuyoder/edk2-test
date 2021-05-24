## @file
#
#  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2011 - 2012, ARM Ltd. All rights reserved.<BR>
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
##
#/*++
#
# Module Name:
#
#   makefile
#
# Abstract:
#
#   This is the makefile for creating a private/public keypair for Secure Boot testing.
#
#--*/

BASE_NAME=SecureBoot
TARGET=$(BIN_DIR)/$(BASE_NAME)

all: TestPK1 TestKEK1 TestDB1 TestDBX1

TestPK1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_PK/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000
	openssl x509 -outform der -in $(TARGET)_$(@).crt -out $(TARGET)_$(@).der

TestKEK1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_PK/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000
	openssl x509 -outform der -in $(TARGET)_$(@).crt -out $(TARGET)_$(@).der

TestDB1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_DB/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000
	openssl x509 -outform der -in $(TARGET)_$(@).crt -out $(TARGET)_$(@).der

TestDBX1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_DB/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000
	openssl x509 -outform der -in $(TARGET)_$(@).crt -out $(TARGET)_$(@).der

clean:
	$(RM) $(BIN_DIR)/$(TARGET)_*.key
	$(RM) $(BIN_DIR)/$(TARGET)_*.crt
	$(RM) $(BIN_DIR)/$(TARGET)_*.der
