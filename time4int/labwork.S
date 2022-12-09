  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.
#Dessa gör att time2string och delay kan acessas från andra filer
  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

	.data
	.align 2
timstr:	.ascii ""
	.text
  #
  # Please add your own code below this line
  #

.global enable_interrupt
enable_interrupt:
	ei
	jr $ra

hexasc: 
	andi $a0, $a0, 0xF
	addi $v0, $a0, 48	
	bgt $v0, 57, boks
	nop
	
	jr $ra
	nop
boks:
	addi $v0, $v0, 7
	jr $ra
	nop

.global time2string 
time2string:
	PUSH $s1
	PUSH $s0
	add $s0, $a0, $0 #Flyttar för sökerhets skull a0 och a1 registerna till s0 och s1
	add $s1, $a1, $0 #ifall hexasc skulle modifiera dessa
	
	andi $a0, $s1, 0xF
	PUSH $ra
	jal hexasc
	nop
	
	POP $ra
	PUSH $v0
	
	andi $a0, $s1, 0xF0
	srl $a0, $a0, 4
	PUSH $ra
	jal hexasc
	nop
	
	POP $ra
	PUSH $v0
	
	andi $a0, $s1, 0xF00
	srl $a0, $a0, 8
	PUSH $ra
	jal hexasc
	nop
	
	POP $ra
	PUSH $v0
	
	andi $a0, $s1, 0xF000
	srl $a0, $a0, 12
	PUSH $ra
	jal hexasc
	nop
	
	POP $ra
	
	add $a0, $s0, $0 
	sb $v0, 0($a0)
	
	POP $v0
	
	sb $v0, 1($a0)
	
	addi $t0, $0, 0x3A
	sb $t0, 2($a0)
	
	POP $v0
	
	sb $v0, 3($a0)
	
	POP $v0
	
	sb $v0, 4($a0)
	
	addi $t0, $0, 0x00
	sb $t0, 5($a0)
	
	POP $s0
	POP $s1

	jr $ra
	nop

addi $a0, $0, 1000

.global delay
delay:
	beq $a0, 0, exit
	nop
	
	addi $a2, $0, 0
	sub $a0, $a0, 1
	
	for: 
	addi $a2, $a2, 1
	
	ble $a2, 6700, for
	nop
	
	bgt $a0, 0, delay
	nop
	
exit:
	jr $ra
	nop

