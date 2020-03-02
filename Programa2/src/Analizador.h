#pragma once
#include <string>
#include <cctype>
#include "Lector.h"
#include "Parte.h"
using namespace std;

//.b=52

class Analizador
{
    private:
        //.d=3
        bool lineaValida(string linea);
        bool stringEntreComillas(string linea, string s);
        int getAmountFromTag(string linea, int i);
        bool findTagAlone(string linea, string tag);
    public:
        //.d=2
        Parte analizarParte(Lector &lector); //.m
};

//.d=5

//.i
Parte Analizador::analizarParte(Lector &lector) //.m
{
    string linea;
    bool inMultilineComment = false, currentLineStartsMultiline = false; //.m
    int total = 0, items = 0, modificadas = 0, base = 0, borradas = 0;
    //.d=1
    while (!lector.fin())
    {   
        linea = lector.getSigLinea();
        if (inMultilineComment)
        {
            //.d=1
            if (linea.find("*/") != -1)
            {
                inMultilineComment = false;
            }
        }
        else
        {
            if ((linea.find("/*") != -1 && !stringEntreComillas(linea, "/*") )&& linea.find("*/") == -1) //.m
            {
                //.d=1
                inMultilineComment = true;

            }
            else if (findTagAlone(linea, "//.i"))
            {
                items++;
            }
            else if (linea.find("//.m") != -1 && !stringEntreComillas(linea, "//.m"))
            {
                bool atEnd = true;
                for(int i = linea.find("//.m") + 4; i < linea.length(); i++) {
                    if (!isspace(linea[i])) {
                        atEnd = false;
                    }
                }
                if(atEnd)
                    modificadas++;
            }
            else if (findTagAlone(linea, "//.b="))
            {
                base += getAmountFromTag(linea, linea.find("//.b=") + 5);
                
            }
            else if (findTagAlone(linea, "//.d="))
            {
                borradas += getAmountFromTag(linea, linea.find("//.d=") + 5);
            }
            if(lineaValida(linea))
            {
                total++;
            }
        }
    }
    Parte parte(lector.getNombre(), total, items, base, borradas, modificadas);
    return parte;
}

//.d=13

//.i
bool Analizador::stringEntreComillas(string linea, string s)
{
    int pos = linea.find(s);

    if(pos != -1){

        string izq = linea.substr(0, pos);
        string der = linea.substr(pos);

        return ((izq.find("\'") != -1 && der.find("\'") != -1) ||
                (izq.find("\"") != -1 && der.find("\"") != -1)) || izq.find("/*") != -1 && izq.find("*/") ==-1;
    }
    return false;
}

//.i
bool Analizador::lineaValida(string linea)
{
    bool bracketSemicolon = false, hayMasQueLlaves = false;
    int posComentario = linea.find("//");
    
    for(int i = 0; i < linea.length(); i++)
    {
        if(linea[i] == ';' && i > 0) {
            bracketSemicolon = linea[i-1] == '}';
        }

        if(!isspace(linea[i]) && linea[i] != '}' && linea[i] != '{' && !bracketSemicolon)
        {
            hayMasQueLlaves = true;
        }
    }

    if(!hayMasQueLlaves)
    {
        return false;
    }

    

    if(posComentario != -1 && !stringEntreComillas(linea, "//"))
    {
        for(int i = 0; i < posComentario; i++)
        {
            if(!isspace(linea[i]))
            {
                return true;
            }
        }
        return false;
    }
    else if (linea.find("/*") != -1 && !stringEntreComillas(linea, "/*")) {
        int n = linea.find("/*");
        for (int i = 0; i < n; i++)
        {
            if(!isspace(linea[i])){
                return true;
            }
        }
        return false;
    } else if (linea.find("*/") != -1 && !stringEntreComillas(linea, "*/")) {
        for(int i = linea.find("*/"); i < linea.length(); i++) {
            if(!isspace(linea[i])) {
                return true;
            }
        }
        return false;
    }
    return true;
}

//.i
int Analizador::getAmountFromTag(string linea, int i)
{
    string amountAsString = "";
    while (linea[i] >= '0' &&linea[i] <= '9') {
        amountAsString+= linea[i];
        i++;
    }
    return stoi(amountAsString);
}

//.i
bool Analizador::findTagAlone(string linea, string tag)
{
    int pos = linea.find(tag);
    if(pos != -1) {
        string izq = linea.substr(0, pos);
        for(char car:izq) {
            if(!isspace(car)){
                return false;
            }
        }
        // Pass posible numbers
        int i = pos+ tag.length();
        while (linea[i] >= '0' &&linea[i] <= '9') {
            i++;
        }
        string der = linea.substr(i);
        for(char car:der){
            if(!isspace(car)) {
                return false;
            }
        }
        return true;
    }
    return false;
}
