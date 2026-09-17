#include<iostream>
int add(int a , int b){
    return a+b;
}
int main (){
    /* Affichage principale*/
   std::cout<<"Hello world"<<std::endl;
   int result = add(1,2);
   std::cout<<"le resultat de cette addition est :"<<result <<std::endl;
    return 0;
}
