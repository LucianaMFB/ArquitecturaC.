#include <iostream>
#include <vector>

void print(std::vector<int> bits)
{
    for (int i = 0; i < bits.size(); i++)
    {
        std::cout << bits[i];
    }
    return;
}

void print_todo(int signo, std::vector<int> Exponente, std::vector<int> Part_float)
{
    std::cout << std::endl;
    std::cout << "  ";
    std::cout << signo << " ";
    print(Exponente);
    std::cout << " ";
    print(Part_float);
    std::cout << " ";
    return;
}

std::vector<int> Con_Binario_Entero(int numero)
{
    std::vector<int> bin_int;

    if (numero < 0)
    {
        numero = numero * -1;
    }
    
    while (numero > 0)
    {
        bin_int.insert(bin_int.begin(), numero % 2);
        numero /= 2;
    }
    return bin_int;
}

/*int Definir_Signo(int numero)
{
    int signo = -1;
    
    if(numero > -1)
    {
        signo = 0;
    }
    
    else
    {
        signo = 1;
    }
    return signo;
}*/

std::vector<int> Con_Binario_Float(float parte_fracc)
{
    int cont = 0;
    std::vector<int> bin_fracc;
    
    while((parte_fracc!=0) && (cont < 16))
    {
        parte_fracc = parte_fracc * 2;
        std::cout << "      Multiplicado por 2: " << parte_fracc << std::endl;
        
        if(parte_fracc < 1)
        {
            std::cout << "0     Menor que uno: " << parte_fracc << std::endl;
            bin_fracc.push_back(0);
        }
        
        else
        {
            std::cout << "1     Mayor que uno: " << parte_fracc << std::endl;
            bin_fracc.push_back(1);
            parte_fracc = parte_fracc - 1;
            std::cout << "      Menos uno: " << parte_fracc << std::endl;
        }
        
        cont++;
    }
    
    return bin_fracc;
}

void Convertir_Binario_Fracc(float num_fracc)
{
   //------------------------- PARA SEPARAR INT DE FLOAT ----------------------------
   int parte_entera = 0;
   float parte_fracc = 0;
   int signo = -1;
   
   if (num_fracc < 0)
   {
        parte_entera = (int)num_fracc*-1;
        parte_fracc = parte_entera*-1 - num_fracc;
        signo = 1;
   }
   
   else
   {
       parte_entera = (int)num_fracc;
       parte_fracc = num_fracc - parte_entera;
       signo = 0;
   }
   
   //int signo = Definir_Signo(parte_entera);
   
   //----------------------- A BINARIO -----------------------------------------------
   
   std::vector<int> Part_int = Con_Binario_Entero(parte_entera);
   std::vector<int> Part_float = Con_Binario_Float(parte_fracc);
   
   //------------------------ JUNTAR TODO ------------------------------------------
   
   int exponente = Part_int.size() - 1; 
   
   //--------------------------------- EXPONENTE --------------------------------
   std::vector<int> Exponente = Con_Binario_Entero(127+exponente);
   
   for(int i = Part_int.size()-1; i > 0; i--)
   {
        Part_float.insert(Part_float.begin(), Part_int[i]);
   }
   
   // -------------------------------------------------------------------------------
   
   if (Part_float.size() > 23)
   {
       int exeso = Part_float.size() - 23;
       
       for(int i = 0; i < exeso; i++)
       {
            Part_float.pop_back();
       }
   }
   
   else if (Part_float.size() < 23)
   {
       int falta = 23 - Part_float.size();
       
       for(int i = 0; i < falta; i++)
       {
            Part_float.push_back(0);
       }
   }
   
   print_todo(signo, Exponente, Part_float);
   
   return;
}



int main()
{
    float Prueba = -3.555555;
    Convertir_Binario_Fracc(Prueba);
    
    //1 10000000 11000111000110101010000


    return 0;
}
