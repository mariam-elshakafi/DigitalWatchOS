#define Set_Bit(Reg,Pin)    Reg|=(1<<Pin)
#define CLR_Bit(Reg,Pin)    Reg&=~(1<<Pin)
#define Toggle_Bit(Reg,Pin)  Reg^=(1<<Pin)
#define Get_Bit(Reg,Pin)     ((Reg>>Pin)&0x01)