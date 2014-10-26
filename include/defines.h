#ifndef DEFINES_H
#define DEFINES_H
//As linhas acimas sao inuteis, mas impedem que o compilador mande warnings case passe aqui duas vezes
#define FILE_HEADLINE "tempo [s]         x [m]         z [m]        vx [m]        vz [m]   atitude [graus]     fuel [kg]\n"

#define TESTMEM(s) if (s == NULL) {\
  fprintf(stderr, "(3x23) Erro detetado: Memory Access Error!");\
  exit(ENOMEM);\
}
#endif
