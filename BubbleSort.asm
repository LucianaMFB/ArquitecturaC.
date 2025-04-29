.data
array:      .word 8, 7, 6, 5, 4, 3, 2, 1   # Array a ordenar
space:      .asciiz " "                    # Espacio para separar números
newline:    .asciiz "\n"                   # Nueva línea
msg_before: .asciiz "Array antes de ordenar: "
msg_after:  .asciiz "Array después de ordenar: "

.text
.globl main

main:
    # Imprimir mensaje inicial
    la $a0, msg_before
    li $v0, 4
    syscall
    
    # Imprimir array antes de ordenar
    la $a0, array      # Dirección del array
    la $t0, array      # Puntero al inicio
    addi $t1, $t0, 28  # Puntero al final (8 elementos * 4 bytes - 4)
    jal print_array
    
    # Imprimir nueva línea
    la $a0, newline
    li $v0, 4
    syscall
    
    # Llamar a bubble_sort_ptrs
    la $a0, array      # Puntero al inicio
    addi $a1, $a0, 28  # Puntero al final (8 elementos * 4 bytes - 4)
    jal bubble_sort_ptrs
    
    # Imprimir mensaje final
    la $a0, msg_after
    li $v0, 4
    syscall
    
    # Imprimir array después de ordenar
    la $a0, array
    la $t0, array      # Puntero al inicio
    addi $t1, $t0, 28  # Puntero al final
    jal print_array
    
    # Salir del programa
    li $v0, 10
    syscall

bubble_sort_ptrs:
    # Guardar registros en la pila
    addi $sp, $sp, -16
    sw $ra, 0($sp)
    sw $s0, 4($sp)
    sw $s1, 8($sp)
    sw $s2, 12($sp)
    
    # Inicializar registros
    move $s0, $a0            # $s0 = puntero al inicio
    move $s1, $a1            # $s1 = puntero al final
    
outer_loop:
    li $s2, 0                # $s2 = swapped (flag para saber si hubo intercambios)
    move $t0, $s0            # $t0 = puntero actual (inicia en el inicio)
    
inner_loop:
    bge $t0, $s1, end_inner  # Si puntero_actual >= puntero_final, salir del bucle interno
    
    lw $t1, 0($t0)           # $t1 = valor actual
    lw $t2, 4($t0)           # $t2 = siguiente valor
    
    ble $t1, $t2, no_swap    # Si valor_actual <= siguiente_valor, no intercambiar
    
    # Intercambiar elementos
    sw $t2, 0($t0)           # array[i] = array[i+1]
    sw $t1, 4($t0)           # array[i+1] = valor_actual
    li $s2, 1                # swapped = true
    
no_swap:
    addi $t0, $t0, 4         # Avanzar al siguiente elemento
    j inner_loop
    
end_inner:
    beqz $s2, end_sort       # Si no hubo intercambios, terminar
    addi $s1, $s1, -4        # Decrementar puntero final (el elemento más grande ya está en su lugar)
    j outer_loop
    
end_sort:
    # Restaurar registros de la pila
    lw $ra, 0($sp)
    lw $s0, 4($sp)
    lw $s1, 8($sp)
    lw $s2, 12($sp)
    addi $sp, $sp, 16
    
    jr $ra                   # Retornar

print_array:
    move $t0, $a0            # Puntero al inicio
    
print_loop:
    lw $a0, 0($t0)           # Cargar valor actual
    li $v0, 1                # Imprimir entero
    syscall
    
    la $a0, space            # Imprimir espacio
    li $v0, 4
    syscall
    
    addi $t0, $t0, 4         # Avanzar al siguiente elemento
    
    # Si puntero actual > puntero final, terminar
    addi $t2, $t1, 4         # $t2 = puntero final + 4 (para incluir el último elemento)
    bge $t0, $t2, end_print
    
    j print_loop
    
end_print:
    jr $ra
