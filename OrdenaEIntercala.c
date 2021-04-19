#include <iostream>
#include <stdio.h>
#include <iostream>
#include <string.h> 
#include <stdlib.h>
#include <math.h>
using namespace std;

#pragma pack(1)

struct Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};
typedef struct Endereco endc;

int compara_endc(const void *e1, const void *e2){
	return strncmp(((endc*)e1)->cep,((endc*)e2)->cep,8);
}

void interc_endc(char *a1, char *a2, char *aSaida){   
  FILE *x, *y, *saida;
  endc a, b;
	x=fopen(a1,"r");
  y=fopen(a2,"r");
  saida=fopen(aSaida,"w");
  fread(&a,sizeof(endc),1,x);
  fread(&b,sizeof(endc),1,y);
  while (!feof(x) && !feof(y)){
    if (compara_endc(&a,&b)<0){
      fwrite(&a,sizeof(endc),1,saida);
      fread(&a,sizeof(endc),1,x);
    }else{
      fwrite(&b,sizeof(endc),1,saida);
      fread(&b,sizeof(endc),1,y);
    }
  }
  while (!feof(y)){
    fwrite(&a,sizeof(endc),1,saida);
    fread(&a,sizeof(endc),1,x);
  }
  while (!feof(y)){
    fwrite(&b,sizeof(endc),1,saida);
    fread(&b,sizeof(endc),1,y);
  }
  fclose(x);
  fclose(y);
  fclose(saida);
}

int main(int argc, char**argv){
	FILE *z; 
  FILE *saida;
  endc *c;
	z=fopen("cep.dat","r"); 
  fseek(z,0,SEEK_END);
  long tam_arq=ftell(z);  
  int bloc=16;
  long qnt_reg=(tam_arq)/(sizeof(endc));
  long regbloco=(qnt_reg)/(bloc);
  cout<<"\n\n";
  cout<<"Tamanho do Arquivo: "<<tam_arq<<"\n";
	cout<<"Tamanho do Registro: "<<sizeof(endc)<<"\n";
	cout<<"Tamanho do Arquivo em Registros: "<<qnt_reg<<"\n";
  cout<<"Registros por Bloco: "<<regbloco<<"\n";
  c=(endc*) malloc(regbloco*sizeof(endc));
	rewind(z);
  free(c);
  fclose(z);
  interc_endc("1.dat","2.dat","17.dat");
  interc_endc("3.dat","4.dat","18.dat");
  interc_endc("5.dat", "6.dat", "19.dat");
  interc_endc("7.dat", "8.dat", "20.dat");
  interc_endc("9.dat", "10.dat", "21.dat");
  interc_endc("11.dat", "12.dat", "22.dat");
  interc_endc("13.dat", "14.dat", "23.dat");
  interc_endc("15.dat", "16.dat", "24.dat");
  interc_endc("17.dat", "18.dat", "25.dat");
  interc_endc("19.dat", "20.dat", "26.dat");
  interc_endc("21.dat", "22.dat", "27.dat");
  interc_endc("23.dat", "24.dat", "28.dat");
  interc_endc("25.dat", "26.dat", "29.dat");
  interc_endc("27.dat", "28.dat", "30.dat");
  interc_endc("29.dat", "30.dat", "31.dat");
  cout<<"\n\n";  
  cout<<"O arquivo 'intercalado_final.dat' foi criado\n";
  rename("31.dat", "intercalado_final");
  return 0;
}