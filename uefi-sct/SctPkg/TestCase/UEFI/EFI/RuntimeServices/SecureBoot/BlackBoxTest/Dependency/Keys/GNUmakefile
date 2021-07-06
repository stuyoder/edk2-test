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
FUTURE_DATE=$(shell date --rfc-3339=date -d "+1 year")
FUTURE_DATE2=$(shell date --rfc-3339=date -d "+1 day")
PAST_DATE=$(shell date --rfc-3339=date -d "-1 year")

ifdef KEYS_DIR
TEST_KEK1_CRT=$(KEYS_DIR)/TestKEK1.crt
TEST_DB1_CRT=$(KEYS_DIR)/TestDB1.crt
TEST_DBX1_CRT=$(KEYS_DIR)/TestDBX1.crt
TEST_KEK1_KEY=$(KEYS_DIR)/TestKEK1.key
TEST_PK1_CRT=$(KEYS_DIR)/TestPK1.crt
TEST_PK1_KEY=$(KEYS_DIR)/TestPK1.key
else
TEST_KEYS=TestPK1 TestKEK1 TestDB1 TestDBX1
TEST_KEK1_CRT=$(BIN_DIR)/SecureBoot_TestKEK1.crt
TEST_KEK1_KEY=$(BIN_DIR)/SecureBoot_TestKEK1.key
TEST_PK1_CRT=$(BIN_DIR)/SecureBoot_TestPK1.crt
TEST_PK1_KEY=$(BIN_DIR)/SecureBoot_TestPK1.key
endif

all: $(TEST_KEYS) TestKEK2 KEKSigList1.auth TestImage1.bin NullKEK.auth NullDB.auth NullDBX.auth TestKEK1.auth TestDB1.auth TestDBX1.auth SignCert1 dbSigList1.auth SignCert2 SignCert3 RevokedCert1 RevokedCert2 RevokedCert3 RevokedCert4 dbSigList2.auth dbSigList3.auth

TestImage1.bin:
	head -c 16K </dev/urandom > $(TARGET)_$(@)

TestImage5.bin:
	cp $(BIN_DIR)/Ebc_EbcDriver.efi $(TARGET)_$(@)

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

TestKEK2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_KEK/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

SignCert1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert1/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

SignCert2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert2/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

SignCert3:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert3/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

RevokedCert1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert1/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

RevokedCert2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert2/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

RevokedCert3:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert3/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

RevokedCert4:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert4/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

KEKSigList1.auth: TestKEK2
	cert-to-efi-sig-list $(TEST_KEK1_CRT) $(BIN_DIR)/SecureBoot_TestKEK1.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestKEK2.crt $(BIN_DIR)/SecureBoot_TestKEK2.esl
	cat $(BIN_DIR)/SecureBoot_TestKEK1.esl $(BIN_DIR)/SecureBoot_TestKEK2.esl > $(BIN_DIR)/SecureBoot_KEKSigList1.esl
	sign-efi-sig-list -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_KEKSigList1.esl $(BIN_DIR)/SecureBoot_KEKSigList1.auth

NullKEK.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullKEK.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_NullKEK.esl $(BIN_DIR)/SecureBoot_NullKEK.auth

NullDB.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullDB.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_NullDB.esl $(BIN_DIR)/SecureBoot_NullDB.auth

NullDBX.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullDBX.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) dbx $(BIN_DIR)/SecureBoot_NullDBX.esl $(BIN_DIR)/SecureBoot_NullDBX.auth

TestKEK1.auth:
	cert-to-efi-sig-list $(TEST_KEK1_CRT) $(BIN_DIR)/SecureBoot_TestKEK1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_TestKEK1.esl $(BIN_DIR)/SecureBoot_TestKEK1.auth

TestDB1.auth:
	cert-to-efi-sig-list $(TEST_DB1_CRT) $(BIN_DIR)/SecureBoot_TestDB1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_TestDB1.esl $(BIN_DIR)/SecureBoot_TestDB1.auth

TestDBX1.auth:
	cert-to-efi-sig-list $(TEST_DBX1_CRT) $(BIN_DIR)/SecureBoot_TestDBX1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) dbx $(BIN_DIR)/SecureBoot_TestDBX1.esl $(BIN_DIR)/SecureBoot_TestDBX1.auth

dbSigList1.auth: SignCert1
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert1.crt $(BIN_DIR)/SecureBoot_TestDB1.esl
	sign-efi-sig-list -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_TestDB1.esl $(BIN_DIR)/SecureBoot_DBSigList1.auth

KEKSigList3.auth: TestKEK3
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestKEK3.crt $(BIN_DIR)/SecureBoot_TestKEK3.esl
	sign-efi-sig-list -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_KEKSigList1.esl $(BIN_DIR)/SecureBoot_KEKSigList1.auth

dbSigListLong: SignCert2 SignCert3 RevokedCert1 RevokedCert2 RevokedCert3 RevokedCert4 TestImage5.bin
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert2.crt $(BIN_DIR)/SecureBoot_TestDB2.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert3.crt $(BIN_DIR)/SecureBoot_TestDB3.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_RevokedCert1.crt $(BIN_DIR)/SecureBoot_TestDB4.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_RevokedCert2.crt $(BIN_DIR)/SecureBoot_TestDB5.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_RevokedCert3.crt $(BIN_DIR)/SecureBoot_TestDB6.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_RevokedCert4.crt $(BIN_DIR)/SecureBoot_TestDB7.esl
	hash-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestImage5.bin $(BIN_DIR)/SecureBoot_TestDB8.esl
	cat $(BIN_DIR)/SecureBoot_TestDB2.esl $(BIN_DIR)/SecureBoot_TestDB3.esl $(BIN_DIR)/SecureBoot_TestDB4.esl $(BIN_DIR)/SecureBoot_TestDB5.esl $(BIN_DIR)/SecureBoot_TestDB6.esl  $(BIN_DIR)/SecureBoot_TestDB7.esl $(BIN_DIR)/SecureBoot_TestDB8.esl  > $(BIN_DIR)/SecureBoot_DBSigListLong.esl

dbSigList2.auth: dbSigListLong
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE2)" db $(BIN_DIR)/SecureBoot_DBSigListLong.esl $(BIN_DIR)/SecureBoot_DBSigList2.auth

dbSigList3.auth: dbSigListLong
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE2)" dbx $(BIN_DIR)/SecureBoot_DBSigListLong.esl $(BIN_DIR)/SecureBoot_DBSigList3.auth

clean:
	$(RM) $(BIN_DIR)/$(TARGET)_*.key
	$(RM) $(BIN_DIR)/$(TARGET)_*.crt
	$(RM) $(BIN_DIR)/$(TARGET)_*.der
