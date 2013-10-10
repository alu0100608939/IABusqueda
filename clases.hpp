#include<iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>   
#include <curses.h>
#include <unistd.h>
using namespace std;

void pressEnter(){ 
 int i=0;
  while (i == 0){
    cin.ignore();
    i = 1;
  }
}

  
class casilla_{
private:
  int pos_i;
  int pos_j;
  int* tipo;
  bool visitado;
 
public:  
  casilla_(int i =0, int j =0){
    pos_i = i;
    pos_j = j;
    visitado = false;
    tipo = new int [3];
    for (int k = 0; k < 3; k++){
      tipo[k] = 0;
    }
  }
  
  void visita(){
    visitado = true;
  }
  
  bool get_visitado(){
    return visitado;
  }
  
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
  
  int get_pos_i(){
   return pos_i;
  }
   int get_pos_j(){
    return pos_j;
  }
  void asigna_pos(int i, int j){
    pos_i = i;
    pos_j = j;
  }
};

class cortacesped_{
private:
  int* s; // 0 -> Arriba, 1->Izquierda, 2->Abajo 3->Derecha
  bool f;
  casilla_* pos;
  public:
  cortacesped_(int i =0,int j =0){
    s = new int[4];
    for (int k = 0; k < 4; k++){
      s[k] = 0;
    }
    f = false;
    pos = new casilla_(i,j);
  }
  void set_pos(int i, int j){
    pos->asigna_pos(i, j);
  }
  int get_pos_i(){
    return pos->get_pos_i();
  }
  
  int get_pos_j(){
    return pos->get_pos_j();
  }
  void set_s(int q){
    
    s[q] = 1;
  } 
  int get_s(int i){
    
    return s[i];
  }
  void set_f(){
    f = true;
  }
  void reset_s(){
    for (int i=0;i<4;i++){
      s[i] = 0;
    }
  }
};


class jardin_{
private:
  int ancho_;
  int alto_;
  int obs_;
  casilla_** casillas;
  cortacesped_* qt;
public:
  
  jardin_(int alt, int an,int obs, int qi, int qj){
    ancho_ = an;
    alto_ = alt;
    obs_ = obs;
    qt = new cortacesped_(qi,qj);
    casillas = new casilla_*[ancho_*alto_-1];
    asigna_casillas();
    asigna_obstaculos();
    }
    
  void asigna_casillas(){
     for (int i = 0; i < ancho_; i++){ 
	for (int j = 0; j < alto_; j++){
	  casillas[i+j*ancho_] = new casilla_(i,j);	  
	  casillas[i+j*ancho_]->asigna_cesped_alto();     
     } 
    }
  }
  	  
  void asigna_obstaculos(){
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
  
    int nodo(int i, int j, int k){
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
  
  void runDFS(int i, int j){
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
      
    }
     if(control == 1 && qt->get_pos_j()-1 >= 0 && qt->get_s(1) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()-1);
    }
     if(control == 2 && (qt->get_pos_i()+1) <= ancho_-1 && qt->get_s(2) == 0){
   //  cout << "Mueve abajo" << endl;
      qt->set_pos(qt->get_pos_i()+1, qt->get_pos_j());
     
    }
     if(control == 3 && qt->get_pos_j()+1 <= alto_-1 && qt->get_s(3) == 0){
      qt->set_pos(qt->get_pos_i(), qt->get_pos_j()+1);
      
    }
    mostrar_jardin();
  }
	  


  void mostrar_jardin(){
    int k;
    system("clear");
    cout << endl << endl;
  for (int i = 0; i < ancho_; i++){ 
      cout << "\t\t";
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
   cout << endl << endl;
  }
};
    
