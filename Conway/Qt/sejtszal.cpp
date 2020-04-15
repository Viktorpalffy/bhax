// sejtszal.cpp
//
// �letj�t�k rajzol�
// Programoz� P�ternoszter
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

#include "sejtszal.h"

SejtSzal::SejtSzal(bool ***racsok, int szelesseg, int magassag, int varakozas, SejtAblak *sejtAblak)
{
    this->racsok = racsok;
    this->szelesseg = szelesseg;
    this->magassag = magassag;
    this->varakozas = varakozas;
    this->sejtAblak = sejtAblak;

    racsIndex = 0;
}

/**
   * Az k�rdezett �llapotban l�v� nyolcszomsz�dok sz�ma.
   *
   * @param   r�cs    a sejtt�r r�cs
   * @param   sor     a r�cs vizsg�lt sora
   * @param   oszlop  a r�cs vizsg�lt oszlopa
   * @param   �llapor a nyolcszomsz�dok vizsg�lt �llapota
   * @return int a k�rdezett �llapotbeli nyolcszomsz�dok sz�ma.
   */
int SejtSzal::szomszedokSzama(bool **racs,
                              int sor, int oszlop, bool allapot) {
    int allapotuSzomszed = 0;
    // A nyolcszomsz�dok v�gigzongor�z�sa:
    for(int i=-1; i<2; ++i)
        for(int j=-1; j<2; ++j)
            // A vizsg�lt sejtet mag�t kihagyva:
            if(!((i==0) && (j==0))) {
        // A sejtt�rb�l sz�l�nek szomsz�dai
        // a szembe oldalakon ("peri�dikus hat�rfelt�tel")
        int o = oszlop + j;
        if(o < 0)
            o = szelesseg-1;
        else if(o >= szelesseg)
            o = 0;

        int s = sor + i;
        if(s < 0)
            s = magassag-1;
        else if(s >= magassag)
            s = 0;

        if(racs[s][o] == allapot)
            ++allapotuSzomszed;
    }

    return allapotuSzomszed;
}

/**
 * A sejtt�r id�beli fejl�d�se a John H. Conway f�le
 * �letj�t�k sejtautomata szab�lyai alapj�n t�rt�nik.
 * A szab�lyok r�szletes ismertet�s�t l�sd p�ld�ul a
 * [MATEK J�T�K] hivatkoz�sban (Cs�k�ny B�la: Diszkr�t
 * matematikai j�t�kok. Polygon, Szeged 1998. 171. oldal.)
 */
void SejtSzal::idoFejlodes() {

    bool **racsElotte = racsok[racsIndex];
    bool **racsUtana = racsok[(racsIndex+1)%2];

    for(int i=0; i<magassag; ++i) { // sorok
        for(int j=0; j<szelesseg; ++j) { // oszlopok

            int elok = szomszedokSzama(racsElotte, i, j, SejtAblak::ELO);

            if(racsElotte[i][j] == SejtAblak::ELO) {
                /* �l� �l� marad, ha kett� vagy h�rom �l�
             szomszedja van, k�l�nben halott lesz. */
                if(elok==2 || elok==3)
                    racsUtana[i][j] = SejtAblak::ELO;
                else
                    racsUtana[i][j] = SejtAblak::HALOTT;
            }  else {
                /* Halott halott marad, ha h�rom �l�
             szomszedja van, k�l�nben �l� lesz. */
                if(elok==3)
                    racsUtana[i][j] = SejtAblak::ELO;
                else
                    racsUtana[i][j] = SejtAblak::HALOTT;
            }
        }
    }
    racsIndex = (racsIndex+1)%2;
}


/** A sejtt�r id�beli fejl�d�se. */
void SejtSzal::run()
{
    while(true) {
        QThread::msleep(varakozas);
        idoFejlodes();
        sejtAblak->vissza(racsIndex);
    }

}

SejtSzal::~SejtSzal()
{
}

