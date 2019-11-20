#include "bangunan.h"

boolean AttackBerhasil;

void CreateBangunanEmpty(Bangunan *B){
    (*B).id = -1;
    (*B).jumlah_pasukan = 0;
    (*B).level = 0;
    (*B).nilai_tambah_pasukan = 0;
    (*B).owner = -1;
    (*B).pertahanan = false;
    (*B).sudahserang = false;
    (*B).posisi.r = 0;
    (*B).posisi.c = 0;
    (*B).type = ' ';
}

boolean IsBangunanEmpty(Bangunan B){
    return B.id == -1;
}

void levelup(Bangunan *B){
/* Menaikkan level dari Bangunan Pemain */
    if(Level(*B) < 4){
        Level(*B) += 1;
        // "M" : 1, "A" : 2, "P" : 3
        if(Type(*B) == 'C'){
            RateTambah(*B) = MatElmt(AttCastle, Level(*B), 1);
            MaxPasukan(*B) = MatElmt(AttCastle, Level(*B), 2);
            Pertahanan(*B) = MatElmt(AttCastle, Level(*B), 3);
            if(Level(*B) == 1) Pasukan(*B) = MatElmt(AttCastle, Level(*B), 4);
        }
        else if(Type(*B) == 'T'){
            RateTambah(*B) = MatElmt(AttTower, Level(*B), 1);
            MaxPasukan(*B) = MatElmt(AttTower, Level(*B), 2);
            Pertahanan(*B) = MatElmt(AttTower, Level(*B), 3);
            if(Level(*B) == 1) Pasukan(*B) = MatElmt(AttTower, Level(*B), 4);
        }
        else if(Type(*B) == 'F'){
            RateTambah(*B) = MatElmt(AttFort, Level(*B), 1);
            MaxPasukan(*B) = MatElmt(AttFort, Level(*B), 2);
            Pertahanan(*B) = MatElmt(AttFort, Level(*B), 3);
            if(Level(*B) == 1) Pasukan(*B) = MatElmt(AttFort, Level(*B), 4);
        }
        else if(Type(*B) == 'V'){
            RateTambah(*B) = MatElmt(AttVillage, Level(*B), 1);
            MaxPasukan(*B) = MatElmt(AttVillage, Level(*B), 2);
            Pertahanan(*B) = MatElmt(AttVillage, Level(*B), 3);
            if(Level(*B) == 1) Pasukan(*B) = MatElmt(AttVillage, Level(*B), 4);
        }
    }
    else{
        printf("Level Bangunan sudah Maksimum, tidak dapat melakukan level up lagi\n");
    }
}

void attack(Bangunan *BAtt, Bangunan *BDef, int jumlah_penyerang){
    AttackBerhasil = false;
    if(Pasukan(*BAtt) < jumlah_penyerang){
        printf("Attack tidak dapat dilakukan karena pasukan tidak mencukupi.\n");
    }
    else{
        /* Perubahan Jumlah Pasukan saat melancarkan Penyerangan */
        Pasukan(*BAtt) -= jumlah_penyerang;
        if(!Pertahanan(*BDef)){
            Pasukan(*BDef) -= jumlah_penyerang;
        }
        else{
            Pasukan(*BDef) -= (3/4 * jumlah_penyerang);
        }
        /* STATE SETELAH PENYERANGAN */
        // Berhasil Diambil
        if(Pasukan(*BDef) < 0){
            printf("Bangunan berhasil diambil, pasukan yang tersisa sebanyak %d pasukan di dalam Bangunan.\n", -Pasukan(*BDef));
            Pasukan(*BDef) = -1 * Pasukan(*BDef);
            BangunanOwner(*BDef) = BangunanOwner(*BAtt);
        }
        else if(Pasukan(*BDef) == 0){
            printf("Bangunan berhasil diambil, tidak ada pasukan yang tersisa untuk menjaga bangunan.\n");
            BangunanOwner(*BDef) = BangunanOwner(*BAtt);
        }
        // Tidak Berhasil Diambil
        else{/* Pasukan(*BDef) > 0 setelah penyerangan, masih tersisa pasukan pertahanan */
            printf("Bangunan tidak berhasil diambil.\n");
        }
    }

}
/* Menghitung perubahan jumlah pasukan saat terjadi penyerangan oleh BAtt kepada BDef */

void move(Bangunan *BAwal, Bangunan *BAkhir, int jumlah_pasukan_pindah){
    if(Pasukan(*BAkhir) == MaxPasukan(*BAkhir)){
         printf("Bangunan yang dituju penuh, tidak dapat MatElmtindahkan pasukan\n");
    }
    else{ /*Bangunan Akhir tidak penuh, perpindahan dapat dilakukan */

        if(Pasukan(*BAwal) < jumlah_pasukan_pindah){ /* Jumlah pasukan di bangunan awal kurang dari jumlah pasukan yang akan dipindahkan */

            if((Pasukan(*BAwal) + Pasukan(*BAkhir)) > MaxPasukan(*BAkhir)){ /*Perpindahan melebihi kapasitas bangunan akhir */
                printf("Pasukan di bangunan awal kurang, MatElmtindahkan %d pasukan karena bangunan akhir sudah penuh\n", MaxPasukan(*BAkhir) - Pasukan(*BAkhir));
                Pasukan(*BAwal) -= MaxPasukan(*BAkhir) - Pasukan(*BAkhir);
                Pasukan(*BAkhir) += MaxPasukan(*BAkhir) - Pasukan(*BAkhir);
            }

            else{ /* Perpindahan masih dapat ditampung kapasitas bangunan akhir */
                printf("Pasukan di bangunan awal kurang, MatElmtindahkan %d pasukan\n", Pasukan(*BAwal));
                Pasukan(*BAwal) -= Pasukan(*BAwal);
                Pasukan(*BAkhir) += Pasukan(*BAwal);
            }
        }

        else{ /*Jumlah pasukan di bangunan awal lebih dari jumlah pasukan yang akan dipindahkan */

            if((jumlah_pasukan_pindah + Pasukan(*BAkhir)) > MaxPasukan(*BAkhir)){ /*Perpindahan melebihi kapasitas bangunan akhir */
                printf("MatElmtindahkan %d pasukan karena bangunan akhir sudah penuh\n", MaxPasukan(*BAkhir) - Pasukan(*BAkhir));
                Pasukan(*BAwal) -= MaxPasukan(*BAkhir) - Pasukan(*BAkhir);
                Pasukan(*BAkhir) += MaxPasukan(*BAkhir) - Pasukan(*BAkhir);
            }
            else{/* Perpindahan terjadi secara normal tanpa ada bangunan yang habis pasukannya atau penuh */
                Pasukan(*BAwal) -= jumlah_pasukan_pindah;
                Pasukan(*BAkhir) += jumlah_pasukan_pindah;
            }
        }
    }
}
/* Menghitung perubahan jumlah pasukan saat terjadi perpindahan pasukan (Command : MOVE) */

void add_pasukan(Bangunan *B){
    if((RateTambah(*B) + Pasukan(*B)) > MaxPasukan(*B)){
        Pasukan(*B) += (MaxPasukan(*B) - Pasukan(*B));
    }
    else{
        Pasukan(*B) += RateTambah(*B);
    }
}
/* Menghitung perubahan jumlah pasukan saat awal turn */

void TulisBangunan(Bangunan B){
    printf("<%d> %c at (%d,%d)\n", B.id, B.type, B.posisi.r, B.posisi.c);
    printf("Milik player "); println(B.owner);
    printf("Level: "); println(B.level);
    printf("Jumlah Pasukan: "); println(B.jumlah_pasukan);
    printf("Shield active? ");
    if(B.pertahanan) printf("yes");
    else printf("no");
    ENDL;
    printf("Sudah serang? ");
    if(B.sudahserang) printf("yes");
    else printf("no");
    ENDL;
}