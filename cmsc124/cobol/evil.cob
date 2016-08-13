      *Jan Keith C. Darunday (2012-10053)
      *CMSC124 T-3L
       IDENTIFICATION DIVISION.
       PROGRAM-ID. STUD-REC.

       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
       SELECT UACCOUNT ASSIGN TO "ACCOUNTS.DAT".

       DATA DIVISION.
       FILE SECTION.
       FD UACCOUNT.
       01 fuser.
         02 fusername pic X(20).
         02 fuserpin pic 9(4).
         02 fbdate.
           03 fbmonth pic X(10).
           03 fbday pic 9(2).
           03 fbyear pic 9(4).
         02 fbalance pic 9(5)V9(2).

       WORKING-STORAGE SECTION.
       77 cnt pic 9(1).
       77 EOF pic 9(1) VALUE ZERO.
       77 iterator pic 9(1).
       77 toggle pic 9(1).
       77 loggedin pic 9(1).
       77 choice pic 9(1).
       77 choice2 pic 9(1).
       77 val pic 9(10)V9(2).
       77 luser pic X(20).
       01 useraccount.
         02 user OCCURS 5 TIMES.
           03 username pic X(20).
           03 userpin pic 9(4).
           03 bdate.
             04 bmonth pic X(10).
             04 bday pic 9(2).
             04 byear pic 9(4).
           03 balance pic 9(5)V9(2).

       PROCEDURE DIVISION.
      *writes data to file
       COMPUTE cnt = 1.
       PERFORM READDATA
       PERFORM UNTIL choice=3
         DISPLAY "[1] Create New Account"
         DISPLAY "[2] Login"
         DISPLAY "[3] Exit"
         DISPLAY "Choice: " WITH NO ADVANCING
         ACCEPT choice
         IF choice = 1
           PERFORM CACC
         END-IF
         IF choice = 2
           PERFORM DOLOGIN
           PERFORM PLOOP UNTIL loggedin=0
         END-IF
         END-PERFORM.

       PERFORM WRITEDATA
       STOP RUN.


       PLOOP.
         DISPLAY "[0] Logout".
         DISPLAY "[1] Withdraw".
         DISPLAY "[2] Deposit".
         DISPLAY "Choice: " WITH NO ADVANCING.
         ACCEPT choice2.
         IF choice2 = 1
           PERFORM WITHDRAW
           DISPLAY "Would you like to do another transaction?"
         END-IF
         IF choice2 = 2
           PERFORM DEPOSIT
           DISPLAY "Would you like to do another transaction?"
         END-IF
         IF choice2 = 0
           COMPUTE loggedin = 0
         END-IF
         EXIT.
         
       CACC.
         IF cnt >= 6
           DISPLAY "There are already 5 accounts."
         ELSE
           DISPLAY "User Name (a-zA-Z0-9): " WITH NO ADVANCING
           ACCEPT username(cnt)
           DISPLAY "  Month: " WITH NO ADVANCING
           ACCEPT bmonth(cnt)
           DISPLAY "  Day  : " WITH NO ADVANCING
           ACCEPT bday(cnt)
           DISPLAY "  Year : " WITH NO ADVANCING
           ACCEPT byear(cnt)
           DISPLAY "PIN: " WITH NO ADVANCING
           ACCEPT userpin(cnt)
           COMPUTE balance(cnt) = 500.00
           COMPUTE cnt = cnt + 1
         END-IF
         EXIT.

       DEPOSIT.
         DISPLAY "Amount to deposit : " WITH NO ADVANCING.
         ACCEPT val.
         COMPUTE balance(loggedin) = balance(loggedin) + val.
         EXIT.

       WITHDRAW.
         DISPLAY "Amount to withdraw : " WITH NO ADVANCING.
         ACCEPT val.
         COMPUTE balance(loggedin) = balance(loggedin) - val.
         EXIT.

       DOLOGIN.
         COMPUTE iterator = 1.
         DISPLAY "Username : " WITH NO ADVANCING.
         ACCEPT luser.
         PERFORM UNTIL iterator=cnt
           IF luser = username(iterator)
             COMPUTE loggedin = iterator
           END-IF
           COMPUTE iterator = iterator + 1
           END-PERFORM.
         IF loggedin > 0
           DISPLAY "PIN : " WITH NO ADVANCING
           ACCEPT luser
           DISPLAY loggedin " " userpin(loggedin)
           IF luser = userpin(loggedin)
             DISPLAY "Successfully Logged In!"
           ELSE
             DISPLAY "Invalid PIN"
             COMPUTE loggedin = 0
           END-IF
         ELSE
           DISPLAY "User not found"
         END-IF
         EXIT.

       WRITEDATA.
         COMPUTE iterator = 1.
         OPEN OUTPUT UACCOUNT.
         PERFORM UNTIL iterator=cnt
           DISPLAY "Writing " username(iterator) " at " iterator
           MOVE user(iterator) TO fuser
           COMPUTE iterator = iterator + 1
           WRITE fuser
           END-PERFORM.
         CLOSE UACCOUNT.
         EXIT.


       READDATA.
         COMPUTE cnt = 1.
         OPEN INPUT UACCOUNT.
         PERFORM UNTIL EOF=1
           READ UACCOUNT
           AT END MOVE 1 TO EOF
           NOT AT END
           PERFORM RECC
             END-PERFORM.
         CLOSE UACCOUNT.
         DISPLAY cnt.
         EXIT.

       RECC.
         MOVE  fuser TO user(cnt)
         DISPLAY "Reading " username(cnt) " to " cnt.
         COMPUTE cnt = cnt + 1.
         EXIT.








