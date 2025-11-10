#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criar_arquivo_jogos() {
    FILE *arquivo = fopen("jogos.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }

    // 100 nomes de jogos famosos
    char jogos[100][50] = {
        "MARIO", "SONIC", "ZELDA", "POKEMON", "FIFA",
        "CALL OF DUTY", "MINECRAFT", "FORTNITE", "GTA", "THE WITCHER",
        "OVERWATCH", "VALORANT", "LEAGUE OF LEGENDS", "DOTA", "CSGO",
        "APEX LEGENDS", "PUBG", "ROCKET LEAGUE", "AMONG US", "FALL GUYS",
        "ROBLOX", "ANIMAL CROSSING", "STARDEW VALLEY", "TERRARIA", "SIMCITY",
        "THE SIMS", "CIVILIZATION", "AGE OF EMPIRES", "WARCRAFT", "STARCRAFT",
        "DIABLO", "BALDURS GATE", "SKYRIM", "FALLOUT", "MASS EFFECT",
        "DRAGON AGE", "DARK SOULS", "ELDEN RING", "BLOODBORNE", "SEKIRO",
        "GOD OF WAR", "DEVIL MAY CRY", "BAYONETTA", "FINAL FANTASY", "PERSONA",
        "DRAGON QUEST", "KINGDOM HEARTS", "FIRE EMBLEM", "XENOBLADE", "METROID",
        "CASTLEVANIA", "MEGAMAN", "CONTRA", "STREET FIGHTER", "MORTAL KOMBAT",
        "TEKKEN", "SOULCALIBUR", "SMASH BROS", "MARIO KART", "MARIO PARTY",
        "SPLATOON", "KIRBY", "DONKEY KONG", "STAR FOX", "FZERO",
        "GEARS OF WAR", "HALO", "FORZA", "GEARS OF WAR", "GEARS",
        "RESIDENT EVIL", "SILENT HILL", "DEAD SPACE", "OUTLAST", "AMNESIA",
        "BATMAN ARKHAM", "SPIDERMAN", "ASSASSINS CREED", "WATCH DOGS", "CYBERPUNK",
        "DEUS EX", "SYSTEM SHOCK", "BIOSHOCK", "PORTAL", "HALFLIFE",
        "LEFT FOR DEAD", "TEAM FORTRESS", "PAYDAY", "BORDERLANDS", "DESTINY",
        "THE DIVISION", "GHOST RECON", "RAINBOW SIX", "BATTLEFIELD", "TITANFALL",
        "FAR CRY", "JUST CAUSE", "RED DEAD", "HORIZON", "GHOST OF TSUSHIMA",
        "DEATH STRANDING", "METAL GEAR", "TOMB RAIDER", "UNCHARTED", "THE LAST OF US",
        "RATCHET AND CLANK", "JAK AND DAXTER", "SPYRO", "CRASH BANDICOOT", "BANJO KAZOOIE"
    };

    // Escreve todos os jogos no arquivo
    for (int i = 0; i < 100; i++) {
        fwrite(jogos[i], sizeof(char), 50, arquivo);
    }
    
    fclose(arquivo);
    printf("Arquivo 'jogos.bin' criado com sucesso com 100 nomes de jogos!\n");
}

int main() {
    criar_arquivo_jogos();
    return 0;
}