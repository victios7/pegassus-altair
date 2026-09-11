# Opcode reference / Referencia de opcodes

## English

### Stack ops
`push` `pop` `dup` `swap` `over` `rot`

### Arithmetic / bitwise
`add` `sub` `mul` `div` `mod` `neg` `not` `and` `or` `xor` `shl` `shr`

### Compare (push 0/1)
`eq` `ne` `lt` `le` `gt` `ge`

### Locals
`load S` `store S` — S in `0..LOCAL_MAX-1`

### Control
`jmp` `jz` `jnz` `call` `ret` `halt`/`end`

### Specialized (optimizer may emit)
`iadd_ll` `imul_ll` `isub_ll` `inc_l` `dec_l` `iadd_ln` `sub_ln` `mul_ln` `div_ln`  
`jle_ln` `jgt_ln` `jlt_ln` `jge_ln` `jz_l` `jnz_l`

### Strings / IO
`pushs` `prints` `strlen` `strcat` `strcmp` `slice`  
`input` `inputn` `print` `dump`

### Files / host
`fopen "path"` `freadln` `fwrite` `fclose` `exec`

### Convert
`itoa` `atoi`

### Arrays / assert
`newarr N` `aload` `astore` `assert "msg"`

---

## Español

### Pila
`push` `pop` `dup` `swap` `over` `rot`

### Aritmética / bits
`add` `sub` `mul` `div` `mod` `neg` `not` `and` `or` `xor` `shl` `shr`

### Comparación (deja 0/1)
`eq` `ne` `lt` `le` `gt` `ge`

### Locales
`load S` `store S` — S en `0..LOCAL_MAX-1`

### Control
`jmp` `jz` `jnz` `call` `ret` `halt`/`end`

### Especializados (el optimizador puede emitirlos)
`iadd_ll` `imul_ll` `isub_ll` `inc_l` `dec_l` `iadd_ln` `sub_ln` `mul_ln` `div_ln`  
`jle_ln` `jgt_ln` `jlt_ln` `jge_ln` `jz_l` `jnz_l`

### Strings / IO
`pushs` `prints` `strlen` `strcat` `strcmp` `slice`  
`input` `inputn` `print` `dump`

### Archivos / host
`fopen "path"` `freadln` `fwrite` `fclose` `exec`

### Conversión
`itoa` `atoi`

### Arrays / assert
`newarr N` `aload` `astore` `assert "msg"`
