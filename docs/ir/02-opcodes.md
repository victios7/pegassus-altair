# Opcodes (detailed) / Opcodes (detallado)

## English

### Stack effect notation
- `(a b -- c)` means: pop b, pop a, push c  
- `(x --)` means: pop x  
- `( -- x)` means: push x  

### Core arithmetic
| Op | Effect | Notes |
|----|--------|-------|
| add | (a b -- a+b) | |
| sub | (a b -- a-b) | a then b on stack: careful order |
| mul | (a b -- a*b) | |
| div | (a b -- a/b) | runtime error on /0 |
| mod | (a b -- a%b) | |
| neg | (a -- -a) | |

Example subtraction order:

```text
push 10
push 3
sub
print      ; 7   because 10-3
```

### Locals
| Op | Effect |
|----|--------|
| load S | ( -- locals[S] ) |
| store S | ( v -- ) locals[S]=v |

S must satisfy `0 <= S < LOCAL_MAX` (131072).

### Control
| Op | Effect |
|----|--------|
| jmp L | IP = L |
| jz L | (c --) jump if c==0 |
| jnz L | (c --) jump if c!=0 |
| call L | push return IP; IP=L |
| ret | pop return IP |
| halt/end | stop |

### Strings
| Op | Effect |
|----|--------|
| pushs "t" | ( -- id ) |
| prints | ( id -- ) |
| strlen | ( id -- n ) |
| strcat | ( id1 id2 -- id3 ) |
| itoa | ( n -- id ) |
| atoi | ( id -- n ) |

### Host
| Op | Effect |
|----|--------|
| exec | ( id -- exitcode ) runs shell command string |

Optimizer may **replace** sequences with specialized ops (`inc_l`, `jle_ln`, …). Source programs usually write the portable form.

---

## Español

### Notación de efecto de pila
- `(a b -- c)` : pop b, pop a, push c  
- `(x --)` : pop x  
- `( -- x)` : push x  

### Aritmética básica
| Op | Efecto | Notas |
|----|--------|-------|
| add | (a b -- a+b) | |
| sub | (a b -- a-b) | cuidado con el orden |
| mul | (a b -- a*b) | |
| div | (a b -- a/b) | error si /0 |
| mod | (a b -- a%b) | |
| neg | (a -- -a) | |

```text
push 10
push 3
sub
print      ; 7   porque 10-3
```

### Locales
| Op | Efecto |
|----|--------|
| load S | ( -- locals[S] ) |
| store S | ( v -- ) locals[S]=v |

`0 <= S < LOCAL_MAX` (131072).

### Control
| Op | Efecto |
|----|--------|
| jmp L | IP = L |
| jz L | (c --) salta si c==0 |
| jnz L | (c --) salta si c!=0 |
| call L | apila IP retorno; IP=L |
| ret | saca IP retorno |
| halt/end | termina |

### Strings
| Op | Efecto |
|----|--------|
| pushs "t" | ( -- id ) |
| prints | ( id -- ) |
| strlen | ( id -- n ) |
| strcat | ( id1 id2 -- id3 ) |
| itoa | ( n -- id ) |
| atoi | ( id -- n ) |

### Host
| Op | Efecto |
|----|--------|
| exec | ( id -- código ) ejecuta comando del shell |

El optimizador puede **sustituir** secuencias por ops especializadas (`inc_l`, `jle_ln`, …). En fuente suele escribirse la forma portable.
