void IapEraseSector(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
unsigned char IapReadByte(unsigned int  addr);
void eepwrite(unsigned char tempdata[],unsigned char templong);
void eepread(unsigned char tempdata[],unsigned char templong);