%include "io.inc"

section .data
    %include "input.inc"
    mesaj: db "Baza incorecta",0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp

    mov ebx, dword [baza]
    mov ecx, dword [numar]
    cmp ebx, 16
    jg eroare
    cmp ebx, 2
    jl eroare
    cmp ecx, ebx
    jl afi_baza   
    mov eax, dword [numar]
    xor ecx, ecx

impartire:
    mov edx, 0
    div ebx
    push edx
    inc ecx
    cmp eax, ebx
    jge impartire
    push eax
    inc ecx
  
afisare:
    pop eax
    cmp eax, 0
    je print0
    cmp eax, 1
    je print1
    cmp eax, 2
    je print2
    cmp eax, 3
    je print3
    cmp eax, 4
    je print4
    cmp eax, 5
    je print5
    cmp eax, 6
    je print6
    cmp eax, 7
    je print7
    cmp eax, 8
    je print8
    cmp eax, 9
    je print9
    cmp eax, 10
    je print10
    cmp eax, 11
    je print11
    cmp eax, 12
    je print12
    cmp eax, 13
    je print13
    cmp eax, 14
    je print14
    cmp eax, 15
    je print15

intoarcere:       
    dec ecx
    jnz afisare
    jmp sfarsit
    
print0:
    PRINT_CHAR '0'
    jmp intoarcere
    
print1:
    PRINT_CHAR '1'
    jmp intoarcere
   
print2:
    PRINT_CHAR '2'
    jmp intoarcere
    
print3:
    PRINT_CHAR '3'
    jmp intoarcere
print4:
    PRINT_CHAR '4'
    jmp intoarcere
    
print5:
    PRINT_CHAR '5'
    jmp intoarcere
   
print6:
    PRINT_CHAR '6'
    jmp intoarcere
    
print7:
    PRINT_CHAR '7'
    jmp intoarcere
    
print8:
    PRINT_CHAR '8'
    jmp intoarcere
    
print9:
    PRINT_CHAR '9'
    jmp intoarcere
   
print10:
    PRINT_CHAR 'a'
    jmp intoarcere
    
print11:
    PRINT_CHAR 'b'
    jmp intoarcere
print12:
    PRINT_CHAR 'c'
    jmp intoarcere
    
print13:
    PRINT_CHAR 'd'
    jmp intoarcere
   
print14:
    PRINT_CHAR 'e'
    jmp intoarcere
    
print15:
    PRINT_CHAR 'f'
    jmp intoarcere

afi_baza:
    mov ecx, 1
    push ebx
    jmp afisare

eroare:
    lea eax, [mesaj]        
    push eax                   
    call puts
    pop eax        

sfarsit:
    leave  
    ret

    