#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define V_FUNC 2

typedef void (**FP)();
typedef void (*PF)();

typedef enum {
    _A, _B, _C
}TI;

typedef struct {
    TI type_info;
    FP vtbl;
}VTbl;

typedef struct{
  int age;
  VTbl* vptr;
}_A_Cl;

typedef struct {
  _A_Cl a_sub;
  PF ptr;
}_B_Cl;

typedef struct {
  _B_Cl b_sub;
}_C_Cl;

// A class virtual member function
void _vf_A_Cl1(_A_Cl* const th) {
    printf("Base class virtual func 1\n");
}

void _vf_A_Cl2(_A_Cl* const th) {
    printf("Base class vrtrual func 2\n");
}

// class A not virtual member function 
void _nov_A_CL(_A_Cl* const th) {
    puts("Not virtual function\n");
}

// class B _vf_A_Cl1 overrided virtual functions
void _vf_B_Cl1(_A_Cl* const th) {
  puts("Derived class override 1\n");
}

// class B _vf_A_Cl2 overrided virtual functions
void _vf_B_Cl2(_A_Cl* const th) {
  puts("Derived class override 2\n");
}

// vitrual function started from class B
void _vf_B_CL3(_B_Cl* const th) {
  puts("Virtual from this class \n");
}

// class B _vf_B_CL3 overrded function  
void _vf_C_CL3(_B_Cl* const th) {
  puts("Derived from class B \n");
}

int main() {
  // creation A class an object instance
  _A_Cl ob;
  ob.vptr = malloc(sizeof(VTbl));
  
  // initialization of virtual table members
  ob.vptr->type_info = _A;
  ob.vptr->vtbl = malloc(V_FUNC * sizeof(FP));
  ob.vptr->vtbl[0] = _vf_A_Cl1 ;
  ob.vptr->vtbl[1] = _vf_A_Cl2;
  
  // call not virtual function from class A;
  _nov_A_CL(&ob);

  // call virtual function from virtual table 
  ob.vptr->vtbl[0]();
  ob.vptr->vtbl[1]();
  
  
  // creation B class an object instance and virtual table
  _B_Cl obj;
  obj.a_sub.vptr = malloc(sizeof(VTbl));
  obj.a_sub.vptr->type_info = _B;
  obj.a_sub.vptr->vtbl = malloc(V_FUNC * sizeof(FP));
  obj.a_sub.vptr->vtbl[0] = _vf_B_Cl1;
  obj.a_sub.vptr->vtbl[1] = _vf_B_Cl2;
  obj.ptr = _vf_B_CL3;
  
  // reffering to B object by base class pointer and calling overrided function
  _A_Cl* ptr = (_A_Cl*)&obj;  
  ptr->vptr->vtbl[0]();
  
  // Creating class C which doesn't override A virtual functions,class B does  
  _C_Cl obc;
  obc.b_sub.a_sub.vptr = obj.a_sub.vptr;
  obc.b_sub.ptr = _vf_C_CL3;
  obc.b_sub.a_sub.vptr->vtbl[0]();
  obc.b_sub.ptr();
  
  // freeing memory
  free(ob.vptr->vtbl);
  free(ob.vptr);
  
  free(obj.a_sub.vptr->vtbl);
  free(obj.a_sub.vptr);
  
}
