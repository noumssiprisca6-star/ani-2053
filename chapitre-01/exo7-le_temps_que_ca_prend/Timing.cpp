#include<iostream>
#include<string>

    class Animal{
        protected :
        std::string Nom ;
        public:
        Animal(std::string nom): Nom(nom){}
        void Marcher (){
        std::cout<<"marche vite"<<std::endl;}
    };
    
    
    int main(){
        Animal animal ("rex");
        animal.Marcher();
        return 0;
    }
    
