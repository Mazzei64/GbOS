char buffer[512];

void os_put_char(char t){
    asm("mov ah,0x0e\nmov al,byte [bp+4]\nint 0x10");
}

void os_put_string(char *msg){
    int i = 0;
    while(1){
        char t = msg[i];
        i++;
        if(t==0){
            break;
        }
        os_put_char(t);
    }
}

char os_reset_drive(char driveno){
    asm("mov ah,0x00\nmov dl,byte [bp+4]\nint 0x13");
}

char os_read_sector(char driveno,short sector){
    asm("mov ax,0x00\nmov bx,0x00\nmov cx,0x00\nmov dx,0x00\nmov ah,0x02\nmov al,byte [bp+6]\nmov dl,byte [bp+4]\nmov si, _buffer\nmov bx, ds\nmov es, bx\nmov bx, si\nint 0x13");
}

char os_detect_fs(char driveno){
    if(os_read_sector(driveno,1)==0){
        os_put_string("sector read OK");
    }else{
        os_put_string("sector read not OK");
    }
}

void os_detect_drives(){
    for(char i = 0 ; i < 5 ; i++){
        char t = os_reset_drive(i);
        if(t==0){
            os_put_string("Drive present\r\n");
            os_detect_fs(i);
        }
    }
}

void main(){
    os_put_string("Welcome to GBOS!\r\n");
    os_detect_drives();
}