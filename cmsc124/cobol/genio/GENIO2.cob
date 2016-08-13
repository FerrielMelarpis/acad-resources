       IDENTIFICATION DIVISION.
       PROGRAM-ID. STUD-REC2.
       ENVIRONMENT DIVISION.
       INPUT-OUTPUT SECTION.
       FILE-CONTROL.
       SELECT ATMREC ASSIGN TO "ACCOUNTS.DAT".

       DATA DIVISION.
       FILE SECTION.
       FD ATMREC.
       01 file-account.
        02 file-name PIC A(20).
        02 file-birthday.
         03 file-month PIC 9(2).
         03 file-day PIC 9(2).
        02 file-pin PIC X(4).
        02 file-cash PIC 9(10).

       01 ATM.
        02 account OCCURS 5 TIMES INDEXED BY counter.
         03 name PIC A(20).
         03 birthdate.
          04 birthmonth PIC 9(2).
          04 birthday PIC 9(2).
         03 pin PIC X(4).
         03 cash PIC 9(10).

       WORKING-STORAGE SECTION.
       77 EOF PIC 9 VALUE ZERO.
       77 choice PIC 9(1) VALUE ZERO.
       77 choice2 PIC 9(1) VALUE ZERO.
       77 repeat PIC 9(1) VALUE ZERO.
       77 temp PIC 9(1) VALUE ZERO.
       77 searchname PIC A(20).
       77 pass PIC X(4).
       77 transaction PIC 9(10).

       PROCEDURE DIVISION.
        MOVE 1 TO counter.
        OPEN INPUT ATMREC.
        PERFORM UNTIL EOF = 1
         READ ATMREC
         AT END MOVE 1 TO EOF
          NOT AT END
           PERFORM
            MOVE file-name TO name(counter)
            MOVE file-month TO birthmonth(counter)
            MOVE file-day TO birthday(counter)
            MOVE file-pin TO pin(counter)
            MOVE file-cash to cash(counter)
            DISPLAY name(counter)" "birthmonth(counter)" "
            DISPLAY birthday(counter)" "pin(counter)" "cash(counter)
            COMPUTE counter = counter + 1
            DISPLAY counter
           END-PERFORM
        END-PERFORM.
        CLOSE ATMREC.
        PERFORM UNTIL choice=3
         DISPLAY " "
         DISPLAY "[1] Create new account"
         DISPLAY "[2] Log-in to existing account"
         DISPLAY "[3] Exit"
         ACCEPT choice
      *CREATE NEW ACCOUNT
         IF choice=1
          IF counter<6
           DISPLAY "Name: "
           ACCEPT name(counter)
           DISPLAY "Birthday"
           DISPLAY "Month: "
           ACCEPT birthmonth(counter)
           DISPLAY "Day: "
           ACCEPT birthday(counter)
           DISPLAY "Pin: "
           ACCEPT pin(counter)
           COMPUTE cash(counter) = 500
           COMPUTE counter = counter + 1
          ELSE
           DISPLAY "The database is full."
          END-IF
         END-IF
      *LOGIN TO EXISTING ACCOUNT
         IF choice=2
      *The program will ask for a name, search for it in the database and, if found, asks the user for the password 
          DISPLAY "Name: "
          ACCEPT searchname
          MOVE 1 TO temp
          PERFORM UNTIL temp = counter
           IF name(temp) = searchname
            DISPLAY "Password: "
            ACCEPT pass
      *If the password input matches the pin, the user will be allowed to tamper with the account in 4 ways: edit, delete, deposit or withdraw
            IF pin(temp) = pass
             MOVE 1 TO repeat
             PERFORM UNTIL repeat=2
              DISPLAY " "
              DISPLAY "[1] Edit Account"
              DISPLAY "[2] Delete Account"
              DISPLAY "[3] Deposit"
              DISPLAY "[4] Withdraw"
              ACCEPT choice2
              IF choice2 = 1
               DISPLAY "Name: "
               ACCEPT name(temp)
               DISPLAY "Birthday"
               DISPLAY "Month: "
               ACCEPT birthmonth(temp)
               DISPLAY "Day: "
               ACCEPT birthday(temp)
               DISPLAY "Pin: "
               ACCEPT pin(temp)
               MOVE 2 TO repeat
              END-IF
              IF choice2 = 2
               COMPUTE counter = counter - 1
               MOVE name(counter) TO name(temp)
               MOVE birthmonth(counter) TO birthmonth(temp)
               MOVE birthday(counter) TO birthday(temp)
               MOVE pin(counter) TO pin(temp)
               MOVE cash(counter) TO cash(temp)
               DISPLAY "Account Deleted"
               MOVE 2 TO repeat
              END-IF
              IF choice2 = 3
               DISPLAY "Deposit"
               DISPLAY "Enter amount: "
               ACCEPT transaction
               IF transaction <= 9999999999 - cash(temp)
                COMPUTE cash(temp) = cash(temp) + transaction
               ELSE
                DISPLAY "Your account can only store" WITH NO ADVANCING
                DISPLAY " up to 9999999999 pesos"
               END-IF
               DISPLAY "Do you want another transaction?"
               DISPLAY "[1] YES"
               DISPLAY "[2] NO"
               ACCEPT repeat
              END-IF
              IF choice2 = 4
               DISPLAY "Withdraw"
               DISPLAY "Enter amount: "
               ACCEPT transaction
               IF transaction <= cash(temp)
                COMPUTE cash(temp) = cash(temp) - transaction
               ELSE
                DISPLAY "Insufficient funds"
               END-IF
               DISPLAY "Do you want another transaction?"
               DISPLAY "[1] YES"
               DISPLAY "[2] NO"
               ACCEPT repeat
              END-IF
             END-PERFORM
             MOVE counter TO temp
            ELSE
             DISPLAY "Incorrect PIN, returning to main menu..."
             MOVE counter TO temp 
            END-IF
           ELSE
            COMPUTE temp = temp + 1
           END-IF
          END-PERFORM
         END-IF
      *for debug purposes only, displays all account information for all users
         IF choice = 4
          MOVE 1 TO temp
          PERFORM UNTIL temp = counter
           DISPLAY "Name: "name(temp)
           DISPLAY "Birthday: "birthmonth(temp)"/"birthday(temp)
           DISPLAY "PIN: "pin(temp)
           DISPLAY "Funds: "cash(temp)
           COMPUTE temp = temp + 1
          END-PERFORM
         END-IF

        END-PERFORM.
        OPEN OUTPUT ATMREC.
         MOVE 1 TO temp.
         PERFORM UNTIL temp = counter
          MOVE name(temp) TO file-name
          MOVE birthmonth(temp) TO file-month
          MOVE birthday(temp) TO file-day
          MOVE pin(temp) TO file-pin
          MOVE cash(temp) TO file-cash
          WRITE file-account
          COMPUTE temp = temp + 1
         END-PERFORM.
        CLOSE ATMREC.
       STOP RUN.
