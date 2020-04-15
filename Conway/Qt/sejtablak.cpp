// sejtablak.cpp
//
// Életjáték rajzoló
// Programozó Páternoszter
//
// Copyright (C) 2011, B�tfai Norbert, nbatfai@inf.unideb.hu, nbatfai@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthet� illetve m�dos�that� a
// Free Software Foundation �ltal kiadott GNU General Public License
// dokumentum�ban le�rtak; ak�r a licenc 3-as, ak�r (tetsz�leges) k�s�bbi
// v�ltozata szerint.
//
// Ez a program abban a rem�nyben ker�l k�zread�sra, hogy hasznos lesz,
// de minden egy�b GARANCIA N�LK�L, az ELADHAT�S�GRA vagy VALAMELY C�LRA
// VAL� ALKALMAZHAT�S�GRA val� sz�rmaztatott garanci�t is bele�rtve.
// Tov�bbi r�szleteket a GNU General Public License tartalmaz.
//
// A felhaszn�l�nak a programmal egy�tt meg kell kapnia a GNU General
// Public License egy p�ld�ny�t; ha m�gsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.
//
//
// Version history:
//
// 0.0.1    A k�t oszt�ly tervez�s�nek f� szempontja az volt, hogy
// ne vagy alig k�l�nb�zz�n az els� C++-os p�ld�t�l, a Mandelost�l:
// http://progpater.blog.hu/2011/02/26/tan_csodallak_amde_nem_ertelek_de_kepzetem_hegyvolgyedet_bejarja
// ez�rt az olyan k�nyesebb dolgokkal, hogy kezelj�k a racsIndex-et a
// k�t oszt�lyra bontott C++ megold�sban, amikor �rjuk �t a Jav�sb�l, nem foglalkoztunk
// a kiindul� Jav�s: http://www.tankonyvtar.hu/informatika/javat-tanitok-1-2-080904-1
// (a baz�r eszme: �Release Early, Release Often" �rjuk ki a posztra)
//

#include "sejtablak.h"

SejtAblak::SejtAblak(int szelesseg, int magassag, QWidget *parent)
: QMainWindow(parent)
{
  setWindowTitle("A John Horton Conway-f�le �letj�t�k");
  
  this->magassag = magassag;
  this->szelesseg = szelesseg;

  
  cellaSzelesseg = 6;
  cellaMagassag = 6;

  setFixedSize(QSize(szelesseg*cellaSzelesseg, magassag*cellaMagassag));
  
  racsok = new bool**[2];
  racsok[0] = new bool*[magassag];
  for(int i=0; i<magassag; ++i)
    racsok[0][i] = new bool [szelesseg];
  racsok[1] = new bool*[magassag];
  for(int i=0; i<magassag; ++i)
    racsok[1][i] = new bool [szelesseg];

  racsIndex = 0;
  racs = racsok[racsIndex];

  // A kiindul� racs minden cell�ja HALOTT
  for(int i=0; i<magassag; ++i)
    for(int j=0; j<szelesseg; ++j)
      racs[i][j] = HALOTT;
    // A kiindul� racsra "ELOl�nyeket" helyez�nk
    //siklo(racs, 2, 2);

    sikloKilovo(racs, 5, 60);

  eletjatek = new SejtSzal(racsok, szelesseg, magassag, 120, this);

  eletjatek->start();
  
}

void SejtAblak::paintEvent(QPaintEvent*) {
  QPainter qpainter(this);
  
  // Az aktu�lis
  bool **racs = racsok[racsIndex];
  // racsot rajzoljuk ki:
  for(int i=0; i<magassag; ++i) { // v�gig l�pked a sorokon
    for(int j=0; j<szelesseg; ++j) { // s az oszlopok
      // Sejt cella kirajzol�sa
      if(racs[i][j] == ELO)
	qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
			  cellaSzelesseg, cellaMagassag, Qt::black);
	else
	  qpainter.fillRect(j*cellaSzelesseg, i*cellaMagassag,
			    cellaSzelesseg, cellaMagassag, Qt::white);
	  qpainter.setPen(QPen(Qt::gray, 1));
	
	qpainter.drawRect(j*cellaSzelesseg, i*cellaMagassag,
			  cellaSzelesseg, cellaMagassag);
    }
  }
  
  qpainter.end();
}


SejtAblak::~SejtAblak()
{
  delete eletjatek;
  
  for(int i=0; i<magassag; ++i) {
    delete[] racsok[0][i];
    delete[] racsok[1][i];
  }
  
  delete[] racsok[0];
  delete[] racsok[1];
  delete[] racsok;
  
  
}

void SejtAblak::vissza(int racsIndex)
{
  this->racsIndex = racsIndex;
  update();
}

/**
 * A sejtt�rbe "ELOl�nyeket" helyez�nk, ez a "sikl�".
 * Adott ir�nyban halad, m�solja mag�t a sejtt�rben.
 * Az ELOl�ny ismertet�s�t l�sd p�ld�ul a
 * [MATEK J�T�K] hivatkoz�sban (Cs�k�ny B�la: Diszkr�t
 * matematikai j�t�kok. Polygon, Szeged 1998. 172. oldal.)
 *
 * @param   racs    a sejtt�r ahov� ezt az �llatk�t helyezz�k
 * @param   x       a befoglal� t�gla bal fels� sark�nak oszlopa
 * @param   y       a befoglal� t�gla bal fels� sark�nak sora
 */
void SejtAblak::siklo(bool **racs, int x, int y) {
  
  racs[y+ 0][x+ 2] = ELO;
  racs[y+ 1][x+ 1] = ELO;
  racs[y+ 2][x+ 1] = ELO;
  racs[y+ 2][x+ 2] = ELO;
  racs[y+ 2][x+ 3] = ELO;
  
}
/**
 * A sejtt�rbe "ELOl�nyeket" helyez�nk, ez a "sikl� �gy�".
 * Adott ir�nyban sikl�kat l� ki.
 * Az ELOl�ny ismertet�s�t l�sd p�ld�ul a
 * [MATEK J�T�K] hivatkoz�sban /Cs�k�ny B�la: Diszkr�t
 * matematikai j�t�kok. Polygon, Szeged 1998. 173. oldal./,
 * de itt az �bra hib�s, egy oszloppal told m�g balra a
 * bal oldali 4 sejtes n�gyzetet. A helyes �gy� rajz�t
 * l�sd pl. az [�LET CIKK] hivatkoz�sban /Robert T.
 * Wainwright: Life is Universal./ (Megeml�thetj�k, hogy
 * mindkett� tartalmaz k�t felesleges sejtet is.)
 *
 * @param   racs    a sejtt�r ahov� ezt az �llatk�t helyezz�k
 * @param   x       a befoglal� t�gla bal fels� sark�nak oszlopa
 * @param   y       a befoglal� t�gla bal fels� sark�nak sora
 */
void SejtAblak::sikloKilovo(bool **racs, int x, int y) {
  
  racs[y+ 6][x+ 0] = ELO;
  racs[y+ 6][x+ 1] = ELO;
  racs[y+ 7][x+ 0] = ELO;
  racs[y+ 7][x+ 1] = ELO;
  
  racs[y+ 3][x+ 13] = ELO;
  
  racs[y+ 4][x+ 12] = ELO;
  racs[y+ 4][x+ 14] = ELO;
  
  racs[y+ 5][x+ 11] = ELO;
  racs[y+ 5][x+ 15] = ELO;
  racs[y+ 5][x+ 16] = ELO;
  racs[y+ 5][x+ 25] = ELO;
  
  racs[y+ 6][x+ 11] = ELO;
  racs[y+ 6][x+ 15] = ELO;
  racs[y+ 6][x+ 16] = ELO;
  racs[y+ 6][x+ 22] = ELO;
  racs[y+ 6][x+ 23] = ELO;
  racs[y+ 6][x+ 24] = ELO;
  racs[y+ 6][x+ 25] = ELO;
  
  racs[y+ 7][x+ 11] = ELO;
  racs[y+ 7][x+ 15] = ELO;
  racs[y+ 7][x+ 16] = ELO;
  racs[y+ 7][x+ 21] = ELO;
  racs[y+ 7][x+ 22] = ELO;
  racs[y+ 7][x+ 23] = ELO;
  racs[y+ 7][x+ 24] = ELO;
  
  racs[y+ 8][x+ 12] = ELO;
  racs[y+ 8][x+ 14] = ELO;
  racs[y+ 8][x+ 21] = ELO;
  racs[y+ 8][x+ 24] = ELO;
  racs[y+ 8][x+ 34] = ELO;
  racs[y+ 8][x+ 35] = ELO;
  
  racs[y+ 9][x+ 13] = ELO;
  racs[y+ 9][x+ 21] = ELO;
  racs[y+ 9][x+ 22] = ELO;
  racs[y+ 9][x+ 23] = ELO;
  racs[y+ 9][x+ 24] = ELO;
  racs[y+ 9][x+ 34] = ELO;
  racs[y+ 9][x+ 35] = ELO;
  
  racs[y+ 10][x+ 22] = ELO;
  racs[y+ 10][x+ 23] = ELO;
  racs[y+ 10][x+ 24] = ELO;
  racs[y+ 10][x+ 25] = ELO;
  
  racs[y+ 11][x+ 25] = ELO;
  
}

