.data
Array: .word 8, 7, 6, 5, 4, 3, 2, 1		# Crear array de enteros
size: .word 8						# Tamaño del array
.text
.globl main
main:
    la $s1, Array        	# Cargar la dirección base del array en $t0
    lw $s2, size         	# Cargar el tamaño del array en $t1
    lw $t0,0($s1) 		# valorMaximo = A[0]
    addi $t5,$zero,0		# posicionValorMaximo = 0 
    addi $t1,$zero,0 		# inicializa i = 0
    
    sort_loop:
    	move $a0, $s1        # cargar base del array en $a0
    	lw $t0, 0($s1)       # valorMaximo = primer elemento
    	move $t5, $zero      # posicionValorMaximo = 0
    	jal buscar_maximo
    	mul $t6, $s2, 4		# tamaño del array * 4 en $t6
    	sub $t6, $t6, 4		# $t6 - 4 en $t6
    	add $t6, $t6, $s1	# $t6 = Array + $t6
    	lw $t7, 0($t6)		# $t7 = contenido de Array + $t6
    	sw $t0, 0($t6)		# contenido de Array + $t6 = valorMaximo
    	mul $t8, $t5, 4		# $t8 = posicionValorMaximo * 4
    	add $t8, $t8, $s1	# $t8 = $t8 + Array
    	sw $t7, 0($t8)		# Almacena $t7 en Array + $t8
    	addi $s2, $s2, -1	# size = size - 1
    	li $t9, 1		# $t9 = 1
    	beq $s2, $t9, fin	# if( size == 1)
    	j sort_loop		#continue
    fin:
    	li $v0, 10
    	syscall
    
    
    #inicio de la funcion:
    buscar_maximo:
    	move $t1, $zero        # Inicializar el índice i a 0 (t1)
    	move $t2, $a0          # $t2 = Dirección del arreglo (Array)
    loop: 
    	add $t1,$t1,1 		# increment index i by 1
    	beq $t1,$s2,fin_loop 	# beq(Branch if Equal) | if(i($t1) == size($s2))
    	
    	add $t2,$t1,$t1 	# suma i + i y guarda en $t2
    	add $t2,$t2,$t2 	# suma $t2 + $t2 y guarda en $t2
    	add $t2,$t2,$s1 	# $t2 = Array + $t2
    	lw $t3,0($t2) 		# guarda el elemento que se encuentra en Array + $t2 en $t3
    	
    	slt $t4,$t0,$t3 	# slt(Set Less Than) | if(valorMaximo < Array[i])
    	beq $t4,$zero,loop 	# beq(Branch if Equal) | si no cumple continue
    	addi $t0,$t3,0 		# si cumple => valorMaximo = Array[i]
    	add $t5,$t1,$t5		# posicionValorMaximo = i + posicionValorMaximo
    	j loop 			# continue
    fin_loop:
    	jr $ra                 # Volver a la función que llamó
