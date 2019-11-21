#include "config_reader.h"
#include <stdio.h>
#include <stdlib.h>

void extract_config(Config* conf) {
    extract_peta(&(*conf).conf_peta);
    extract_banyak_bangunan(&(*conf).conf_banyak_bangunan);
    extract_listBangunan((*conf).conf_banyak_bangunan,&(*conf).conf_list_bangunan);
    extract_relasi((*conf).conf_banyak_bangunan, &(*conf).conf_relasi);
    CC = ' ';
}

void extract_peta(Peta *peta){
    START_file(1);
    int r = Token.Bil;
    ADV_file();
    int c = Token.Bil;
    MakePeta(peta, r, c);
}

void extract_banyak_bangunan(int *banyak_bangunan) {
    START_file(2);
    *banyak_bangunan = Token.Bil;
}

void extract_listBangunan(int banyak_bangunan, TabBangunan* list_bangunan) {
    CreateEmptyTabBangunan(list_bangunan, banyak_bangunan);
    for(int i = 1; i < banyak_bangunan+1; i++ ) {
        START_file(2 + i);

        Bangunan B; 
        B.id = i;
        if(i <= 2) B.owner = i;
        else B.owner = 0;

        B.type = Token.Val;
        ADV_file();
        B.posisi.r = Token.Bil;
        ADV_file();
        B.posisi.c = Token.Bil;

        B.level = 0;
        levelup(&B);
        AddBangunan(B, list_bangunan);
    }
}

void extract_relasi(int banyak_bangunan, Graph* relasi) {
    int i, j;
    *relasi = CreateGraph(banyak_bangunan, banyak_bangunan);
    for ( i = 1; i <= banyak_bangunan; i++ ) {
        START_file(2 + banyak_bangunan + i);
        for ( j = 1; j <= banyak_bangunan; j++ ) {
            if ( Token.Bil == 1) SetBangunanTerhubung(*relasi, i, j);
            ADV_file();
        }
    }
}
