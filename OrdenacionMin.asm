.data
Array: .word 2, 3, -3, 5, 0, 5, 7, 8    # Crear array de enteros
size: .word 8                          # Tamaño del array
.text
.globl main
main:
    la $s1, Array    # Cargar la dirección base del array en $s1
    lw $s2, size     # Cargar el tamaño del array en $s2
    addi $s3, $zero, 0  # índice del primer elemento no ordenado

sort_loop:
    move $a0, $s1    # cargar base del array en $a0
    move $a1, $s3    # pasar el índice de inicio para buscar
    lw $t0, 0($s1)   # valorMinimo = primer elemento 
    move $t5, $s3    # posicionValorMinimo = s3 (índice inicial)
    jal buscar_minimo
    
    # Intercambiar el valor mínimo con el primer elemento no ordenado
    mul $t6, $s3, 4         # índice inicio * 4 en $t6
    add $t6, $t6, $s1       # $t6 = Array + $t6 (dirección del primer elemento no ordenado)
    lw $t7, 0($t6)          # $t7 = contenido de Array[$s3]
    sw $t0, 0($t6)          # contenido de Array[$s3] = valorMinimo
    mul $t8, $t5, 4         # $t8 = posicionValorMinimo * 4
    add $t8, $t8, $s1       # $t8 = $t8 + Array
    sw $t7, 0($t8)          # Almacena $t7 en Array[$t5]
    
    addi $s3, $s3, 1        # incrementa el índice de inicio
    sub $t9, $s2, $s3       # compara size - índice inicio
    beq $t9, $zero, fin     # if(size - índice inicio == 0) terminar
    j sort_loop            # continuar
fin:
    li $v0, 10
    syscall

#inicio de la función:
buscar_minimo:
    move $t1, $a1    # Inicializar el índice i al índice de inicio (pasado como argumento)
    move $t2, $a0    # $t2 = Dirección del arreglo (Array)
    
    # Inicializar valorMinimo con el primer elemento no ordenado
    mul $t4, $a1, 4  # t4 = índice de inicio * 4
    add $t4, $t4, $t2  # t4 = Array + t4
    lw $t0, 0($t4)   # t0 = Array[índice de inicio]
    move $t5, $a1    # posicionValorMinimo = índice de inicio
    
loop:
    addi $t1, $t1, 1    # incrementar índice i en 1
    beq $t1, $s2, fin_loop  # if(i == size) terminar
    
    mul $t3, $t1, 4     # t3 = i * 4
    add $t3, $t3, $s1   # t3 = Array + t3
    lw $t4, 0($t3)      # t4 = Array[i]
    
    slt $t6, $t4, $t0   # slt(Set Less Than) | if(Array[i] < valorMinimo)
    beq $t6, $zero, loop  # si no cumple, continuar
    move $t0, $t4       # si cumple: valorMinimo = Array[i]
    move $t5, $t1       # posicionValorMinimo = i
    j loop              # continuar
    
fin_loop:
    jr $ra              # Volver a la función que llamó
