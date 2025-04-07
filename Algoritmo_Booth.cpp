#include <iostream>
#include <vector>

std::vector<int> SumaUnBit(std::vector<int> binario)
{
    int sum = 1;

    for (int i = binario.size()-1; i > -1; i--)
    {
        if (binario[i] == 1 && sum == 1)
        {
            binario[i] = 0;
            sum = 1;
            continue;
        }

        else if (binario[i] == 0 && sum == 1)
        {
            binario[i] = 1;
            sum = 0;
            continue;
        }

        else if ((binario[i] == 1) && (sum == 0))
        {
            binario[i] = 1;
            sum = 0;
            continue;
        }

        else if ((binario[i] == 0) && (sum == 0))
        {
            binario[i] = 0;
            sum = 0;
            continue;
        }
    }
    return binario;
}

std::vector<int> convertirComplemento2(std::vector<int> bits)
{
    for (int i = bits.size()-1; i > -1; i--)
    {
        if (bits[i] == 0)
        {
            bits[i] = 1;
        }

        else if (bits[i] == 1)
        {
            bits[i] = 0;
        }
    }

    bits = SumaUnBit(bits);
    return bits;
}

void print(std::vector<int> bits)
{
    for (int i = 0; i < bits.size(); i++)
    {
        std::cout << bits[i];
    }
    std::cout << std::endl;
    return;
}

void print_(std::vector<int> bits)
{
    for (int i = 0; i < bits.size(); i++)
    {
        std::cout << bits[i];
    }
    return;
}

std::vector<int> convertirABinario(int numero)
{
    std::vector<int> bits;

    if (numero > -1)
    {
        while (numero > 0)
        {
            bits.insert(bits.begin(), numero % 2);
            numero /= 2;
        }
        
        if (bits[0] == 1)
        {
            bits.insert(bits.begin(), 0);
        }
        return bits;
    }

    else
    {
        //std::cout << numero << std::endl;
        numero = numero * -1;
        //std::cout << numero << std::endl;
        while (numero > 0)
        {
            bits.insert(bits.begin(), numero % 2);
            numero /= 2;
        }

        int a = bits.size();

        for (int i = 0; i < 4 - a; i++)
        {
            bits.insert(bits.begin(), 0);
        }

        bits = convertirComplemento2(bits);
        if (bits[0] == 0)
        {
            bits.insert(bits.begin(), 1);
        }
        return bits;
    }


}

std::vector<int> SumarA_M (std::vector<int> A, std::vector<int> M)
{
    int acarreo = 0;
    
    for(int i = A.size()-1; i>-1; i--)
    {
        int suma = A[i] + M[i] + acarreo;
        
        if (suma == 0)
        {
            A[i] = 0;
            acarreo = 0;
        }
        
        else if (suma == 1)
        {
            A[i] = 1;
            acarreo = 0;
        }
        
        else if (suma == 2)
        {
            A[i] = 0;
            acarreo = 1;
        }
        
        else if (suma == 3)
        {
            A[i] = 1;
            acarreo = 1;
        }
        
    }
    return A;
}

std::vector<int> RestarA_M (std::vector<int> A, std::vector<int> M)
{
    std::cout << "  M:  ";
    print(M);
    std::cout << "  A:  ";
    print(A);
    M = convertirComplemento2(M);
    std::cout << "  M en Complemento 2:  ";
    print(M);
    A = SumarA_M (A,M);
    std::cout << "  A - M:  ";
    print(A);
    
    return A;
    
}

int Convertir_Entero(std::vector<int> A, std::vector<int> Q)
{
    int cont = 0;
    
    if (A[0] == 1)
    {
        int exponente = A.size() + Q.size() - 1;
        int resultado = 1 << exponente;
        cont = cont - resultado;
        A[0] = 0;
    }
    
    for(int i = 0; i < A.size(); i++)
    {
        if(Q[i] == 1)
        {
            int exponente = Q.size()-1-i;
            int resultado = 1 << exponente;
            cont = cont + resultado;
        }
        
        if(A[i] == 1)
        {
            int exponente = A.size()+Q.size()-1-i;
            int resultado = 1 << exponente;
            cont = cont + resultado;
        }
    }
    return cont;
}

void AlgoritmoBoth(std::vector<int> M, std::vector<int> Q)
{
    
    //------COMPARAR TAMAÑOS Y RELLENAR DEPENDIENDO DEL MAYOR------
    
    while(M.size() < Q.size())
    {
        M.insert(M.begin(), M[0]);
    }
    
    while(M.size() > Q.size())
    {
        Q.insert(Q.begin(), Q[0]);  
    }
    
    std::cout << "  Multiplicando M:  ";
    print(M);
    std::cout << "  Multiplicador Q:  ";
    print(Q);
    
    //------ CREAR VARIABLES NECESARIAS (A, Q-1,n) --------------
    
    std::vector<int> A(M.size(), 0);
    int q = 0;
    int n = M.size();
    int contador = n;
    
    //-------- LOGICA PARA EL ALGORITMO ---------------------
    
    std::cout << std::endl;
    std::cout << "  ";
    print_(A);
    std::cout << "  ";
    print_(Q);
    std::cout << "  ";
    std::cout << q << std::endl;
    
    while (contador>0)
    {
        std::cout << std::endl;
        std::cout << "\x1B[33;1m  CICLO " << contador;
        std::cout << "\x1B[m"<< std::endl;
        
        if(Q[n-1] == q)
        {
            std::cout << "  Recorrimiento  porque ";
            std::cout << " Q = " << Q[n-1] << " q = " << q << std::endl;
        }
        
        else if((Q[n-1] == 0) && (q == 1))
        {
            std::cout << "  A = A + M  porque ";
            std::cout << " Q = " << Q[n-1] << " q = " << q << std::endl;
            
            A = SumarA_M (A,M);
            
        }
        
        else if((Q[n-1] == 1) && (q == 0))
        {
            std::cout << "  A = A - M  porque ";
            std::cout << " Q = " << Q[n-1] << " q = " << q << std::endl;
            
            A = RestarA_M (A,M);
           
        }
        
        //-------------- RECORRIMIENTO -----------------------
        
        std::cout << std::endl;
        std::cout << "  RECORRIMIENTO: ";
        
        q = Q[n-1];
        int a = A[n-1];
        for(int i = n-1; i > 0; i--)
        {
            Q[i] = Q[i-1];
            A[i] = A[i-1];
        }
        
        Q[0] = a;
        A[0] = A[1];
        
        std::cout << std::endl;
        std::cout << "  ";
        print_(A);
        std::cout << "  ";
        print_(Q);
        std::cout << "  ";
        std::cout << q << std::endl;
        
        contador--;
    }
    
    std::cout << std::endl;
    std::cout << "\x1B[95;1m  RESULTADO: ";
    std::cout << std::endl;
    std::cout << "  ";
    print_(A);
    print_(Q);
    std::cout << "   => ";
    
    std::cout << Convertir_Entero(A, Q) << std::endl;
    std::cout << "\x1B[m" << std::endl;
}



int main()
{
    std::cout << std::endl;
    std::cout << std::endl;
    int Multiplicando = -1;
    int Multiplicador = -1;
    std::cout << " Ingrese el Multiplicando: ";
    std::cin >> Multiplicando;
    
    while((Multiplicando > 255)||(Multiplicando < -256))
    {
        std::cout << " FUERA DE RANGO " << std::endl;
        std::cout << " Ingrese el Multiplicando: ";
        std::cin >> Multiplicando;
    }
    std::cout << " Ingrese el Multiplicador: ";
    
    std::cin >> Multiplicador;
    while((Multiplicador > 255)||(Multiplicador < -256))
    {
        std::cout << " FUERA DE RANGO " << std::endl;
        std::cout << " Ingrese el Multiplicador: ";
        std::cin >> Multiplicador;
    }
    std::cout << std::endl;
    
    if((Multiplicador == 0) || (Multiplicando == 0))
    {
        std::cout << "\x1B[95;1m  RESULTADO: => 0 \x1B[m";
        return 0;
    }
    
    std::vector<int> M = convertirABinario(Multiplicando);
    std::vector<int> Q = convertirABinario(Multiplicador);
    
    AlgoritmoBoth(M, Q);

    return 0;
}
