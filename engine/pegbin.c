#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct { uint8_t*d; size_t n,c; } B;
static void binit(B*b){b->d=0;b->n=0;b->c=0;}
static void bgrow(B*b,size_t k){if(b->n+k>b->c){b->c=(b->c?b->c*2:256)+k;b->d=realloc(b->d,b->c);}}
static void b1(B*b,uint8_t v){bgrow(b,1);b->d[b->n++]=v;}
static void bn(B*b,const void*p,size_t n){bgrow(b,n);memcpy(b->d+b->n,p,n);b->n+=n;}
static void bu16(B*b,uint16_t v){b1(b,v);b1(b,v>>8);}
static void bu32(B*b,uint32_t v){bu16(b,v);bu16(b,v>>16);}
static void bu64(B*b,uint64_t v){bu32(b,(uint32_t)v);bu32(b,(uint32_t)(v>>32));}

static void emit_push(B*b,int64_t v){b1(b,0x48);b1(b,0xB8);bu64(b,(uint64_t)v);b1(b,0x50);}
static void emit_pop_rax(B*b){b1(b,0x58);}
static void emit_pop_rbx(B*b){b1(b,0x5B);}
static void emit_push_rax(B*b){b1(b,0x50);}
static void emit_add(B*b){emit_pop_rax(b);emit_pop_rbx(b);b1(b,0x48);b1(b,0x01);b1(b,0xD8);emit_push_rax(b);}
static void emit_sub(B*b){emit_pop_rax(b);emit_pop_rbx(b);b1(b,0x48);b1(b,0x29);b1(b,0xC3);b1(b,0x48);b1(b,0x89);b1(b,0xD8);emit_push_rax(b);}
static void emit_mul(B*b){emit_pop_rax(b);emit_pop_rbx(b);b1(b,0x48);b1(b,0x0F);b1(b,0xAF);b1(b,0xC3);emit_push_rax(b);}
static void emit_neg(B*b){emit_pop_rax(b);b1(b,0x48);b1(b,0xF7);b1(b,0xD8);emit_push_rax(b);}
static void emit_dup(B*b){b1(b,0x58);b1(b,0x50);b1(b,0x50);}
static void emit_exit_linux(B*b,int code){
  emit_pop_rax(b);
  b1(b,0x48);b1(b,0x89);b1(b,0xC7);
  b1(b,0x48);b1(b,0xC7);b1(b,0xC0);bu32(b,60);
  b1(b,0x0F);b1(b,0x05);
}
static void emit_print_linux(B*b){
  /* Pop number, print decimal using a small fixed routine into [r12+1900] */
  emit_pop_rax(b);
  b1(b,0x48);b1(b,0x89);b1(b,0xC3); /* mov rbx,rax  value */
  /* r13 = buffer end at r12+2000 */
  b1(b,0x4D);b1(b,0x8D);b1(b,0xAC);b1(b,0x24);bu32(b,2000); /* lea r13,[r12+2000] */
  b1(b,0x41);b1(b,0xC6);b1(b,0x45);b1(b,0x00);b1(b,10); /* mov byte [r13],10 newline */
  b1(b,0x49);b1(b,0xFF);b1(b,0xCD); /* dec r13 */
  b1(b,0x48);b1(b,0x31);b1(b,0xC9); /* xor rcx,rcx len */
  b1(b,0x48);b1(b,0xFF);b1(b,0xC1); /* inc rcx for newline */
  /* sign flag r14 */
  b1(b,0x48);b1(b,0xC7);b1(b,0xC6);bu32(b,0); /* mov rsi,0 as sign */
  b1(b,0x48);b1(b,0x85);b1(b,0xDB);
  b1(b,0x0F);b1(b,0x89);bu32(b,7); /* jns skip */
  b1(b,0x48);b1(b,0xF7);b1(b,0xDB); /* neg rbx */
  b1(b,0x48);b1(b,0xC7);b1(b,0xC6);bu32(b,1); /* sign=1 */
  /* if zero */
  b1(b,0x48);b1(b,0x85);b1(b,0xDB);
  b1(b,0x0F);b1(b,0x85);bu32(b,8);
  b1(b,0x41);b1(b,0xC6);b1(b,0x45);b1(b,0x00);b1(b,0x30);
  b1(b,0x49);b1(b,0xFF);b1(b,0xCD);
  b1(b,0x48);b1(b,0xFF);b1(b,0xC1);
  b1(b,0xEB);b1(b,28);
  /* loop */
  b1(b,0x48);b1(b,0x89);b1(b,0xD8);
  b1(b,0x48);b1(b,0x31);b1(b,0xD2);
  b1(b,0x49);b1(b,0xC7);b1(b,0xC0);bu32(b,10); /* mov r8,10 */
  b1(b,0x49);b1(b,0xF7);b1(b,0xF0); /* div r8 */
  b1(b,0x48);b1(b,0x89);b1(b,0xC3); /* quot rbx */
  b1(b,0x48);b1(b,0x83);b1(b,0xC2);b1(b,0x30);
  b1(b,0x41);b1(b,0x88);b1(b,0x55);b1(b,0x00); /* mov [r13],dl */
  b1(b,0x49);b1(b,0xFF);b1(b,0xCD);
  b1(b,0x48);b1(b,0xFF);b1(b,0xC1);
  b1(b,0x48);b1(b,0x85);b1(b,0xDB);
  b1(b,0x75);b1(b,(uint8_t)(-30)); /* jnz loop */
  /* minus */
  b1(b,0x48);b1(b,0x85);b1(b,0xF6);
  b1(b,0x0F);b1(b,0x84);bu32(b,8);
  b1(b,0x41);b1(b,0xC6);b1(b,0x45);b1(b,0x00);b1(b,0x2D);
  b1(b,0x49);b1(b,0xFF);b1(b,0xCD);
  b1(b,0x48);b1(b,0xFF);b1(b,0xC1);
  /* write: rax=1 rdi=1 rsi=r13+1 rdx=rcx */
  b1(b,0x49);b1(b,0x8D);b1(b,0x75);b1(b,0x01); /* lea rsi,[r13+1] */
  b1(b,0x48);b1(b,0x89);b1(b,0xCA); /* mov rdx,rcx */
  b1(b,0x48);b1(b,0xC7);b1(b,0xC0);bu32(b,1);
  b1(b,0x48);b1(b,0xC7);b1(b,0xC7);bu32(b,1);
  b1(b,0x0F);b1(b,0x05);
}

/* locals in [rsp+8*i] after frame: we keep a parallel area via r12 base */
static void emit_prologue(B*b){
  b1(b,0x55); /* push rbp */
  b1(b,0x48);b1(b,0x89);b1(b,0xE5);
  b1(b,0x48);b1(b,0x81);b1(b,0xEC);bu32(b,2048); /* sub rsp,2048 locals */
  b1(b,0x49);b1(b,0x89);b1(b,0xE4); /* mov r12,rsp */
}

static void emit_epilogue_linux(B*b){
  b1(b,0x48);b1(b,0x89);b1(b,0xEC); /* mov rsp,rbp */
  b1(b,0x5D); /* pop rbp */
  b1(b,0x48);b1(b,0xC7);b1(b,0xC0);bu32(b,60);
  b1(b,0x48);b1(b,0x31);b1(b,0xFF);
  b1(b,0x0F);b1(b,0x05);
}

static void emit_store(B*b,int slot){
  emit_pop_rax(b);
  /* mov [r12+8*slot], rax */
  b1(b,0x49);b1(b,0x89);b1(b,0x84);b1(b,0x24);bu32(b,(uint32_t)(slot*8));
}
static void emit_load(B*b,int slot){
  b1(b,0x49);b1(b,0x8B);b1(b,0x84);b1(b,0x24);bu32(b,(uint32_t)(slot*8));
  emit_push_rax(b);
}

static void emit_cmp_set(B*b,int setcc){
  emit_pop_rax(b);emit_pop_rbx(b);
  b1(b,0x48);b1(b,0x39);b1(b,0xC3); /* cmp rbx,rax */
  b1(b,0x0F);b1(b,setcc);b1(b,0xC0); /* setcc al */
  b1(b,0x48);b1(b,0x0F);b1(b,0xB6);b1(b,0xC0);
  emit_push_rax(b);
}

static int*load_code(const char*path,int*n){
  FILE*f=fopen(path,"r");if(!f)return 0;
  int cap=256,cnt=0;int*a=malloc(cap*sizeof(int));
  char line[128];
  while(fgets(line,sizeof line,f)){
    char*e=0;long v=strtol(line,&e,10);
    if(e==line)continue;
    if(cnt>=cap){cap*=2;a=realloc(a,cap*sizeof(int));}
    a[cnt++]=(int)v;
  }
  fclose(f);*n=cnt;return a;
}

typedef struct { int bc_off; int mc_off; } Map;
typedef struct { int patch_at; int target_bc; int kind; } Patch; /* kind 0=jmp 1=jnz */

static void gen_mc(B*b,int*C,int N,int os){
  Map*map=calloc(N+1,sizeof(Map));
  Patch*P=malloc(512*sizeof(Patch));int pn=0;
  emit_prologue(b);
  int i=0;
  while(i<N){
    map[i].bc_off=i;map[i].mc_off=(int)b->n;
    int op=C[i++];
    if(op==0){ /* HALT */
      if(os==0)emit_epilogue_linux(b); else { emit_pop_rax(b); b1(b,0xC3); }
      break;
    }
    else if(op==1){ /* PUSH */ int64_t v=0; if(i<N)v=C[i++]; emit_push(b,v); }
    else if(op==2){ /* POP */ emit_pop_rax(b); }
    else if(op==3){ emit_dup(b); }
    else if(op==7){ emit_add(b); }
    else if(op==8){ emit_sub(b); }
    else if(op==9){ emit_mul(b); }
    else if(op==11){ emit_neg(b); }
    else if(op==17){ /* EQ */ emit_cmp_set(b,0x94); }
    else if(op==18){ /* NE */ emit_cmp_set(b,0x95); }
    else if(op==19){ /* LT */ emit_cmp_set(b,0x9C); }
    else if(op==20){ /* LE */ emit_cmp_set(b,0x9E); }
    else if(op==21){ /* GT */ emit_cmp_set(b,0x9F); }
    else if(op==22){ /* GE */ emit_cmp_set(b,0x9D); }
    else if(op==23){ /* LOAD */ int s=0; if(i<N)s=C[i++]; emit_load(b,s); }
    else if(op==24){ /* STORE */ int s=0; if(i<N)s=C[i++]; emit_store(b,s); }
    else if(op==25){ /* JMP */ int t=0; if(i<N)t=C[i++];
      b1(b,0xE9); if(pn<512){P[pn].patch_at=(int)b->n;P[pn].target_bc=t;P[pn].kind=0;pn++;}
      bu32(b,0);
    }
    else if(op==27){ /* JNZ */ int t=0; if(i<N)t=C[i++];
      emit_pop_rax(b);
      b1(b,0x48);b1(b,0x85);b1(b,0xC0); /* test rax,rax */
      b1(b,0x0F);b1(b,0x85); /* jnz rel32 */
      if(pn<512){P[pn].patch_at=(int)b->n;P[pn].target_bc=t;P[pn].kind=1;pn++;}
      bu32(b,0);
    }
    else if(op==26){ /* JZ */ int t=0; if(i<N)t=C[i++];
      emit_pop_rax(b);
      b1(b,0x48);b1(b,0x85);b1(b,0xC0);
      b1(b,0x0F);b1(b,0x84);
      if(pn<512){P[pn].patch_at=(int)b->n;P[pn].target_bc=t;P[pn].kind=1;pn++;}
      bu32(b,0);
    }
    else if(op==28){ /* CALL skip as jmp-ish unsupported fully */ int t=0; if(i<N)t=C[i++]; (void)t; }
    else if(op==29){ /* RET */ b1(b,0xC3); }
    else if(op==30){ /* PRINT */ emit_print_linux(b); }
    else if(op==39){ /* INC_L */ int s=0; if(i<N)s=C[i++];
      b1(b,0x49);b1(b,0xFF);b1(b,0x84);b1(b,0x24);bu32(b,(uint32_t)(s*8));
    }
    else if(op==40){ /* DEC_L */ int s=0; if(i<N)s=C[i++];
      b1(b,0x49);b1(b,0xFF);b1(b,0x8C);b1(b,0x24);bu32(b,(uint32_t)(s*8));
    }
    else {
      /* unknown: try skip 0-3 args by not consuming - stop */
      break;
    }
  }
  /* patch jumps: find mc_off for target_bc */
  int p;
  for(p=0;p<pn;p++){
    int tb=P[p].target_bc;
    int mct=-1,k;
    for(k=0;k<N;k++) if(map[k].bc_off==tb){mct=map[k].mc_off;break;}
    if(mct<0) continue;
    int at=P[p].patch_at;
    int32_t rel=mct-(at+4);
    b->d[at]=rel&0xff; b->d[at+1]=(rel>>8)&0xff; b->d[at+2]=(rel>>16)&0xff; b->d[at+3]=(rel>>24)&0xff;
  }
  free(map);free(P);
  if(os==0) emit_epilogue_linux(b);
}

static int write_elf(const char*out,B*code){
  B f;binit(&f);
  size_t phoff=64,entry=64+56,filesz=entry+code->n,memsz=filesz+16384;
  uint8_t mag[]={0x7f,'E','L','F',2,1,1,0};bn(&f,mag,8);bu64(&f,0);
  bu16(&f,2);bu16(&f,62);bu32(&f,1);bu64(&f,0x400000+entry);bu64(&f,phoff);bu64(&f,0);
  bu32(&f,0);bu16(&f,64);bu16(&f,56);bu16(&f,1);bu16(&f,0);bu16(&f,0);bu16(&f,0);
  bu32(&f,1);bu32(&f,7);bu64(&f,0);bu64(&f,0x400000);bu64(&f,0x400000);
  bu64(&f,filesz);bu64(&f,memsz);bu64(&f,4096);
  bn(&f,code->d,code->n);
  FILE*o=fopen(out,"wb");if(!o)return 1;
  fwrite(f.d,1,f.n,o);fclose(o);free(f.d);return 0;
}
static int write_pe(const char*out,B*code){
  B f;binit(&f);b1(&f,'M');b1(&f,'Z');
  size_t i;for(i=0;i<58;i++)b1(&f,0);bu32(&f,128);
  for(i=0;i<64;i++)b1(&f,0);
  b1(&f,'P');b1(&f,'E');b1(&f,0);b1(&f,0);
  bu16(&f,0x8664);bu16(&f,1);bu32(&f,0);bu32(&f,0);bu32(&f,0);bu16(&f,0xF0);bu16(&f,0x23);
  while(f.n<512)b1(&f,0);
  bn(&f,code->d,code->n);
  FILE*o=fopen(out,"wb");if(!o)return 1;
  fwrite(f.d,1,f.n,o);fclose(o);free(f.d);return 0;
}
static int write_macho(const char*out,B*code){
  B f;binit(&f);bu32(&f,0xFEEDFACF);bu32(&f,0x01000007);bu32(&f,1);bu32(&f,5);
  bu32(&f,1);bu32(&f,0);bu32(&f,0);bu32(&f,0);
  bn(&f,code->d,code->n);
  FILE*o=fopen(out,"wb");if(!o)return 1;
  fwrite(f.d,1,f.n,o);fclose(o);free(f.d);return 0;
}
int main(int argc,char**argv){
  int os=0;const char*out=0,*codepath=0;int i;
  for(i=1;i<argc;i++){
    if(!strcmp(argv[i],"--linux"))os=0;
    else if(!strcmp(argv[i],"--windows")||!strcmp(argv[i],"--win"))os=1;
    else if(!strcmp(argv[i],"--macos")||!strcmp(argv[i],"--mac"))os=2;
    else if(!out)out=argv[i];
    else codepath=argv[i];
  }
  if(!out||!codepath){
    fprintf(stderr,
      "pegbin — native subset of Pegassus bytecode\n"
      "uso: pegbin [--linux|--windows|--macos] <salida> <codigo.pegbc>\n"
      "soporta: push/pop/dup add/sub/mul neg eq/ne/lt/le/gt/ge\n"
      "         load/store jmp/jz/jnz inc_l/dec_l halt\n"
      "semantica completa = VM Pegassus (interpretador)\n");
    return 1;
  }
  int n=0;int*C=load_code(codepath,&n);if(!C){fprintf(stderr,"no code\n");return 1;}
  B mc;binit(&mc);gen_mc(&mc,C,n,os);free(C);
  int rc=0;
  if(os==0)rc=write_elf(out,&mc);
  else if(os==1)rc=write_pe(out,&mc);
  else rc=write_macho(out,&mc);
  free(mc.d);
  if(rc){fprintf(stderr,"write fail\n");return 1;}
  return 0;
}
