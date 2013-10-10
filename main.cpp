#include"clases.hpp"

int main(){
  cortacesped_ corta(0,0);
  jardin_ Jardin(50,50,30,0,0);
  Jardin.asigna_casillas();    
  Jardin.asigna_obstaculos();
  Jardin.asigna_sucesores();
  Jardin.mostrar_jardin();
  
  Jardin.runDFS(0,0);
  
}