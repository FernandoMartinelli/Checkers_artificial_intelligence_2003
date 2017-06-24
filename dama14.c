#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mt.c" // inclui o Mersenne Twister

//#define PECA1 (-72)
//#define PECA2 (-87)
#define PECA1 (99)
#define PECA2 (114)
#define DAMA1 (67)
#define DAMA2 (82)
#define BRANCO1 (-78)
#define BRANCO2 (-80)

char superdama;
int profundidademinimax;
int profundidademinimax_;

char *** trajetoriasquecomemporpeca(char ** tabuleiro, char turno, char * posicao, char comdama);

int gerarAleatorio(int mod)
{
   return genrand() %(mod);
}

char maiusc(char i)
{
   char a;
   a = i;
   if ((a >= 97)  &&  (a <= 122))
   {
      a -= 32;
   }
   return a;
}

////////////////Turno/////////////////////////////////

char pecadoturno(char turno)
{
   char result;
   if (turno == 0)
   {
      result = PECA1;
   }
   else
   {
      result = PECA2;
   }
   return result;
}

char damadoturno(char turno)
{
   char result;
   if (turno == 0)
   {
      result = DAMA1;
   }
   else
   {
      result = DAMA2;
   }
   return result;
}

////////////////Posicao///////////////////////////////

char * criarposicao(int linha, int coluna)
{
   char * result;
   result = (char *)malloc(2 * sizeof(char));
   result[0] = linha;
   result[1] = coluna;
   return result;
}

void destruirposicao(char * posicao)
{
   free(posicao);
}

char * copiarposicao(char * posicao)
{
   char * result;
   result = (char *)malloc(2 * sizeof(char));
   result[0] = posicao[0];
   result[1] = posicao[1];
   return result;
}

////////////////Trajetoria/////////////////////////////

char ** criartrajetoria()
{
   char ** result;
   result = (char **)malloc(sizeof(char *));
   result[0] = NULL;
   return result;
}

void destruirtrajetoria(char ** trajetoria)
{
   int i;
   for (i = 0; trajetoria[i] != NULL; i++)
   {
      free(trajetoria[i]);
   }
   free(trajetoria);
}

int tamanhodetrajetoria(char ** trajetoria)
{
   int i;
   for (i = 0; trajetoria[i] != NULL; i++)
   {
      
   }
   return i;
}

char ** copiartrajetoria(char ** trajetoria)
{
   char ** result;
   int s, i;
   
   s = tamanhodetrajetoria(trajetoria);
   result = (char **)malloc((s + 1) * sizeof(char *));
   result[s] = NULL;
   for (i = 0; i < s; i++)
   {
      result[i] = (char *)malloc(2 * sizeof(char));
      result[i][0] = trajetoria[i][0];
      result[i][1] = trajetoria[i][1];
   }
   return result;
}

char ** aumentartrajetoria(char ** trajetoria, char * posicao)
{
   int s;
   char ** result;

   s = tamanhodetrajetoria(trajetoria);
   trajetoria[s] = posicao;
   s++;
   result = (char **)realloc(trajetoria,  (s + 1) * sizeof(char *));
   result[s] = NULL;
   return result;
}

char ** textoparatrajetoria(char * texto)
{
   int i, linha, coluna;
   char * posicao, ** result;
   
   result = criartrajetoria();
   for (i = 0; texto[i] != 0; i = i + 2)
   {
      linha = texto[i + 1] - 49;
      coluna = maiusc(texto[i]) - 65;
      posicao = criarposicao(linha, coluna);
      result = aumentartrajetoria(result, posicao);
   }
   return result;
}

char * trajetoriaparatexto(char ** trajetoria)
{
   int i, s;
   char * result;
   
   s = tamanhodetrajetoria(trajetoria);
   result = (char *)malloc((2 * s + 1) * sizeof(char));
   result[2 * s] = 0;
  
   for (i = 0; trajetoria[i] != NULL; i++)
   {
      result[2 * i + 1] = trajetoria[i][0] + 49;
      result[2 * i] = trajetoria[i][1] + 65;
   }
   return result;
}

////////////////Trajetorias//////////////////////////////////////

char *** criartrajetorias()
{
   char *** result;
   result = (char ***)malloc(sizeof(char **));
   result[0] = NULL;
   return result;
}

void destruirtrajetorias(char *** trajetorias)
{
   int i;
   if (trajetorias != NULL)
   {
      for (i = 0; trajetorias[i] != NULL; i++)
      {
         destruirtrajetoria(trajetorias[i]);
      }
      free(trajetorias);
   }
}

int tamanhodetrajetorias(char *** trajetorias)
{
   int i;
   for (i = 0; trajetorias[i] != NULL; i++)
   {
      
   }
   return i;
}

char *** copiartrajetorias(char *** trajetorias)
{
   char *** result;
   int s, i;
   
   s = tamanhodetrajetorias(trajetorias);
   result = (char ***)malloc((s + 1) * sizeof(char **));
   result[s] = NULL;
   for (i = 0; i < s; i++)
   {
      result[i] = copiartrajetoria(trajetorias[i]);
   }
   return result;
}

char *** aumentartrajetorias(char *** trajetorias, char ** trajetoria)
{
   char *** result;
   int s;

   s = tamanhodetrajetorias(trajetorias);
   trajetorias[s] = trajetoria;
   s++;
   result = (char ***)realloc(trajetorias,  (s + 1) * sizeof(char **));
   result[s] = NULL;
   return result;
}

char *** concatenartrajetorias(char *** trajetorias1, char *** trajetorias2)
{
   char *** result;
   int i, s1, s2;
   
   s1 = tamanhodetrajetorias(trajetorias1);
   s2 = tamanhodetrajetorias(trajetorias2);
   
   if (s1 == 0)
     return copiartrajetorias(trajetorias2);
   
   if (s2 == 0)
      return copiartrajetorias(trajetorias1);

   result = (char ***)malloc((s1 + s2 + 1) * sizeof(char **));
   result[s1 + s2] = NULL;
   for (i = 0; i < s1; i++)
   {
      result[i] = copiartrajetoria(trajetorias1[i]);
   }
   for (i = 0; i < s2; i++)
   {
      result[i + s1] = copiartrajetoria(trajetorias2[i]);
   }
   return result;
}

char emtrajetorias(char *** trajetorias, char ** trajetoria)
{
   char result, trajetoriaigual;
   int i, j;
   
   result = 0;
   for (i = 0; trajetorias[i] != NULL; i++)
   {
      trajetoriaigual = 1;
      for (j = 0; trajetorias[i][j] != NULL && trajetoria[j] != NULL; j++)
      {
         if ((trajetorias[i][j][0] != trajetoria[j][0]) || (trajetorias[i][j][1] != trajetoria[j][1]))
         {
            trajetoriaigual = 0;
            break;
         }
      }
      if (trajetoriaigual == 1)
      {
         if (tamanhodetrajetoria(trajetorias[i]) != tamanhodetrajetoria(trajetoria))
         {
            trajetoriaigual = 0;
         }
      }
      if (trajetoriaigual == 1)
      {
         result = 1;
         break;
      }
   }
   
   return result;
}

void mostrartrajetorias(char *** trajetorias)
{
   int i;
   for (i = 0; trajetorias[i] != NULL; i++)
   {
      printf("Trajetoria %d: %s.\n", i, trajetoriaparatexto(trajetorias[i]));
   }
}

/////////////////Tabuleiro/////////////////////////

char ** criartabuleiro()
{
   int i, j;
   char ** tabuleiro;

   tabuleiro = (char **)malloc(8 * sizeof(char *));
   for (i = 0; i < 8; i++)
   {
      tabuleiro[i] = (char *)malloc(sizeof(char));
      for (j = 0; j < 8; j++)
      {
         if ((((i + j) % 2) == 1) && (i < 3))
         {
            tabuleiro[i][j] = PECA1;
         }
         if ((((i + j) % 2) == 1) && (i > 4))
         {
            tabuleiro[i][j] = PECA2;
         }
         if ((((i + j) % 2) == 1) && ((i > 2) && (i < 5)))
         {
            tabuleiro[i][j] = BRANCO1;
         }
         if (((i + j) % 2) == 0)
         {
            tabuleiro[i][j] = BRANCO2;
         }
      }
   }
   return tabuleiro;
}

void destruirtabuleiro(char ** tabuleiro)
{
   int i, j;

   for (i = 0; i < 8; i++)
   {
      free(tabuleiro[i]);
   }
   free(tabuleiro);
}

char ** copiartabuleiro(char ** tabuleiro)
{
   int i, j;
   char ** result;

   result = (char **)malloc(8 * sizeof(char *));
   for (i = 0; i < 8; i++)
   {
      result[i] = (char *)malloc(sizeof(char));
      for (j = 0; j < 8; j++)
      {
         result[i][j] = tabuleiro[i][j];
      }
   }
   return result;
}

void executartrajetoria(char ** tabuleiro, char ** trajetoria)
{
   int i, k, l, m, n;
   
   for (i = 0; trajetoria[i + 1] != NULL; i++)
   {
      k = trajetoria[i][0];
      l = trajetoria[i][1];
      m = trajetoria[i + 1][0];
      n = trajetoria[i + 1][1];
      tabuleiro[m][n] = tabuleiro[k][l];
      tabuleiro[k][l] = BRANCO1;
      if (abs(m - k) > 1)
      {
         tabuleiro[m - ((m - k) / abs(m - k))][n - ((n - l) / abs(n - l))] = BRANCO1;
      }
   }
   if ((trajetoria[i][0] == 7) && (tabuleiro[trajetoria[i][0]][trajetoria[i][1]] == PECA1))
   {
      tabuleiro[trajetoria[i][0]][trajetoria[i][1]] = DAMA1;
   }
   if ((trajetoria[i][0] == 0) && (tabuleiro[trajetoria[i][0]][trajetoria[i][1]] == PECA2))
   {
      tabuleiro[trajetoria[i][0]][trajetoria[i][1]] = DAMA2;
   }
}

int valordotabuleiro (char ** tabuleiro, char turno, int pesodapeca, int pesodadama)
{
   char i, j, pecaAmiga, pecaInimiga, damaAmiga, damaInimiga;
   int k = 0;

   pecaAmiga = pecadoturno(turno);  damaAmiga = damadoturno(turno);
   pecaInimiga = pecadoturno(1 - turno);  damaInimiga = damadoturno(1 - turno);
   for (i = 0; i < 8; i++)
      for (j = 0; j < 8; j++)
      {
         if (tabuleiro[i][j] == pecaAmiga) k = k + pesodapeca; if (tabuleiro[i][j] == damaAmiga) k = k + pesodadama;
         if (tabuleiro[i][j] == pecaInimiga) k = k - pesodapeca; if (tabuleiro[i][j] == damaInimiga) k = k - pesodadama;
      }
   return k;
}

void mostrartabuleiro(char ** tabuleiro)
{
   int i, j;
   
   printf("\n  A B C D E F G H\n\n");
   for (i = 0; i < 8; i++)
   {
      printf("%d ", i +1);
      for (j = 0; j < 8; j++)
      {
         printf("%c ", tabuleiro[i][j]);
      }
      printf("%d", i +1);
      printf("\n\n");
   }
   printf("  A B C D E F G H\n\n");
}

////////////////Verificacao das trajetorias////////////////////////

char ** pecas(char ** tabuleiro, char turno)
{
   char ** result;
   int i, j;

   result = criartrajetoria();
   for (i = 0; i < 8; i++)
   {
      for (j = 0; j < 8; j++)
      {
         if (((i + j) % 2) == 1)
         {
            if (((tabuleiro[i][j] == pecadoturno(turno)) || (tabuleiro[i][j] == damadoturno(turno))))
            {
               result = aumentartrajetoria(result, criarposicao(i, j));
            }
         }
      }
   }
   return result;
}

////////////////Verificacao das trajetorias que comem////////////////////////

char *** desenvolvertrajetorias_(char ** tabuleiro, char turno, char *** trajetorias, int * i)
{
   char *** result, ** trajetoria, *** trajetoriasadj, ** tab;
   int s, j, t;

   result = trajetorias;
   trajetoria = copiartrajetoria(result[*i]);
   s = tamanhodetrajetoria(result[*i]);
   trajetoriasadj = trajetoriasquecomemporpeca(tabuleiro, turno, result[*i][s - 1], 0);
   
   for (j = 0; trajetoriasadj[j] != NULL; j++)
   {
      if (j == 0)
      {
         tab = copiartabuleiro(tabuleiro);
         executartrajetoria(tab, trajetoriasadj[j]);
         result[*i] = aumentartrajetoria(result[*i], copiarposicao(trajetoriasadj[j][1]));
         result = desenvolvertrajetorias_(tab, turno, result, i);
         destruirtabuleiro(tab);
      }
      else
      {
         result = aumentartrajetorias(result, copiartrajetoria(trajetoria));
         t = *i;
         *i = tamanhodetrajetorias(result) - 1;
         
         tab = copiartabuleiro(tabuleiro);
         executartrajetoria(tab, trajetoriasadj[j]);
         result[*i] = aumentartrajetoria(result[*i], copiarposicao(trajetoriasadj[j][1]));
         result = desenvolvertrajetorias_(tab, turno, result, i);
         destruirtabuleiro(tab);
         
         *i = t;
      }
   }
   destruirtrajetorias(trajetoriasadj);
   destruirtrajetoria(trajetoria);
   
   return result;
}

char *** trajetoriasquecomemporpeca(char ** tabuleiro, char turno, char * posicao, char analisartodatrajetoria)
{  
   char *** result, *** oldresult, *** trajetorias, ** trajetoria, * posicao1, * posicao2, ** tab;
   int i, j, a, alpha, beta, w;
   
   result = criartrajetorias();
   for (j = 0; j < 4; j++)
   {
      switch (j)
      {
         case 0:
            alpha = 1;
            beta = 1;
         break;
         case 1:
            alpha = 1;
            beta = -1;
         break;
         case 2:
            alpha = -1;
            beta = 1;
         break;
         case 3:
            alpha = -1;
            beta = -1;
         break;
      }
      
      a = 0;
      for (i = 1;  a == 0; i++)
      {
         if (((posicao[0] + (i + 1) * alpha) * alpha < (3.5 + 4.5 * alpha) * alpha) && ((posicao[1] + (i + 1) * beta) * beta < (3.5 + 4.5 * beta) * beta))
         {
            if ((tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == pecadoturno(1 - turno)) || (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == damadoturno(1 - turno)))
            {
               if (tabuleiro[posicao[0] + (i + 1) * alpha][posicao[1] + (i + 1) * beta] == BRANCO1)
               {
                  posicao1 = criarposicao(posicao[0], posicao[1]);
                  posicao2 = criarposicao(posicao[0] + (i + 1) * alpha, posicao[1] + (i + 1) * beta);
                  trajetoria = criartrajetoria();
                  trajetoria = aumentartrajetoria(trajetoria, posicao1);
                  trajetoria = aumentartrajetoria(trajetoria, posicao2);
                  trajetorias = criartrajetorias();
                  trajetorias = aumentartrajetorias(trajetorias, trajetoria);
                  if (analisartodatrajetoria == 1)
                  {
                     tab = copiartabuleiro(tabuleiro);
                     executartrajetoria(tab, trajetoria);
                     w = 0;
                     trajetorias = desenvolvertrajetorias_(tab, turno, trajetorias, &w);
                     destruirtabuleiro(tab);
                  }

                  oldresult = result;
                  result = concatenartrajetorias(result, trajetorias);
                  destruirtrajetorias(oldresult);
                  destruirtrajetorias(trajetorias);
               }
               a = 1;  //comeu uma peca
            }
            if (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == pecadoturno(turno) || tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == damadoturno(turno))
            {
               a = 1;  //encontrou uma peca amiga
            }
            if (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == pecadoturno(1 - turno) || tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == damadoturno(1 - turno))
            {
               a = 1;  //encontrou uma peca inimiga
            }
         }
         else
         {
            a = 1;  //acabou o tabuleiro
         }
         if (tabuleiro[posicao[0]][posicao[1]] == pecadoturno(turno))
         {
            a = 1;  //peca naum eh dama
         }
         else
         {
            if ((analisartodatrajetoria == 0) && (superdama == 0))
            {
               a = 1;  //segundo movimento de uma dama(no modo normal)
            }
         }
      }
   }      
   return result;
}

char *** trajetoriasquecomem(char ** tabuleiro, char turno)
{
   char *** result, *** oldresult, *** trajetorias, ** pecas_;
   int j;
   
   result = criartrajetorias();
   pecas_ = pecas(tabuleiro, turno);
   for (j = 0; pecas_[j] != NULL; j++)
   {    
      trajetorias = trajetoriasquecomemporpeca(tabuleiro, turno, pecas_[j], 1);
      oldresult = result;
      result = concatenartrajetorias(result, trajetorias);
      destruirtrajetorias(oldresult);
      destruirtrajetorias(trajetorias);
   }
   destruirtrajetoria(pecas_);
   return result;
}

////////////////Verificacao das trajetorias normais////////////////////////

char *** trajetoriasnormaisporpeca(char ** tabuleiro, char turno, char * posicao)
{  
   char *** result, *** oldresult, *** trajetorias, ** trajetoria, * posicao1, * posicao2, ** tab, peca;
   int i, j, a, alpha, beta;
   
   result = criartrajetorias();
   for (j = 0; j < 4; j++)
   {
      switch (j)
      {
         case 0:
            alpha = 1;
            beta = 1;
         break;
         case 1:
            alpha = 1;
            beta = -1;
         break;
         case 2:
            alpha = -1;
            beta = 1;
         break;
         case 3:
            alpha = -1;
            beta = -1;
         break;
      }
      
      a = 0;
      for (i = 1;  a == 0; i++)
      {
         if ((posicao[0] * alpha + i < 3.5 * alpha + 4.5) && (posicao[1] * beta + i < 3.5 * beta + 4.5))
         {
            if (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == BRANCO1)
            {
               peca = tabuleiro[posicao[0]][posicao[1]];
               if ((peca == DAMA1) || (peca == DAMA2) || ((peca == PECA1) && (alpha > 0)) || ((peca == PECA2) && (alpha < 0)))
               {
                  posicao1 = criarposicao(posicao[0], posicao[1]);
                  posicao2 = criarposicao(posicao[0] + i * alpha, posicao[1] + i * beta);
                  trajetoria = criartrajetoria();
                  trajetoria = aumentartrajetoria(trajetoria, posicao1);
                  trajetoria = aumentartrajetoria(trajetoria, posicao2);
                  trajetorias = criartrajetorias();
                  trajetorias = aumentartrajetorias(trajetorias, trajetoria);
                  oldresult = result;
                  result = concatenartrajetorias(result, trajetorias);
                  destruirtrajetorias(oldresult);
                  destruirtrajetorias(trajetorias);
               }
            }
            if (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == pecadoturno(turno) || tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == damadoturno(turno))
            {
               a = 1;
               //encontrou uma peca amiga
            }
            if (tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == pecadoturno(1 - turno) || tabuleiro[posicao[0] + i * alpha][posicao[1] + i * beta] == damadoturno(1 - turno))
            {
               a = 1;
               //encontrou uma peca inimiga
            }
         }
         else
         {
            a = 1;
            //acabou o tabuleiro
         }
         if (tabuleiro[posicao[0]][posicao[1]] == pecadoturno(turno))
         {
            a = 1;
            //peca naum eh dama
         }
      }
   }      
   return result;
}

char *** trajetoriasnormais(char ** tabuleiro, char turno)
{
   char *** result, *** oldresult, *** trajetorias, ** pecas_;
   int j;
   
   result = criartrajetorias();
   pecas_ = pecas(tabuleiro, turno);
   for (j = 0; pecas_[j] != NULL; j++)
   {    
      trajetorias = trajetoriasnormaisporpeca(tabuleiro, turno, pecas_[j]);
      oldresult = result;
      result = concatenartrajetorias(result, trajetorias);
      destruirtrajetorias(oldresult);
      destruirtrajetorias(trajetorias);
   }  
   destruirtrajetoria(pecas_);   
   return result;
}

////////////////Verificacao das trajetorias validas////////////////////////

char *** trajetoriasvalidas(char ** tabuleiro, char turno)
{
   char *** result, *** trajetoriasquecomem_;
   int i, g, h;
   trajetoriasquecomem_ = trajetoriasquecomem(tabuleiro, turno);
   h = 0;
   for (i = 0; trajetoriasquecomem_[i] != NULL; i++)
   {
      g = tamanhodetrajetoria(trajetoriasquecomem_[i]);
      if (g > h)
      {
         h = g;
      }
   }
   if (h > 0)
   {
      result = criartrajetorias();
      for (i = 0; trajetoriasquecomem_[i] != NULL; i++)
      {
         g = tamanhodetrajetoria(trajetoriasquecomem_[i]);
         if (g == h)
         {
            result = aumentartrajetorias(result, copiartrajetoria(trajetoriasquecomem_[i]));
         }
      }
   }
   else
   {
      result = trajetoriasnormais(tabuleiro, turno);
   }
   destruirtrajetorias(trajetoriasquecomem_);
   
   return result;
}

//////////////////////Inteligencia artificial///////////////////////////////////

int testartrajetoria(char ** tabuleiro, char turno, char ** trajetoria, int alpha, int * i, int p, int d)
{
   char ** tab, *** trajetoriasvalidas_;
   int j, result, k;
   
   result = 0;
   *i = *i + 1;
   tab = copiartabuleiro(tabuleiro);
   executartrajetoria(tab, trajetoria);
   
   if (*i < alpha)
   {
      
      trajetoriasvalidas_ = trajetoriasvalidas(tab, turno);
      if (*i % 2 == 1)
      {
         result = 1000;
      }
      else
      {
         result = -1000;
      }
      
      for (j = 0; trajetoriasvalidas_[j] != NULL; j++)
      {
         k = testartrajetoria(tab, 1 - turno, trajetoriasvalidas_[j], alpha, i, p, d);
         if (*i % 2 == 1)
         {  
            if (k < result) //sempre procura minimizar os pontos
            {
               result = k;
            }
         }
         else
         {
            if (k > result) //sempre procura maximizar os pontos
            {
               result = k;
            }
         }
      }
      if (j == 0)
      {
         if (*i % 2 == 1)
         {
            result = - valordotabuleiro(tab, turno, p, d);
         }
         else
         {
            result = valordotabuleiro(tab, turno, p, d);
         }
      }
      
      destruirtrajetorias(trajetoriasvalidas_);
   }
   else
   {
     if (*i % 2 == 1)
     {
       result = - valordotabuleiro(tab,turno, p, d);
     }
     else
     {
       result = valordotabuleiro(tab,turno, p, d);
     }
   }
   
   destruirtabuleiro(tab);
   *i = *i - 1;
   return result;
}

char ** melhortrajetoria(char ** tabuleiro, char turno)
{
   int i, k, g, h;
   char ** result, *** trajetoriasvalidas_, *** trajetoriasmelhores;
      
   trajetoriasvalidas_ = trajetoriasvalidas(tabuleiro, turno);
   trajetoriasmelhores = criartrajetorias();
   h = -100;
   for (i = 0; trajetoriasvalidas_[i] != NULL; i++)
   {
      k = 0;
      g = testartrajetoria(tabuleiro, 1 - turno, trajetoriasvalidas_[i], profundidademinimax, &k, 1 + superdama, 2 + superdama);
      printf("Trajetoria %d: %d\n", i, g);
      if (g == h)
      {
         trajetoriasmelhores = aumentartrajetorias(trajetoriasmelhores, copiartrajetoria(trajetoriasvalidas_[i]));
      }
      if (g > h)
      {
         h = g;
         destruirtrajetorias(trajetoriasmelhores);
         trajetoriasmelhores = criartrajetorias();
         trajetoriasmelhores = aumentartrajetorias(trajetoriasmelhores, copiartrajetoria(trajetoriasvalidas_[i]));
      }
   }
   i = gerarAleatorio(tamanhodetrajetorias(trajetoriasmelhores));
   result = copiartrajetoria(trajetoriasmelhores[i]);
   destruirtrajetorias(trajetoriasmelhores);
   destruirtrajetorias(trajetoriasvalidas_);

   return result;
}

char ** trajetoriaAleatoria(char ** tabuleiro, char turno)
{
   char *** trajetoriasValidas, ** trajetoriaEscolhida;
   int a;
   trajetoriasValidas = trajetoriasvalidas(tabuleiro, turno);
   a = gerarAleatorio(tamanhodetrajetorias(trajetoriasValidas));
   trajetoriaEscolhida = copiartrajetoria(trajetoriasValidas[a]);
   destruirtrajetorias(trajetoriasValidas);
   return trajetoriaEscolhida;
}

char ** vamosParaADireita(char ** tabuleiro, char turno)
{
   int a;
   char *** trajetoriasValidas, *** trajetoriasQueVaoParaADireita, ** trajetoriaEscolhida, s, t;
   trajetoriasValidas  = trajetoriasvalidas(tabuleiro, turno);
   trajetoriasQueVaoParaADireita = criartrajetorias();
   for(s = 0; trajetoriasValidas[s] != NULL; s++)
   {
      for(t = 0; trajetoriasValidas[s][t] != NULL; t++) ;
      if (trajetoriasValidas[s][t - 1][1] > trajetoriasValidas[s][1][1])
         aumentartrajetorias(trajetoriasQueVaoParaADireita, copiartrajetoria(trajetoriasValidas[s]));
   }
   if (tamanhodetrajetorias(trajetoriasQueVaoParaADireita) > 0)
   {
      a = gerarAleatorio(tamanhodetrajetorias(trajetoriasQueVaoParaADireita));
      trajetoriaEscolhida = copiartrajetoria(trajetoriasQueVaoParaADireita[a]);
   }
   else
   {
      a = gerarAleatorio(tamanhodetrajetorias(trajetoriasValidas));
      trajetoriaEscolhida = copiartrajetoria(trajetoriasValidas[a]);
   }      
   destruirtrajetorias(trajetoriasQueVaoParaADireita);
   destruirtrajetorias(trajetoriasValidas);
   return trajetoriaEscolhida;
}

int main(int argc, char ** argv)
{
	char turno, ** tabuleiro, *** trajetoriasvalidas_, ***historico, ** trajetoria, * texto;
   char jogoacabou, trajetoriavalida;
   int i, semente, jogadasparadas, numerodepecas, numerodepecasanterior;
   char jogadores, pec, sujeira, x, comp1 = PECA2, comp2 = PECA2, ia;
   char ** (*inteligencia1) (char **, char);
   char ** (*inteligencia2) (char **, char);
   
   int VC = 0, VR = 0, EP = 0;
   
   printf("\n\nJogo de damas versao 0.8.12659\n\n");
   printf("Jogar com super dama? (S / *): "); scanf("%c", &x);  x = maiusc(x);
   if (x == 'S') 
   {
      superdama = 1;
      printf("\nAssumindo modo de jogo Super Dama!\n\n");
   }
   else
   {
      superdama = 0;
      printf("\nAssumindo modo de jogo normal\n\n");
   }
  
   for(jogadores = -1; jogadores < 0 || jogadores > 2;)
   {
      printf("Numero de jogadores externos: ");
      scanf("%d",&jogadores); printf("\nAssumindo %d\n", jogadores);
      if (jogadores == 0)
      {
         comp1 = PECA1;
         comp2 = PECA2;
      }
      else 
      {
         if (jogadores == 1)
         {
            tabuleiro = criartabuleiro();
            mostrartabuleiro(tabuleiro);
            destruirtabuleiro(tabuleiro);
            for (pec = 0; pec != 'A' && pec != 'B';)
            {
               printf("\nCom que pecas voce mais profundamente deseja jogar?\n");
               printf("\n(A)  Pecas do tipo %c", PECA1);
               printf("\n(B)  Pecas do tipo %c\n", PECA2);
               scanf("%c %c", &sujeira, &pec);   pec = maiusc(pec);
            }
            if (pec == 'A') {comp1 = PECA2; comp2 = PECA2;}
            if (pec == 'B') {comp1 = PECA1; comp2 = PECA1;}
         }
      
         else
         {
            if (jogadores == 2)
            {
               comp1 = 0;
               comp2 = 0;
            }
            else
            {
               printf("\nO numero de jogadores externos deve ser 0, 1 ou 2\n");
            }
         }
      }
   }
   if (comp1 == PECA1 || comp1 == PECA2)
   {
      for(ia = 0; ia != 'A' && ia != 'B' && ia != 'C'; )
      { 
         printf("\nDe que forma %c deve jogar?\n", comp1);
         printf("\n(A)  IA");
         printf("\n(B)  Aleatoriamente");
         printf("\n(C)  Vamos para a direita\n");
         
         scanf("%c %c", &sujeira, &ia); ia = maiusc(ia);
         if (ia == 'A') inteligencia1 = melhortrajetoria;
         if (ia == 'B') inteligencia1 = trajetoriaAleatoria;
         if (ia == 'C') inteligencia1 = vamosParaADireita;
      }
   }
   if (comp2 != comp1 && (comp2 == PECA1 || comp2 == PECA2))
   {
      for(ia = 0;ia != 'A' && ia != 'B' && ia != 'C';)
      { 
         printf("\nDe que forma %c deve jogar?\n", comp2);
         printf("\n(A)  IA");
         printf("\n(B)  Aleatoriamente");
         printf("\n(C)  Vamos para a direita\n");
         
         scanf("%c %c", &sujeira, &ia); ia = maiusc(ia);
         if (ia == 'A') inteligencia2 = melhortrajetoria;
         if (ia == 'B') inteligencia2 = trajetoriaAleatoria;
         if (ia == 'C') inteligencia2 = vamosParaADireita;
      }
   }
   if (inteligencia1 == melhortrajetoria || inteligencia2 == melhortrajetoria)
   {
      for(profundidademinimax = 0; profundidademinimax == 0;)
      {
         printf("\nDigite o nivel de habilidade da IA: ");
         scanf("%d", &profundidademinimax);
      }
   
   }
   if (comp1 != 0 || comp2 != 0)
   {
      for(semente = 0; semente == 0;)
      {
         printf("\nPor favor, forneca um numero inteiro diferente de zero: ");
         scanf("%d", &semente);
      }
      sgenrand(semente);
   }

   tabuleiro = criartabuleiro();
   turno = 0;
   numerodepecasanterior = valordotabuleiro(tabuleiro, turno, 1, 1);
   jogadasparadas = 0;
   jogoacabou = 0;
   historico = criartrajetorias();   
   do
   {
      mostrartabuleiro(tabuleiro);
      trajetoriasvalidas_ = trajetoriasvalidas(tabuleiro, turno);
      printf("Turno do %c.\n", pecadoturno(turno));
      printf("Trajetorias validas:\n");
      mostrartrajetorias(trajetoriasvalidas_);
    
      if (tamanhodetrajetorias(trajetoriasvalidas_) > 0)
      {
         printf("Digite uma trajetoria:\n");
         trajetoriavalida = 0;
         do
         {
            if (pecadoturno(turno) != comp1 && pecadoturno(turno) != comp2)
            {
               texto = (char *)malloc(100 * sizeof(char));
               texto[99] = 0;
               scanf(" %s", texto);
               trajetoria = textoparatrajetoria(texto);
               free(texto);
            }
            else
            {
               if (pecadoturno(turno) == comp1)
               {
                  trajetoria = (*inteligencia1)(tabuleiro, turno);
                  texto = trajetoriaparatexto(trajetoria);
                  printf("%s\n", texto);
                  free(texto);
               }
               else
               {
                  trajetoria = (*inteligencia2)(tabuleiro, turno);
                  texto = trajetoriaparatexto(trajetoria);
                  printf("%s\n", texto);
                  free(texto);
               }
            }
            trajetoriavalida = emtrajetorias(trajetoriasvalidas_, trajetoria);
            if (trajetoriavalida == 0)
            {
               printf("Trajetoria invalida. Digite uma outra trajetoria:\n");
            }
         } while (trajetoriavalida == 0);
         executartrajetoria(tabuleiro, trajetoria);
         historico = aumentartrajetorias(historico, copiartrajetoria(trajetoria));
         destruirtrajetoria(trajetoria);
         destruirtrajetorias(trajetoriasvalidas_);

         jogadasparadas++;
         numerodepecas = valordotabuleiro(tabuleiro, turno, 1, 1);
         if (numerodepecas != numerodepecasanterior)
         {
            numerodepecasanterior = numerodepecas;
            jogadasparadas = 0;
         }
         if (jogadasparadas >= 20)
         {
            jogoacabou = 1;
         }
         
         turno = 1 - turno;
      }
      else
      {
         jogoacabou = 3;
      }
   }      
   while (jogoacabou == 0);

   if (jogoacabou == 1)
   {
      printf("Fim do jogo. Nao houve vencedores.\n");
   }
   else
   {
      printf("Fim do jogo. Vencedor: %c\n", pecadoturno(1 - turno));
   }

   printf("Fazer \"replay\" da partida? (S / *):");
   scanf("%c %c", &sujeira, &x); printf("\n");
   x = 'n';
   x = maiusc(x);
   for(; x == 'S';)
   {
      destruirtabuleiro(tabuleiro);
      tabuleiro = criartabuleiro();
      turno = 0;
      scanf("%c", &sujeira);
      for(i = 0; historico[i] != NULL; i++)
      {
         mostrartabuleiro(tabuleiro);
         printf("Turno do %c.\n", pecadoturno(turno));
         printf("%s\n", trajetoriaparatexto(historico[i]));
         executartrajetoria(tabuleiro, historico[i]);
         scanf("%c", &sujeira); printf("\n");
         turno = 1 - turno;
      }
      mostrartabuleiro(tabuleiro);
      printf("Turno do %c.\n", pecadoturno(turno));
      if (jogoacabou == 1)
      {
         printf("Fim do jogo. Nao houve vencedores.\n");
      }
      else
      {
         printf("Fim do jogo. Vencedor: %c\n", pecadoturno(1 - turno));
      }
      printf("Fazer novo \"replay\" da partida? (S / *):");
      scanf("%c %c", &sujeira, &x); printf("\n");
      x = maiusc(x);
   }
   destruirtrajetorias(historico);
   destruirtabuleiro(tabuleiro);
  
	return 0;
}
