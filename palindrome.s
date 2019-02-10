# Author: Kenneth M Murry
# CptS 260 HW6
# Palindrome Program

    .option pic0
    
    .data
    .align 2

    fileName: 
        .asciiz "/usr/share/dict/words" # this is the path to get all the words to check 
    
    buffer: 
        .space 64 # this is going to be used to hold the strings
    
    fileMode: 
        .asciiz "r"

    messageFormat:
        .asciz  "%s"
    
    promptMessage:
        .asciz "Murry's Palindrome MIPS Program\n"
        .align 2

    fileError:
        .asciz "File Did Not Open!\n"
        .align 2

        .text
        .align 2

    #This function will display my custom starting logo
    .global palindrome_prompt
palindrome_prompt:
    la $a0, promptMessage # storing address of promptMessage in $a0

    addiu $sp, $sp, -4 # create space on the stack for $sp
    sw $ra, ($sp)      # save $sp on the stack

    move $a1, $a0
    la $a0, messageFormat
    jal printf

    lw $ra, ($sp)
    addiu $sp, $sp, +4

    jr $ra

    #This function will be used to prompt the user that file
    #did not open
    .global palindrome_error
palindrome_error:
    la $a0, fileError # storing address of test in $a0

    addiu $sp, $sp, -4 # create space on the stack for $sp
    sw $ra, ($sp)      # save $sp on the stack

    move $a1, $a0
    la $a0, messageFormat
    jal printf

    lw $ra, ($sp)
    addiu $sp, $sp, +4

    jal error_exit 
    
    #This function will be used to exit program if file could
    #Not be openned
    .global error_exit
error_exit:
    li      $a0,0
    jal     exit

    # This function will print the palindrome
    .global palindrome_print
palindrome_print:
  
    addiu $sp, $sp, -4  
    sw    $ra, ($sp)    

    move $a1, $a0
    la   $a0, messageFormat
    jal  printf
    
    lw    $ra, ($sp)    
    addiu $sp, $sp, +4  

    jr    $ra


    .global main    
 main:
    #jal palindrome_prompt # Prints my custom logo

    la $a0, fileName # file path $a0
    la $a1, fileMode # file mode used to read file
    jal fopen  
   
    addiu $t0, $0, 0
    beq $t0, $v0, palindrome_error # making sure file openned

    move $s1, $v0 # saving file pointer from fopen into $s1

    addiu $s0, $0, 0 # $s0 = 0
    addiu $s3, $0, 97 # ascii value for 'a'
    addiu $s4, $0, 4  # If length is equal or less than skip

while:
     
    jal palindrome_get_string

    move $a0, $v0 # loading string from fgets into $a0
    beq $s0, $v0, whileEnd #If $v0 == 0 EOF reached

    la $t1, buffer  # Base array pointer
    la $t2, buffer  # End of array pointer starting at beginning

    jal strlen          # getting String length 
    move $s2, $v0       # loading current string length to $s2
    blt $s2, $s4, not_palindrome #If length is less than 4 branch
    addi $s2, $s2, -2   # need to add -2 to move index to just pass \n
    add $t2, $t1, $s2   # moving pointer to end of array
    jal palindrome_check 

    j while


palindrome_check:
    lb $t3, ($t1) # get character at lower pointer
    blt $t3, $s3, not_palindrome # If first element is a Capital letter skip
    bge $t1, $t2, is_palindrome

    lb $t3, ($t1) # get character at lower pointer
    
    lb $t4, ($t2) # get character at end pointer

    bne $t3, $t4, not_palindrome

    addi $t1, $t1, 1 # increment lower pointer
    addi $t2, $t2, -1 # decrement end pointer

    j palindrome_check

not_palindrome:
    j while

is_palindrome:
    jal palindrome_print
    j while

palindrome_get_string:

    addiu $sp, $sp, -4
    sw    $ra, ($sp)

    la   $a0, buffer # load str to read into
    la   $a1, 64 # max number of bytes to be read
    move $a2, $s1 # Load pointer to stream
    jal  fgets  

    lw $ra, ($sp)
    addiu $sp, $sp, +4

    jr $ra

whileEnd:
    move $a0, $s1 # move file pointer($s1) to $a0
    jal fclose  #freeing the file pointer
    li      $a0, 0
    jal     exit
