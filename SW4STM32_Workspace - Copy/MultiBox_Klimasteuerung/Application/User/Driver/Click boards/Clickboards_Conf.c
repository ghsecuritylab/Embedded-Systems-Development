#include "Clickboards_Conf.h"

struct clickBoard * Create_clickBoard(uint8_t MB, uint8_t Address, char * Name, char * Description) {
    //Erstellen der Clickboard Treiber Struktur die von den Treibern genutzt wird
    struct clickBoard * TempClickboard = malloc(sizeof(struct clickBoard));

    //Erstellen der ParameterGruppe des Clickboards
    Firmware_EasyClickboard_CreateDriverParaGroup(&ParameterGroup_ClickBoards, MB, Address, Name, Description);

    //Verlinken TreiberStruktur mit ParameterGruppe
    TempClickboard->Group = ParameterGroup_ClickBoards.ChildGroups[ParameterGroup_ClickBoards.Count-1];

    ClickBoardArray[ClickBoardArrayCount] = TempClickboard;
    ClickBoardArrayCount++;

    Update_Clickboard(TempClickboard);

    return TempClickboard;
}


void Update_Clickboard(struct clickBoard * clickBoard) {
    //Übertragen der ParameterÄnderung in die ClickBoard Struktur
    if (clickBoard != NULL) {
        clickBoard->Address = ParameterRead(clickBoard->Group->Para[1],Value);
        uint8_t Index = ParameterRead(clickBoard->Group->Para[0],Value);
        clickBoard->MB = MB_Array[Index-1];
    }
}
