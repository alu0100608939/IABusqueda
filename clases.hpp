#include<iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <curses.h>
#include <unistd.h>
#include <list>
using namespace std;

/**
 * Método pressEnter(): Espera a que se pulse la tecla intro para continuar
 **/
void pressEnter(){ 
 int i=0;
  while (i == 0){
    cin.ignore();
    i = 1;
  }
}
/*
 * Clase Casilla_: El Jardín estara compuesto por un array de estas casillas.
 **/
  
class casilla_{
private:
  int pos_i; // Coordenadad
  int pos_j; // Coordenada
  int* tipo; // Siendo 0 Cesped alto, 1 cesped bajo y 2 obstáculo
  bool visitado;
  int coste;
  int coste_ac;
public:  
  casilla_(int i =0, int j =0){ //Constructor
    pos_i = i;
    pos_j = j;
    visitado = false;
    coste = 99999;
    coste_ac = 1;
    tipo = new int [3];
    for (int k = 0; k < 3; k++){
      tipo[k] = 0;
    }
  }
  
  void visita(){ // Método para visitar un nodo
    visitado = true;
  }
  
  bool get_visitado(){ // Método para saber si un nodo está visitado
    return visitado;
  }
  
  //Metodos de asignación de tipo.
  
  void asigna_cesped_alto(){
    for (int i = 0; i < 3; i++){
    if (i == 0)
      tipo[i] = 1;
  } 
}  
  void asigna_cesped_bajo(){
    for (int i = 0; i < 3; i++){
    if (i == 1)
      tipo[i] = 1;
    else
      tipo[i] = 0;
  } 
} 
   void asigna_cesped_obs(){
    for (int i = 0; i < 3; i++){
    if (i == 2)
      tipo[i] = 1;
    else
      tipo[i] = 0;
     }
}
//Devuelve el tipo de una casilla. Solo podrá ser de un tipo.
  int get_tipo(){
    if (tipo[0] == 1){
      return 0;
    }
    else if (tipo[1] == 1){
      return 1;
    }
    else
      return 2;
  }
  // Métodos  para obtener las coordenadas
  int get_pos_i(){
   return pos_i;
  }
   int get_pos_j(){
    return pos_j;
  }
  
  //Método para asignar coordenadas
  void asigna_pos(int i, int j){
    pos_i = i;
    pos_j = j;
  }
  void set_coste(int c){
    coste = c;
  }
  void set_coste_ac(int c){
    coste_ac = c;
  }
  int get_coste(){
    return coste;
  }
  
  int get_coste_ac(){
    return coste_ac;
  }
  
};
bool compare_casilla(casilla_ cas1, casilla_ cas2){
    if (cas1.get_coste() < cas2.get_coste())
      return true;
   
    else
      return false;
  }
/*
 * Clase Cortacesped: Contara con un sensor de proximidad s que devuelve el estado de las
 * casillas accesibles, si ha de cortar el cesped y la casilla en la que está posicionado
 **/

class cortacesped_{ 
private:
  int* s; // 0 -> Arriba, 1->Izquierda, 2->Abajo 3->Derecha
  bool f;
  casilla_* pos;
  public:
  cortacesped_(int i =0,int j =0){ // Constructor
    s = new int[4];
    for (int k = 0; k < 4; k++){
      s[k] = 0;
    }
    f = false;
    pos = new casilla_(i,j);
  }
  
  //Setters.
  void set_pos(int i, int j){
    pos->asigna_pos(i, j);
  }
  void set_pos_2(casilla_* cas){
    pos = cas;
  }
    
    
    
  void set_s(int q){
    
    s[q] = 1;
  }
  void set_f(){
    f = true;
  }
  // Getters
  int get_pos_i(){
    return pos->get_pos_i();
  }
  
  int get_pos_j(){
    return pos->get_pos_j();
  }

  int get_s(int i){
    return s[i];
  }

  void reset_s(){ // Método que resetea el sensor.
    for (int i=0;i<4;i++){
      s[i] = 0;
    }
  }
};



/*Clase Jardin: Tablero donde se aplican los métodos.
 * Cuenta con dos dimensiones ancho_ y alto_. Se declarara un array de casillas de 
 * tamaño ancho_*alto_. Ademas cuenta con un objeto cortacesped asociado.
 */
class jardin_{
private:
  int ancho_;
  int alto_;
  int obs_;
  casilla_** casillas;
  cortacesped_* qt;
public:
  
  jardin_(int alt, int an,int obs, int qi, int qj){ //Constructor
    ancho_ = an;
    alto_ = alt;
    obs_ = obs;
    qt = new cortacesped_(qi,qj);
    casillas = new casilla_*[ancho_*alto_-1];
    asigna_casillas();
    asigna_obstaculos();
    }
    
  void asigna_casillas(){ //Iniciacion de casillas a cesped alto
     for (int i = 0; i < ancho_; i++){ 
	for (int j = 0; j < alto_; j++){
	  casillas[i+j*ancho_] = new casilla_(i,j);	  
	  casillas[i+j*ancho_]->asigna_cesped_alto();     
     } 
    }
  }
  	  
  void asigna_obstaculos(){ // Asignación aleatoria de obstáculos respecto al porcentaje
    int n_obs = obs_*ancho_*alto_/100;
    int * array_obs = new int[n_obs];
    int k = rand() % (ancho_*alto_);
    for (int i = 0; i < n_obs; i++){
      while (casillas[k]->get_tipo() == 2){
      k = rand() % (ancho_*alto_);
      }
      
      casillas[k]->asigna_cesped_obs();
  
    }
  }
  
    int nodo(int i, int j, int k){ // Método que dado un nodo i,j y un control k, devuleve el siguiente nodo
    if (k == 0){
      return (i-1)+j*ancho_;
    }
     if (k == 1){
      return i+(j-1)*ancho_;
    }
     if (k == 2){
      return (i+1)+j*ancho_;
    }
     if (k == 3){
      return i+(j+1)*ancho_;
    }
  }
  
  void runDFS(int i, int j){ // Profundidad
    int a = i;
    int b = j;
     casillas[i+j*ancho_]->visita();
  // casillas[i+j*ancho_]->visita();
   if(casillas[i+j*ancho_]->get_visitado()){
    // cout << "Nodo "<< i << " " << j << " visitado" << endl;
   }
   // for (int i = k; i < ancho_; i++){ 
	//for (int j = b; j < alto_; j++){
	  for(int k = 0; k < 4; k++){
	   // cout << i << " " << j << " " << k << endl;
	    corta_recon();
	    if(qt->get_s(k) == 0 && 
	      casillas[nodo(i,j,k)]->get_visitado() == false){
	      cout << qt->get_s(k) << " " << k << endl;
	      corta_move_auto(k);
	       usleep(50000);
	      runDFS(qt->get_pos_i(),qt->get_pos_j());
	      
	      if(k == 0){
		corta_move_auto(2);
	      }
	      if(k == 1){
		corta_move_auto(3);
	      }
	      if(k == 2){
		corta_move_auto(0);
	      }
	      if(k == 3){
		corta_move_auto(1);
	      }
	       usleep(50000);
	   // }
	  //}
	    }
	    
    }
//    cout << "Salida de DFS "<< endl;
  }
  
    void camino(int i, int j, int i_f, int j_f){
     if (i != i_f || j != j_f){
      int dist[4]; 
      int min = 999999;
      int min_  = 12;
      casillas[i+j*ancho_]->visita();
	corta_recon();
	for(int k = 0; k < 4; k++){
	  dist[k] = 999999;
	  corta_recon();
	  if(qt->get_s(k) == 0 && casillas[nodo(qt->get_pos_i(),qt->get_pos_j(),k)]->get_visitado() == false){
	    dist[k] = distancia_manhattan(casillas[nodo(qt->get_pos_i(),qt->get_pos_j(),k)], casillas[i_f+j_f*ancho_]);
	   }
	}         
	for (int q = 0; q < 4; q++){
	  if (dist[q] < min){
	    min = dist[q];
	    min_ = q;
	  }
	}
	cout << min_;
	
	corta_move_auto(min_);
	if (dist[min_] == 0){
	  return;
	}
	usleep(50000);
	if (min_ != 12){
	camino(qt->get_pos_i(),qt->get_pos_j(), i_f, j_f);
	}
	
	
	if (i != i_f || j != j_f){
	      if(min_ == 0){
		corta_move_auto(2);
		camino(qt->get_pos_i(),qt->get_pos_j(), i_f, j_f);
	      }
	      if(min_ == 1){
		corta_move_auto(3);
		camino(qt->get_pos_i(),qt->get_pos_j(), i_f, j_f);
	      }
	      if(min_ == 2){
		corta_move_auto(0);
		camino(qt->get_pos_i(),qt->get_pos_j(), i_f, j_f);
	      }
	      if(min_ == 3){
		corta_move_auto(1);
 		camino(qt->get_pos_i(),qt->get_pos_j(), i_f, j_f);
	      }
	       usleep(500000);
	}
      }
     }
    
    void camino2(int x, int y, int i_f, int j_f){

	list <casilla_> abierto;  
	list <casilla_> cerrado;
	list <casilla_>::iterator it = abierto.begin();
	
	abierto.push_back(*casillas[0]);
	abierto.front().set_coste(distancia_manhattan(casillas[x+y*ancho_], casillas[i_f+j_f*ancho_]));
	
	while (abierto.empty() == false || (abierto.front().get_pos_i() == i_f && abierto.front().get_pos_j() == j_f)){
	  it = abierto.begin();
	  qt->set_pos_2(&abierto.front());
	  for(int k = 0; k < 4; k++){
	    corta_recon2();     
	    if(qt->get_s(k) == 0){
	      abierto.push_back(*casillas[qt->get_pos_i() + qt->get_pos_j()*ancho_]);
	      abierto.back().set_coste_ac(casillas[qt->get_pos_i()+qt->get_pos_j()*ancho_]->get_coste_ac()+1);
	      abierto.back().set_coste(distancia_manhattan(casillas[qt->get_pos_i() + qt->get_pos_j()*ancho_],casillas[i_f+j_f*ancho_])+abierto.back().get_coste_ac());
	    }
	    while(it != abierto.end()){
	      if((it->get_pos_i()+it->get_pos_j()*ancho_) == (abierto.back().get_pos_i() + abierto.back().get_pos_j()*ancho_)){
		if (it->get_coste() < abierto.back().get_coste()){
		  abierto.pop_back();
		}
	      }
	      it++;
	    }
	  }
	 abierto.sort(compare_casilla);
	 qt->set_pos_2(&abierto.front());
	 cerrado.push_back(abierto.front());
	 abierto.pop_front();
	  }
	
	while(cerrado.empty() != true){
	  qt->set_pos_2(&cerrado.front());
	  corta_recon();
	  mostrar_jardin();
	  cerrado.pop_front();
	  pressEnter();
	}
	
	
	
	
	/*
	while (abierto.empty() == false || (abierto.front().get_pos_i() == i_f && abierto.front().get_pos_j() == j_f)){
	    
	    for(int k = 0; k < 4; k++){
	      corta_recon2();     
	 	if(qt->get_s(k) == 0 && casillas[nodo(qt->get_pos_i(),qt->get_pos_j(),k)]->get_visitado() == false){		 
		  abierto.push_back(*casillas[cerrado.back().get_pos_i(), cerrado.back().get_pos_j(),k]);
		  abierto.back().set_coste_ac(casillas[qt->get_pos_i()+ (qt->get_pos_j())*ancho_]->get_coste_ac()+1);
		  abierto.back().set_coste(distancia_manhattan(casillas[nodo(qt->get_pos_i(),qt->get_pos_j(),k)], casillas[i_f+j_f*ancho_])+abierto.back().get_coste_ac());
		 
		 /* while(it != abierto.end()){
		    if(casillas[it->get_pos_i()+it->get_pos_j()*ancho_] == casillas[abierto.back().get_pos_i()+abierto.back().get_pos_j()*ancho_]){
		      if(it->get_coste() < abierto.back().get_coste()){
			abierto.pop_back();
		      }
		    }
		    it++;
		  }
		}
	      }
	cerrado.push_back(abierto.front());
	abierto.pop_front();
	abierto.sort(compare_casilla);
	qt->set_pos_2(&abierto.front());
	}
	
	cout << "Camino encontrado" << endl;
	qt->set_pos_2(casillas[0]);
	corta_recon();
	
	
	}*/
      }
      
  void corta_recon(){
    qt->reset_s();
  //  cout << "Dentro de corta_recon" << endl;
    if (casillas[qt->get_pos_i()+qt->get_pos_j()*ancho_]->get_tipo() == 0){
      casillas[qt->get_pos_i()+qt->get_pos_j()*ancho_]->asigna_cesped_bajo();
    }
    
    if(qt->get_pos_i() == 0 || casillas[qt->get_pos_i()-1+qt->get_pos_j()*ancho_]->get_tipo() == 2){
      qt->set_s(0);
    
    }
    if (qt->get_pos_i() == ancho_-1 || casillas[qt->get_pos_i()+1+qt->get_pos_j()*ancho_]->get_tipo() == 2){
      qt->set_s(2);
    }
    if(qt->get_pos_j() == 0 || casillas[qt->get_pos_i()+(qt->get_pos_j()-1)*ancho_]->get_tipo() == 2){
      qt->set_s(1);
      
    }
    if(qt->get_pos_j() == alto_-1 || casillas[qt->get_pos_i()+(qt->get_pos_j()+1)*ancho_]->get_tipo() == 2){
      qt->set_s(3);
      
    }
  }
  void corta_recon2(){
    qt->reset_s();
  //  cout << "Dentro de corta_recon" << endl;
    if(qt->get_pos_i() == 0 || casillas[qt->get_pos_i()-1+qt->get_pos_j()*ancho_]->get_tipo() == 2){
      qt->set_s(0);
    
    }
    if (qt->get_pos_i() == ancho_-1 || casillas[qt->get_pos_i()+1+qt->get_pos_j()*ancho_]->get_tipo() == 2){
      qt->set_s(2);
    }
    if(qt->get_pos_j() == 0 || casillas[qt->get_pos_i()+(qt->get_pos_j()-1)*ancho_]->get_tipo() == 2){
      qt->set_s(1);
      
    }
    if(qt->get_pos_j() == alto_-1 || casillas[qt->get_pos_i()+(qt->get_pos_j()+1)*ancho_]->get_tipo() == 2){
      qt->set_s(3);
      
    }
  }
  void corta_move(){
    initscr();
    cbreak ();
    char control;
    control=getch ();
    corta_recon();
   // casillas[qt->get_pos_i(),qt->get_pos_j()]->asigna_cesped_bajo();
    
    if(control == '8' && qt->get_pos_i()-1 >= 0 && qt->get_s(0) == 0){
  
      qt->set_pos(qt->get_pos_i()-1, qt->get_pos_j());
      
    }
     if(control == '4' && qt->get_pos_j()-1 >= 0 && qt->get_s(1) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()-1);
    }
     if(control == '2' && (qt->get_pos_i()+1) <= ancho_ && qt->get_s(2) == 0){
     
      qt->set_pos(qt->get_pos_i()+1, qt->get_pos_j());
     
    }
     if(control == '6' && qt->get_pos_j()+1 <= alto_ && qt->get_s(3) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()+1);
      
    }
    endwin ();
    mostrar_jardin();
  }
   void corta_move_auto(int control){
    
   corta_recon();
   // casillas[qt->get_pos_i(),qt->get_pos_j()]->asigna_cesped_bajo();
    
    if(control == 0 && qt->get_pos_i()-1 >= 0 && qt->get_s(0) == 0){
      qt->set_pos(qt->get_pos_i()-1, qt->get_pos_j());
      mostrar_jardin();
      
    }
     if(control == 1 && qt->get_pos_j()-1 >= 0 && qt->get_s(1) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()-1);
      mostrar_jardin();
    }
     if(control == 2 && (qt->get_pos_i()+1) <= ancho_-1 && qt->get_s(2) == 0){
   //  cout << "Mueve abajo" << endl;
      qt->set_pos(qt->get_pos_i()+1, qt->get_pos_j());
      mostrar_jardin();
     
    }
     if(control == 3 && qt->get_pos_j()+1 <= alto_-1 && qt->get_s(3) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()+1);
      mostrar_jardin();
      
    }

  }
  
  int distancia_manhattan(casilla_* A, casilla_* B){
    return abs(A->get_pos_i() - B->get_pos_i()) + abs(A->get_pos_j()-B->get_pos_j());
  }

 
  void mostrar_jardin(){
    int k;
    system("clear");
      cout << "\t\t  ";
    
  for (int j = 0; j < alto_; j++){
      if (j < 10)
	cout << j << " ";
      else
	cout << j;
    }
    cout << endl;
  for (int i = 0; i < ancho_; i++){
    if (i < 10)
      cout <<"\t"<<"\t" << i << " ";
    else
       cout << "\t\t" << i;
    
    for (int j = 0; j < alto_; j++){
	
	if  (i+j*ancho_ == qt->get_pos_i()+qt->get_pos_j()*ancho_){
	   cout << "\033[31m██\033[0m";   
	}
	else if (casillas[i+j*ancho_]->get_tipo() == 0 ){
	  cout << "\033[5;32m██\033[0m";
	}
	else if (casillas[i+j*ancho_]->get_tipo() == 1 ){
	  cout << "\033[2;33m██\033[0m";
	}
	else if (casillas[i+j*ancho_]->get_tipo() == 2 ){
	  cout << "\033[33m██\033[0m";
	} 
	
      }
  cout << endl;
  } 
  }
};
    
