      * A simple cobol program for CMSC124 COBOL exercise 2
      * Copyright (C) 2014 Ferriel Lisandro B. Melarpis
      * This program is free software: you can redistribute it and/or modify
      * it under the terms of the GNU General Public License as published by
      * the Free Software Foundation, either version 3 of the License, or (at
      * your option) any later version.
      * This program is distributed in the hope that it will be useful, but
      * WITHOUT ANY WARRANTY; without even the implied warranty of
      * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
      * General Public License for more details.
      * You should have received a copy of the GNU General Public License
      * along with this program.  If not, see <http://www.gnu.org/licenses/>.
	IDENTIFICATION DIVISION.
	PROGRAM-ID. StudentRecords.
	AUTHOR. FerrielMelarpis.
	
	ENVIRONMENT DIVISION.
	INPUT-OUTPUT SECTION.
	FILE-CONTROL.
      * assign file pointer to the file
	SELECT fp ASSIGN TO "ACCOUNTS.DAT".
      * data declarations
	DATA DIVISION.
      * structure for file
	FILE SECTION.
	FD fp.
	01 fuser.
              02 fusername pic X(20).
              02 fbirthday.
                     03 fbmonth pic X(10).
                     03 fbday pic 99.
                     03 fbyear pic 9(4).
              02 fuserpin pic 9(4).
              02 fusermoney pic 9(5)V99.
	WORKING-STORAGE SECTION.
      * variables
       77 eof pic 9 VALUE 0.
       77 t pic 9.
       77 choice pic 9 VALUE 3.
       77 logchoice pic 9.
       77 log pic 9.
       77 val pic 9(5)V99.
       77 cont pic X.
       77 tmpuser pic X(20).
      * array of structures for retrieving data from file
       01 useraccount.
              02 user OCCURS 5 TIMES INDEXED BY cnt.
                     03 username pic X(20).
                     03 userbirthday.
                            04 bmonth pic X(10).
                            04 bday pic 99.
                            04 byear pic 9(4).
                     03 userpin pic 9(4).
                     03 usermoney pic 9(5)V99.
      * main process
       PROCEDURE DIVISION.
              MOVE 1 to cnt.
              PERFORM ReadFile.
              PERFORM MainMenu UNTIL choice=0.
              PERFORM WriteFile.
       STOP RUN.
      * terminate
      
      * function for displaying the main menu
       MainMenu.
       DISPLAY " ".
       DISPLAY "===========================================".
       DISPLAY "[1] Add New Account.".
       DISPLAY "[2] Log In To An Existing Account.".
       DISPLAY "[0] End Transaction.".
       DISPLAY "===========================================".
       DISPLAY "Enter choice: " WITH NO ADVANCING.
       ACCEPT choice.
       IF choice=1
              IF cnt<=5
              PERFORM AddAccount
              ELSE
              DISPLAY "________________________________________"
              DISPLAY "NOTICE: ACCOUNTS.DAT is already full!"
              DISPLAY "________________________________________"
       END-IF.
       IF choice=2
              PERFORM Authenticate
              PERFORM Transact UNTIL log=0
       END-IF.
       EXIT.
      * function for updating(increasing) user's money
       Deposit.
       DISPLAY "Amount to deposit : " WITH NO ADVANCING.
       ACCEPT val.
       COMPUTE usermoney(log) = usermoney(log) + val.
       EXIT.
      * function for updating(decreasing) user's money 
       Withdraw.
       DISPLAY "Amount to withdraw : " WITH NO ADVANCING.
       ACCEPT val.
       COMPUTE usermoney(log) = usermoney(log) - val.
       EXIT.
      * function (submenu) that processes logging in
       Transact.
       DISPLAY " "
       DISPLAY "==========================================="
       DISPLAY "[1] Edit Account"
       DISPLAY "[2] Delete Account"
       DISPLAY "[3] Deposit"
       DISPLAY "[4] Withdraw"
       DISPLAY "==========================================="
       DISPLAY "Enter choice: " WITH NO ADVANCING
       ACCEPT logchoice
       IF logchoice=1
              PERFORM EditUser
              DISPLAY "Continue transaction? (Y/n) : " WITH NO ADVANCING
              ACCEPT cont
              IF cont="n"
                     MOVE 0 TO log
              END-IF
       END-IF
       IF logchoice=2
              PERFORM DeleteUser
              MOVE 0 TO log
       END-IF
       IF logchoice=3
              PERFORM Deposit
              DISPLAY "Continue transaction? (Y/n) : " WITH NO ADVANCING
              ACCEPT cont
              IF cont="n"
                     MOVE 0 TO log
              END-IF
       END-IF
       IF logchoice=4
              PERFORM Withdraw
              DISPLAY "Continue transaction? (Y/n) : " WITH NO ADVANCING
              ACCEPT cont
              IF cont="n"
                     MOVE 0 TO log
              END-IF
       END-IF
       EXIT. 
      * function for deleting the logged in user
       DeleteUser.
              DISPLAY "________________________________________"
              DISPLAY "=Delete Account="
              SUBTRACT 1 FROM cnt GIVING cnt
              MOVE user(cnt) TO user(log)
              DISPLAY "Your account has been deleted."
              MOVE 0 TO log
       EXIT.
      * function for editing the logged in user
       EditUser.
              DISPLAY "________________________________________"
              DISPLAY "=Edit Account="
              DISPLAY "Enter new name: " WITH NO ADVANCING
              ACCEPT username(log)
              DISPLAY "Enter new PIN: " WITH NO ADVANCING
              ACCEPT userpin(log)
              DISPLAY "_Birhtday_"
              DISPLAY "Enter Month: " WITH NO ADVANCING
              ACCEPT bmonth(log)
              DISPLAY "Enter Day: " WITH NO ADVANCING
              ACCEPT bday(log)
              DISPLAY "Enter Year: " WITH NO ADVANCING
              ACCEPT byear(log)
              DISPLAY "Your account has been successfully updated."
       EXIT.
      * function for checking if account is valid
       Authenticate.
       MOVE 1 TO t
       DISPLAY "Name: " WITH NO ADVANCING
       ACCEPT tmpuser
       PERFORM UNTIL t=cnt
              IF tmpuser = username(t)
              MOVE t TO log
              END-IF
              ADD 1 TO t GIVING t
       END-PERFORM
       IF log>0
       DISPLAY "PIN: " WITH NO ADVANCING
       ACCEPT tmpuser
              IF tmpuser=userpin(log)
              DISPLAY "User Authenticated."
              ELSE
              DISPLAY "Invalid PIN."
              MOVE 0 TO log
              END-IF
       ELSE
       DISPLAY "User not found."
       END-IF
       EXIT.
      * function for adding users
       AddAccount.
       DISPLAY "Name: " WITH NO ADVANCING.
       ACCEPT username(cnt).
       DISPLAY "_Birthday_".
       DISPLAY "-->Month: " WITH NO ADVANCING.
       ACCEPT bmonth(cnt).
       DISPLAY "-->Day  : " WITH NO ADVANCING.
       ACCEPT bday(cnt).
       DISPLAY "-->Year : " WITH NO ADVANCING.
       ACCEPT byear(cnt).
       DISPLAY "PIN: " WITH NO ADVANCING.
       ACCEPT userpin(cnt)
       MOVE 500.00 TO usermoney(cnt).
       ADD 1 TO cnt GIVING cnt.
       EXIT.
      * function for writing the data to file
       WriteFile.
       MOVE 1 TO t.
       OPEN OUTPUT fp.
       PERFORM UNTIL t=cnt
       MOVE user(t) TO fuser
       ADD 1 TO t GIVING t
       WRITE fuser
       END-PERFORM.
       CLOSE fp.
       EXIT.
      * function for reading data from file
       ReadFile.
       MOVE 1 TO cnt.
       OPEN INPUT fp.
       PERFORM UNTIL eof=1
       READ fp
       AT END MOVE 1 TO eof
       NOT AT END
       PERFORM Upload
       END-PERFORM.
       CLOSE fp.
       EXIT.
      * function for transferring each user info to array
       Upload.
       MOVE  fuser TO user(cnt)
       ADD 1 TO cnt GIVING cnt.
       EXIT.
      * END OF PROGRAM