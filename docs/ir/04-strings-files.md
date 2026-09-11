# Strings, files, exec (long) / Strings, archivos, exec (largo)

## English

### String pool model
`pushs "hi"` interns the text and pushes an integer **id**. Most string ops work on ids, not on raw characters in the IR.

### Printing
- `print` — numeric top of stack  
- `prints` — string id top of stack  

### itoa / atoi
```text
push 42
itoa
prints           ; "42"

pushs "  -99zz"
atoi
print            ; -99
```
`atoi` skips spaces, accepts optional sign, stops at the first non-digit.

### strlen / strcat / strcmp
```text
pushs "ab"
pushs "c"
strcat
strlen
print            ; 3
```

### Files
```text
fopen "data.txt"     ; path is a literal in the instruction
; handle on stack — use freadln/fwrite/fclose as documented by opcode set
```
File ops are host-dependent. Prefer pure computation in portable libraries.

### exec
```text
pushs "echo hello"
exec
print            ; exit code
```
Runs a host command. Useful to invoke tools; not available or restricted in some sandboxes. Libraries in `lib/` stay pure and do **not** require exec.

---

## Español

### Modelo de pool de strings
`pushs "hi"` interna el texto y apila un **id** entero.

### Impresión
- `print` — número  
- `prints` — id de string  

### itoa / atoi
```text
push 42
itoa
prints

pushs "  -99zz"
atoi
print            ; -99
```

### strlen / strcat / strcmp
Trabajan con ids del pool.

### Archivos
`fopen` con ruta literal. Dependiente del host. Las libs en `lib/` son puras y **no** exigen archivos.

### exec
```text
pushs "echo hello"
exec
print
```
Comando del host. Las libs oficiales puras no lo necesitan.
