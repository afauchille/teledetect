#include <stdio.h>
#include <gtk/gtk.h>

/*******************************************************
IL EST FORMELLEMENT INTERDIT DE CHANGER LE PROTOTYPE
DES FONCTIONS
*******************************************************/


/*---------------------------------------
  Proto: 

  
  But: 

  Entrees: 
          --->le tableau des valeurs des pixels de l'image d'origine
	      (les lignes sont mises les unes à la suite des autres)
	  --->le nombre de lignes de l'image,
	  --->le nombre de colonnes de l'image,
          --->le tableau des valeurs des pixels de l'image resultat
	      (les lignes sont mises les unes à la suite des autres)


  Sortie:

  Rem: 

  Voir aussi:

  ---------------------------------------*/

#define VEC(V) {V, V, V, V, V}
#define SQ(X) (X) * (X)
#define NB_CLASS 5
#define GET(p, i, j, w) p[(j) * w + i]

double dist(unsigned char v1[5], unsigned char v2[5])
{
  double res = 0;
  for (int i = 0; i < 5; ++i)
    res += SQ(v1[i] - v2[i]);
  return res;
}

int getNeighbour(unsigned char v[5], unsigned char c[NB_CLASS][5])
{
  int minI = -1;
  double minDist = 1e10;

  double d;
  for (int i = 0; i < NB_CLASS; ++i)
  {
    d = dist(v, c[i]);
    if (d < minDist)
    {
      minDist = d;
      minI = i;
    }
  }

  return minI;
}

void ComputeImage(guchar *pucImaOrig, 
		  int NbLine,
		  int NbCol, 
		  guchar *pucImaRes)
{
  int iNbPixelsTotal, iNumPix;
  int iNumChannel, iNbChannels=3; /* on travaille sur des images couleurs*/
  guchar ucMeanPix;

  printf("Segmentation de l'image.... A vous!\n");

  unsigned char c[NB_CLASS][5] = {VEC(255), VEC(255 * 3/4), VEC(255 * 2/4), VEC(255 * 1/4), VEC(0)};

  iNbPixelsTotal=NbCol*NbLine;
  for(iNumPix=0;
      iNumPix<iNbPixelsTotal*iNbChannels;
      iNumPix=iNumPix+iNbChannels){
    /*moyenne sur les composantes RVB */
    ucMeanPix=(unsigned char)
	((
	  *(pucImaOrig+iNumPix) +
	  *(pucImaOrig+iNumPix+1) +
	  *(pucImaOrig+iNumPix+2))/3);

    /* sauvegarde du resultat */
    for(iNumChannel=0;
	iNumChannel<iNbChannels;
	iNumChannel++)
      *(pucImaRes+iNumPix+iNumChannel)= ucMeanPix;
  }

  unsigned char v[5] = VEC(200);

  unsigned int res[5] = VEC(0);

  int n = 0;
  // We omit bordel pixels
  for (int j = 1; j < NbLine - 1; j += iNbChannels)
  {
    for (int i = 1; i < NbCol - 1; i += iNbChannels)
      {
	v[0] = GET(pucImaRes, i, j - 1, NbCol);
	v[1] = GET(pucImaRes, i - 1, j, NbCol);
	v[2] = GET(pucImaRes, i, j, NbCol);
	v[3] = GET(pucImaRes, i + 1, j, NbCol);
	v[4] = GET(pucImaRes, i, j + 1, NbCol);

	int iClass = getNeighbour(v, c);
	res[iClass] += 1;
	n += 1;
      }
  }

  printf("%d pixels analyzed.\nResults:\n", n);
  for (int i = 0; i < NB_CLASS; ++i)
    printf("Class %u: %d\n", i, res[i]);
}

