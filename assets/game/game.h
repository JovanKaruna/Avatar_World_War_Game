#ifndef GAME_H
#define GAME_H

#include "../util/util.h"
#include "../util/gui.h"
#include "../peta/peta.h"
#include "../bangunan/list_bangunan.h"
#include "../bangunan/arraydin_bangunan.h"
#include "../game/game_stackt.h"
#include "../util/config_reader.h"
#include "../save/save.h"

// GameCondition yang digunakan adalah yang berada di Top
// setiap melakukan aksi lakukan Push pada stackt
// saat melakukan UNDO lakukan Pop pada stackt 

#define Player(n) InfoTopStackt(G.GameConditions).Players[n-1]
#define CurTurn() InfoTopStackt(G.GameConditions).turn
#define OtherTurn() ((InfoTopStackt(G.GameConditions).turn)%2)+1
#define CurPlayer() Player(CurTurn())
#define OtherPlayer() Player(OtherTurn())

void InitGame();
// Membaca file config dan menginisialisasi attribut pada Game G
// a. Pada saat permainan dimulai, game akan membaca konfigurasi permainan dari file
// eksternal (dijelaskan pada bab selanjutnya).
// b. Queue ​ skill setiap pemain berisi 1 buah skill, yaitu Instant Upgrade

void InitPlayer();

void InitMap();

void InitTurn();

// void SaveGame();
// void LoadGame(GameCondition Gc);
// Load permainan yang telah disimpan
// I.S : Sembarang
// F.s : G.GameCondition = Gc

void LoadFromFile(Kata filename);

void StartGame();
// Memulai permainan

boolean IsGameEnded();
boolean IsPlayerLose(int player);

#endif