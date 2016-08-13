	IDENTIFICATION DIVISION.
	PROGRAM-ID. StudentRecords.
	AUTHOR. FerrielMelarpis.
	
	ENVIRONMENT DIVISION.
	INPUT-OUTPUT SECTION.
	FILE-CONTROL.
	SELECT fp ASSIGN TO "ACCOUNTS.DAT".
	
	DATA DIVISION.
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
       77 eof pic 9 VALUE 0.
       77 t pic 9.
       77 choice pic 9 VALUE 3.
       77 logchoice pic 9.
       77 log pic 9.
       77 val pic 9(5)V99.
       77 cont pic X.
       77 tmpuser pic X(20).
       
       01 useraccount.
              02 user OCCURS 5 TIMES INDEXED BY cnt.
                     03 username pic X(20).
                     03 userbirthday.
                            04 bmonth pic X(10).
                            04 bday pic 99.
                            04 byear pic 9(4).
                     03 userpin pic 9(4).
                     03 usermoney pic 9(5)V99.
       
       PROCEDURE DIVISION.
              MOVE 1 to cnt.
              PERFORM ReadFile.
              PERFORM MainMenu UNTIL choice=0.
              PERFORM WriteFile.
       STOP RUN.
       
       
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
       
       Deposit.
       DISPLAY "Amount to deposit : " WITH NO ADVANCING.
       ACCEPT val.
       COMPUTE usermoney(log) = usermoney(log) + val.
       EXIT.
       
       Withdraw.
       DISPLAY "Amount to withdraw : " WITH NO ADVANCING.
       ACCEPT val.
       COMPUTE usermoney(log) = usermoney(log) - val.
       EXIT.
       
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
       
       DeleteUser.
              DISPLAY "________________________________________"
              DISPLAY "=Delete Account="
              SUBTRACT 1 FROM cnt GIVING cnt
              MOVE user(cnt) TO user(log)
              DISPLAY "Your account has been deleted."
              MOVE 0 TO log
       EXIT.
       
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
       
       Upload.
       MOVE  fuser TO user(cnt)
       ADD 1 TO cnt GIVING cnt.
       EXIT.