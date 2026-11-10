org 100h

.DATA
    MSG_NUM1    DB 'Enter first single-digit number (0-9): $'
    MSG_NUM2    DB 0DH, 0AH, 'Enter second single-digit number (0-9): $'

    MENU_MSG    DB 0DH, 0AH, 0DH, 0AH, '========== MENU ==========', 0DH, 0AH
                DB 'Enter 1 for adding 2 values', 0DH, 0AH
                DB 'Enter 2 for Subtracting 2 values', 0DH, 0AH
                DB 'Enter 3 for dividing 2 values', 0DH, 0AH
                DB 'Enter 4 for Multiplying 2 values', 0DH, 0AH
                DB 'Enter your choice (1-4): $'

    MSG_ADD     DB 0DH, 0AH, 'Result of Addition: $'
    MSG_SUB     DB 0DH, 0AH, 'Result of Subtraction: $'
    MSG_DIV     DB 0DH, 0AH, 'Result of Division (Quotient): $'
    MSG_MUL     DB 0DH, 0AH, 'Result of Multiplication: $'
    MSG_INVALID DB 0DH, 0AH, 'Invalid Choice! Program Terminated.$'

    NUM1        DB ?
    NUM2        DB ?

.CODE
MAIN PROC
    ; Initialize Data Segment
    MOV AX, @DATA
    MOV DS, AX

    ; Read First Number
    LEA DX, MSG_NUM1
    MOV AH, 09H
    INT 21H

    MOV AH, 01H            ; Read character into AL
    INT 21H
    SUB AL, '0'            ; Convert ASCII character to numeric value
    MOV NUM1, AL

    ; Read Second Number
    LEA DX, MSG_NUM2
    MOV AH, 09H
    INT 21H

    MOV AH, 01H            ; Read character into AL
    INT 21H
    SUB AL, '0'            ; Convert ASCII character to numeric value
    MOV NUM2, AL

    ; Display Menu
    LEA DX, MENU_MSG
    MOV AH, 09H
    INT 21H

    ; Read User Choice
    MOV AH, 01H
    INT 21H                ; AL holds chosen ASCII character

    CMP AL, '1'
    JE DO_ADDITION

    CMP AL, '2'
    JE DO_SUBTRACTION

    CMP AL, '3'
    JE DO_DIVISION

    CMP AL, '4'
    JE DO_MULTIPLICATION

    ; Default: Invalid choice
    LEA DX, MSG_INVALID
    MOV AH, 09H
    INT 21H
    JMP EXIT_PROGRAM


DO_ADDITION:
    LEA DX, MSG_ADD
    MOV AH, 09H
    INT 21H

    MOV AL, NUM1
    ADD AL, NUM2           ; Perform Addition
    MOV AH, 00H
    AAA                    ; ASCII Adjust after Addition for multi-digit results

    MOV BX, AX             ; Save result (AH = tens digit, AL = ones digit)

    ; Print Tens Digit (if non-zero)
    CMP BH, 0
    JE PRINT_ADD_ONES
    MOV DL, BH
    ADD DL, '0'
    MOV AH, 02H
    INT 21H

PRINT_ADD_ONES:
    MOV DL, BL
    ADD DL, '0'
    MOV AH, 02H
    INT 21H
    JMP EXIT_PROGRAM


DO_SUBTRACTION:
    LEA DX, MSG_SUB
    MOV AH, 09H
    INT 21H

    MOV AL, NUM1
    CMP AL, NUM2           ; Compare NUM1 and NUM2
    JGE POSITIVE_RESULT    ; If NUM1 >= NUM2, branch to direct subtraction

    ; Result is negative (NUM1 < NUM2)
    MOV DL, '-'            ; Display '-' sign
    MOV AH, 02H
    INT 21H

    MOV AL, NUM2           ; Compute (NUM2 - NUM1) for magnitude
    SUB AL, NUM1
    JMP PRINT_SUB_RESULT

POSITIVE_RESULT:
    SUB AL, NUM2           ; Compute (NUM1 - NUM2)

PRINT_SUB_RESULT:
    ADD AL, '0'            ; Convert result to ASCII digit
    MOV DL, AL
    MOV AH, 02H
    INT 21H
    JMP EXIT_PROGRAM


DO_DIVISION:
    LEA DX, MSG_DIV
    MOV AH, 09H
    INT 21H

    MOV AH, 00H            ; Clear AH before division
    MOV AL, NUM1
    DIV NUM2               ; Divide AX by NUM2 (Quotient in AL, Remainder in AH)
    ADD AL, '0'            ; Convert quotient to ASCII character

    MOV DL, AL
    MOV AH, 02H
    INT 21H
    JMP EXIT_PROGRAM

DO_MULTIPLICATION:
    LEA DX, MSG_MUL
    MOV AH, 09H
    INT 21H

    MOV AL, NUM1
    MUL NUM2               ; Result in AX (AH:AL)
    AAM                    ; AH = tens digit, AL = ones digit

    MOV BX, AX             ; Save result

    CMP BH, 0
    JE PRINT_MUL_ONES
    MOV DL, BH
    ADD DL, '0'
    MOV AH, 02H
    INT 21H

PRINT_MUL_ONES:
    MOV DL, BL
    ADD DL, '0'
    MOV AH, 02H
    INT 21H
    JMP EXIT_PROGRAM


EXIT_PROGRAM:
    MOV AH, 4CH
    INT 21H

MAIN ENDP
END MAIN