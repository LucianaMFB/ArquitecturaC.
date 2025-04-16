#include <iostream>
#include <vector>

void print(std::vector<int> A)
{
    for (int i = 0; i < A.size(); i++)
    {
        std::cout << A[i];
    }
    return;
}

void printAll(std::vector<int> binarioIEEE)
{
    std::cout << std::endl;
    std::cout << "  ";
    std::cout << binarioIEEE[0] << " ";
    for (int i = 1; i < 9; i++)
    {
        std::cout << binarioIEEE[i];
    }
    std::cout << " ";
    for (int i = 9; i < 32; i++)
    {
        std::cout << binarioIEEE[i];
    }
    std::cout << " ";
    return;
}

std::vector<int> convertirEnteroABinario(int numeroEntero)
{
    std::vector<int> enteroBinario;

    if (numeroEntero < 0)
    {
        numeroEntero = numeroEntero * -1;
    }
    
    else if (numeroEntero == 0)
    {
        enteroBinario.insert(enteroBinario.begin(), 0);
    }
    
    while (numeroEntero > 0)
    {
        enteroBinario.insert(enteroBinario.begin(), numeroEntero % 2);
        numeroEntero /= 2;
    }
    return enteroBinario;
}

std::vector<int> convertirFlotanteABinario(float numeroFloat)
{
    int cont = 0;
    std::vector<int> floatBinario;
    
    while((numeroFloat!=0) && (cont < 16))
    {
        numeroFloat = numeroFloat * 2;
        //std::cout << "      Multiplicado por 2: " << numeroFloat << std::endl;
        
        if(numeroFloat < 1)
        {
            //std::cout << "0     Menor que uno: " << numeroFloat << std::endl;
            floatBinario.push_back(0);
        }
        
        else
        {
            //std::cout << "1     Mayor que uno: " << numeroFloat << std::endl;
            floatBinario.push_back(1);
            numeroFloat = numeroFloat - 1;
            //std::cout << "      Menos uno: " << numeroFloat << std::endl;
        }
        
        cont++;
    }
    
    return floatBinario;
}

std::vector<int> redondearBinarioFlotante(std::vector<int> binarioFlotante)
{
    if (binarioFlotante.size() > 23)
   {
       int exeso = binarioFlotante.size() - 23;
       
       for(int i = 0; i < exeso; i++)
       {
            binarioFlotante.pop_back();
       }
       
       return binarioFlotante;
   }
   
   else if (binarioFlotante.size() < 23)
   {
       int falta = 23 - binarioFlotante.size();
       
       for(int i = 0; i < falta; i++)
       {
            binarioFlotante.push_back(0);
       }
       
       return binarioFlotante;
   }
   
   else
   {
       return binarioFlotante;
   }
}

int buscarUno(std::vector<int> binarioFlotante)
{
    for (int i = 0; i < binarioFlotante.size(); i++)
    {
        if (binarioFlotante[i] == 1)
        {
            return (-1 * (i + 1));
            break;
        }
    }
    
    return 0;
}

std::vector<int> calcularExponente(std::vector<int> binarioEntero, std::vector<int> binarioFlotante)
{
    int exponente = 0;
    std::vector<int> binarioExponente;
    
    if (binarioEntero[0] == 0)
    {
        exponente = buscarUno(binarioFlotante);
    }
    
    else
    {
        exponente = binarioEntero.size() - 1; 
    }
    
    if (binarioEntero.size() == 1 && binarioEntero[0] == 0 && (buscarUno(binarioFlotante) == 0))
    {
        binarioExponente = convertirEnteroABinario(0);
    }
    else
    {
        binarioExponente = convertirEnteroABinario(127+exponente);
    }
    
    if (binarioExponente.size() < 8)
   {
       int falta = 8 - binarioExponente.size();
       
       for(int i = 0; i < falta; i++)
       {
            binarioExponente.insert(binarioExponente.begin(), 0);
       }
   }
    return binarioExponente;
}

std::vector<int> juntarTodo (int signo, std::vector<int> binarioExponente, std::vector<int> binarioFlotante)
{
    std::vector<int> binarioIEEE;
    
    binarioExponente.insert(binarioExponente.begin(), signo);
    
    for (int i = binarioFlotante.size() - 1; i > -1; i--)
    {
        binarioIEEE.insert(binarioIEEE.begin(), binarioFlotante[i]);
    }
    
    for (int i = binarioExponente.size() - 1; i > -1; i--)
    {
        binarioIEEE.insert(binarioIEEE.begin(), binarioExponente[i]);
    }
    
    return binarioIEEE;
}

std::vector<int> convertirABinarioIEEE(float numeroGeneral)
{
   //------------------------- PARA SEPARAR INT DE FLOAT ----------------------------
   int numeroEntero = 0;
   float numeroFloat = 0;
   int signo = -1;
   
   if (numeroGeneral < 0 || numeroGeneral == -0)
   {
        numeroEntero = (int)numeroGeneral* - 1;
        numeroFloat = numeroEntero* - 1 - numeroGeneral;
        signo = 1;
   }
   
   else
   {
       numeroEntero = (int)numeroGeneral;
       numeroFloat = numeroGeneral - numeroEntero;
       signo = 0;
   }
   
   //----------------------- A BINARIO -----------------------------------------------
   
   std::vector<int> binarioEntero = convertirEnteroABinario(numeroEntero);
   std::vector<int> binarioFlotante = convertirFlotanteABinario(numeroFloat);

   //--------------------------------- EXPONENTE --------------------------------
   
   std::vector<int> binarioExponente = calcularExponente(binarioEntero, binarioFlotante);
   
   if (numeroEntero == 0)
   {
       int fin = -1 * buscarUno(binarioFlotante);
       
       for(int i = 0; i < fin; i++)
       {
            binarioFlotante.erase(binarioFlotante.begin());
       }
   }
   
   else
   {
       for(int i = binarioEntero.size() - 1; i > 0 ; i--)
       {
            binarioFlotante.insert(binarioFlotante.begin(), binarioEntero[i]);
       }
   }
   
   // -------------------------------------------------------------------------------
   
   binarioFlotante = redondearBinarioFlotante(binarioFlotante);
   std::vector<int> binarioIEEE = juntarTodo (signo, binarioExponente, binarioFlotante);
   printAll(binarioIEEE);
   
   return binarioIEEE;
}

//--------------------------------- DIVIDIR FLOTANTES ---------------------------------

int definirSigno(int signoA, int signoB)
{
    if (signoA == signoB)
    {
        return 0;
    }
    
    else if (signoA != signoB)
    {
        return 1;
    }
    
    return 1;
}

int convertirAEntero(std::vector<int> A)
{
    int cont = 0;

    for(int i = 0; i < A.size(); i++)
    {
        if(A[i] == 1)
        {
            int exponente = A.size() - 1 -i;
            int resultado = 1 << exponente;
            cont = cont + resultado;
        }
    }
    return cont;
}

int restarExponentes (std::vector<int> A,std::vector<int> B)
{
    int exponenteA = convertirAEntero(A);
    int exponenteB = convertirAEntero(B);
    int resultadoResta = exponenteA - exponenteB + 127;
    
    if (resultadoResta < 0)
    {
        return -1;
    }
    
    else if (resultadoResta > 255)
    {
        return -2;
    }
    
    return resultadoResta;
}

int compararBinarios (std::vector<int> A, std::vector<int> B)
{
    int i = 0;
    while(i < A.size())
    {
        if((A[i] == 1) && (B[i] == 0))
        {
            //std::cout <<  "     A mayor que B, ambos se restan, Cociente = 1     " << std::endl;
            //print(A);
            return 1;
        }
        
        else if((A[i] == 0) && (B[i] == 1))
        {
            //std::cout <<  "     B mayor que A, se agrega un 0, Cociente = 0     " << std::endl;
            //print(B);
            return 2;
        }
        
        i++;
    }
    //std::cout <<  "     A es Igual que B, Cociente = 1" << std::endl;
    return 3;
}

std::vector<int> restarBinarios(std::vector<int> A, std::vector<int> B)
{
    std::vector<int> resultado;
    
    for (int i = A.size()-1; i > -1; i--)
    {
        if ( ((A[i] == 0) && (B[i] == 0)) || ((A[i] == 1) && (B[i] == 1)) )
        {
            //std::cout <<  "Normalito A y B iguales" << std::endl;
            resultado.insert(resultado.begin(), 0);
        }
        
        else if ((A[i] == 1) && (B[i] == 0))
        {
            //std::cout <<  "Normalito A = 1 y B = 0" << std::endl;
            resultado.insert(resultado.begin(), 1);
        }
        
        else if ((A[i] == 0) && (B[i] == 1))
        {
            //std::cout <<  "Anormal" << std::endl;
            if ((A[i - 1] == 1) && (B[i - 1] == 0)) 
            {
                resultado.insert(resultado.begin(), 1);
                A[i - 1] = 0;
            }
            
            else 
            {
                resultado.insert(resultado.begin(), 1);
                int l = i;
                while (A[l] != 1)
                {
                    A[l] = 1;
                    l--;
                }
                
                A[l] = 0;
            }
            
        }
    }
    
    //print(resultado);
    return resultado;
}

std::vector<int> dividirMatisas(std::vector<int> dividendo, std::vector<int> divisor)
{
    std::vector<int> cociente;
    
    dividendo.insert(dividendo.begin(), 1);
    divisor.insert(divisor.begin(), 1);
    int limite = divisor.size();
    
    for (int i = 0; i < limite; i++)
    {
        //std::cout << std::endl;
        //std::cout << "  Ciclo n: " << i << std::endl;
        int l = compararBinarios(dividendo,divisor);
        
        switch (l)
        {
            case 1:
            cociente.push_back(1);
            dividendo = restarBinarios(dividendo,divisor);
            dividendo.push_back(0);
            divisor.insert(divisor.begin(), 0);
            //print(dividendo);
            //print(divisor);
            break;
            
            case 2:
            cociente.push_back(0);
            dividendo.push_back(0);
            divisor.insert(divisor.begin(), 0);
            //print(dividendo);
            //print(divisor);
            break;
            
            case 3:
            cociente.push_back(1);
            //print(dividendo);
            //print(divisor);
            //return cociente;
            i = limite;
            break;
        }
    }
    
    
    cociente.erase(cociente.begin());
    cociente = redondearBinarioFlotante(cociente);
    
    //std::cout << "  RESULTADO matisa: ";
    //print(cociente);
    return cociente;
}

int recorrer(std::vector<int> A)
{
    int cont = 0;
    
    for (int i = 1; i < A.size(); i++)
    {
        cont = cont + A[i];
        //std::cout << cont << std::endl;
    }
    
    return cont;
}



void dividirBinariosFlotantes(std::vector<int> dividendo, std::vector<int> divisor)
{
    int signoDividendo = dividendo[0];
    int signoDivisor = divisor[0];
    
    int signoResultado = definirSigno(signoDividendo, signoDivisor);
    
    if ( (recorrer(dividendo) == 0) && (recorrer(divisor) == 0) )
    {
        std::cout << std::endl;
        std::cout << "  NaN :(" << std::endl;
        return ;
    }
    
    else if ( (recorrer(divisor) == 0) && (signoResultado == 1) )
    {
        std::cout << std::endl;
        std::cout << "  - Inf" << std::endl;
        return ;
    }
    
    else if ( (recorrer(divisor) == 0) && (signoResultado == 0) )
    {
        std::cout << std::endl;
        std::cout << "  Inf" << std::endl;
        return ;
    }
    
    else if ( (recorrer(divisor) == 0))
    {
        std::cout << std::endl;
        std::cout << "  Resultado = 0" << std::endl;
        return ;
    }
    
    
    std::vector<int> exponenteDividendo;
    for (int i = 1; i<9; i++)
    {
        exponenteDividendo.push_back(dividendo[i]);
    }
    std::vector<int> matisaDividendo;
    for (int i = 9; i<dividendo.size(); i++)
    {
        matisaDividendo.push_back(dividendo[i]);
    }
    
    
    std::vector<int> exponenteDivisor;
    for (int i = 1; i<9; i++)
    {
        exponenteDivisor.push_back(divisor[i]);
    }
    std::vector<int> matisaDivisor;
    for (int i = 9; i<dividendo.size(); i++)
    {
        matisaDivisor.push_back(divisor[i]);
    }
    
    int exponenteResultado = restarExponentes (exponenteDividendo, exponenteDivisor);
    //std::cout << exponenteResultado << std::endl;
    
    if (exponenteResultado == -1)
    {
        std::cout << "  UNDERFLOW :(" << std::endl;
        return ;
    }
    
    else if (exponenteResultado == -2)
    {
        std::cout << "  OVERFLOW :(" << std::endl;
        return ;
    }
    
    std::vector<int> exponenteResultadoBinario = convertirEnteroABinario(exponenteResultado);
    if (exponenteResultadoBinario.size() < 8)
    {
       int falta = 8 - exponenteResultadoBinario.size();
       
       for(int i = 0; i < falta; i++)
       {
            exponenteResultadoBinario.insert(exponenteResultadoBinario.begin(), 0);
       }
    }
    
    
    
    std::vector<int> matisaResultado = dividirMatisas(matisaDividendo, matisaDivisor);
    std::vector<int> resultadoGeneral = juntarTodo (signoResultado, exponenteResultadoBinario, matisaResultado);
    
    std::cout << std::endl;
    std::cout << "  RESULTADO: ";
    printAll(resultadoGeneral);
    
    return;
}

int main()
{
    float dividendo = -04.455;
    float divisor = -0.0;
    
    std::cout << std::endl;
    std::cout << "  DIVIDENDO: " << dividendo ; 
    std::vector<int> dividendoBinario = convertirABinarioIEEE(dividendo);
    std::cout << std::endl;
    
    std::cout << std::endl;
    std::cout << "  DIVISOR: " << divisor;
    std::vector<int> divisorBinario = convertirABinarioIEEE(divisor);
    std::cout << std::endl;
    dividirBinariosFlotantes(dividendoBinario, divisorBinario);
    std::cout << std::endl;
    
    std::cout << "  RESULTADO: " << dividendo / divisor << std::endl;

    

    return 0;
}
