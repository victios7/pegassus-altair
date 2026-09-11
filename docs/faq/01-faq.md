# FAQ (long) / FAQ (larga)

## English

### Why does my included library run by itself?
Because `include` pastes code into the program. Without `jmp main` first, execution starts at the first instruction of the lib.

### Why does O2/bare change results?
It should not. If it does, that is a bug. Run `testsuite`. 1.9.12 rolls back bad passes; please report remaining mismatches with a minimal `.ir`.

### How big is the stack?
131072 entries, **1 MiB dedicated**.

### How many locals?
131072 slots (`0..131071`), **1 MiB dedicated**.

### Can I use slot 0 in a library?
You can, but you should not: applications use low slots. Prefer 240+.

### Does `exec` work offline?
It runs host commands; sandboxed or locked-down environments may block it.

### Is pegbin equal to the VM?
No. Documented subset only.

### How do I ship a language on top of Pegassus?
1. Write a frontend → emit `.ir`  
2. Ship `pegassus` binary  
3. Optionally ship `lib/*.ir`  
4. Document your ABI extensions if any

---

## Español

### ¿Por qué mi lib se ejecuta sola?
`include` pega código en el programa. Sin `jmp main` al inicio, se ejecuta la lib.

### ¿Por qué O2/bare cambia resultados?
No debería. Si pasa, es bug. Ejecuta `testsuite`. 1.9.12 revierte pasadas malas; reporta con un `.ir` mínimo.

### ¿De qué tamaño es la pila?
131072 entradas, **1 MiB dedicado**.

### ¿Cuántos locales?
131072 slots (`0..131071`), **1 MiB dedicado**.

### ¿Puedo usar el slot 0 en una lib?
Puedes, pero no debes: las apps usan los bajos. Prefiere 240+.

### ¿`exec` funciona offline?
Ejecuta comandos del host; entornos restringidos pueden bloquearlo.

### ¿pegbin es igual que la VM?
No. Solo un subconjunto documentado.

### ¿Cómo publico un lenguaje encima de Pegassus?
1. Frontend → emite `.ir`  
2. Distribuye el binario `pegassus`  
3. Opcional: `lib/*.ir`  
4. Documenta extensiones de ABI
