#include"clases.hpp"

int main(){
  
  system("clear");
  int alto, ancho, porc, x, y;
  int op, c_i, c_j;
  char sn;
  cout << "INTELIGENCIA ARTIFICIAL: PRACTICA BUSQUEDAS" << endl;
  cout << "Introduzca las dimensiones del jardín " << endl
  << "Ancho: ";
  cin >> ancho;
  cout << "Alto: ";
  cin >> alto;
  cout << "Porcentaje de obstáculos: ";
  cin >> porc;
  cout << "Desea definir las coordenadas iniciales del cortacesped? (Y/N)" << endl;
  cin >> sn;
  if ( sn == 'y' || sn == 'Y'){
    cout << "Coordenada X:";
    cin >> x;
    cout << "Coordenada Y:";
    cin >> y;
  }
  else{
    x = 0;
    y = 0;
  }
  
   //alto = 20; ancho = 10; porc = 10; x = 0; y = 0

  jardin_ Jardin(ancho,alto,porc,x,y);
  Jardin.mostrar_jardin();

  pressEnter();
  cout << "Elija el modo de ejecución: " << endl << "	1. DFS" << endl << "	2. Manual" << "	3. Camino Escalada"<<endl;
  cin >> op;
  
  switch(op){
    case 1:
      Jardin.mostrar_jardin();
      Jardin.runDFS(x,y);
      Jardin.mostrar_jardin();
      break;
    case 2:
    cout << "Controles (Numpad):" << endl << "\t8-Arriba" << endl<< "4-Izda\t6-Dcha"<<endl<<"\t2-Abajo"; 
    //Jardin.mostrar_jardin();  
    pressEnter();
    while(true){
      Jardin.corta_move();
    }
    break;
    case 3:
	cout << "Introduzca el punto al que calcular el camino" << endl << "Coordenada x:";
	cin >> c_i;
	cout << "Coordenada y:";
	cin >> c_j;
        Jardin.camino(c_i,c_j);
	break;
  } 
  Jardin.mostrar_jardin();
  pressEnter();
  
}