      * A simple cobol program for CMSC124 COBOL exercise 1
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
       PROGRAM-ID. melarpist-3le1.
      * variable declarations
       DATA DIVISION.
       WORKING-STORAGE SECTION.
       77 Name pic X(20).
       77 Age pic 9(2).
       01 Working-Hour.
          02 Time-In.
             03 In-Hour pic 9(2).
             03 In-Minute pic 9(2).
          02 Time-out.
             03 Out-Hour pic 9(2).
             03 Out-Minute pic 9(2).
       77 Normal-Pay pic 9(5)V9(2).
       77 OverTime-Pay pic 9(5)V9(2).
       77 Total-Pay pic 9(5)V9(2).
       77 hours pic 9(2).
       77 minutes pic 9(2).
       77 hourspay pic 9(5)V9(2).
       77 minutespay pic 9(5)V9(2).
       77 otpay pic 9(5)V9(2).
       77 otmpay pic 9(5)V9(2).
       77 othpay pic 9(5)V9(2).
      * main procedure of the program
       PROCEDURE DIVISION.
       PERFORM SCAN.
       PERFORM CALCULATE.
       PERFORM PRINT.
       STOP RUN.
      * function for scanning the user's input
       SCAN.
         DISPLAY "Name: " WITH NO ADVANCING.
         ACCEPT Name.
         DISPLAY "Age: " WITH NO ADVANCING.
         ACCEPT Age.
         DISPLAY "Time In".
         DISPLAY "Hours: " WITH NO ADVANCING.
         ACCEPT In-Hour.
         DISPLAY "Minutes: " WITH NO ADVANCING.
         ACCEPT In-Minute.
         DISPLAY "Time Out".
         DISPLAY "Hours: " WITH NO ADVANCING.
         ACCEPT Out-Hour.
         DISPLAY "Minutes: " WITH NO ADVANCING.
         ACCEPT Out-Minute.
      * function for computing the salary
       CALCULATE.
         COMPUTE hours=Out-Hour - In-Hour.
         COMPUTE minutes=Out-Minute - In-Minute.
         IF In-Hour<=12 AND Out-Hour>=13
            COMPUTE hours=hours - 1
         END-IF.
         IF hours<=8 AND minutes=0
            COMPUTE hourspay=hours*65
            COMPUTE minutespay=minutes*65/60.00
            COMPUTE Normal-Pay=hourspay+minutespay
            MOVE 0 TO OverTime-Pay
         ELSE
            COMPUTE Normal-Pay=8*65
            COMPUTE hours=hours - 8
            COMPUTE othpay=hours*115
            COMPUTE otmpay=minutes*115/60.00
            COMPUTE OverTime-Pay=othpay+otmpay
         END-IF.
         COMPUTE Total-Pay=Normal-Pay+OverTime-Pay.
      * function for printing the output 
       PRINT.
         DISPLAY "===============================================".
         DISPLAY "Name: "Name.
         DISPLAY "Age: "Age.
         DISPLAY "Normal Pay: "Normal-Pay" pesos".
         DISPLAY "Overtime Pay: "OverTime-Pay" pesos".
         DISPLAY "Total Pay: "Total-Pay" pesos".
         DISPLAY "===============================================".
      * END OF PROGRAM
