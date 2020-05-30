// Backspace: 14, Tab: 15, Enter: 28, Ctrl: 29, LShift: 42/170, RShift: 54/182, Alt: 56, Space: 57, Cmd: 91

char keyboard_map[64] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=',8,9,
    'q','w','e','r','t','y','u','i','o','p','[',']',13,0,'a',
    's','d','f','g','h','j','k','l',';','\'','`',0,'\\','z','x',
    'c','v','b','n','m',',','.','/',0,0,0,' '
};

char shifted_keyboard_map[64] = {
    0,27,'!','@','#','$','%','^','&','*','(',')','_','+',8,9,
    'q','w','e','r','t','y','u','i','o','p','[',']',13,0,'a',
    's','d','f','g','h','j','k','l',':','"','~',0,'|','z','x',
    'c','v','b','n','m','<','>','?',0,0,0,' '
};


int read();

int shift=0;
int caps=0;


char getChar(){

    int keyCode = read();

    // Shift in
    if(keyCode == 42 || keyCode == 54){
        shift = 1;
        return 15;
    }

    // Shift out
    if(keyCode == 170 || keyCode == 182){
        shift = 0;
        return 14;
    }

    // Caps lock
    if(keyCode == 58){
        caps = caps ? 0 : 1;
        return 14;
    }

    // Release code
    if(keyCode >= 129){
        return 0;
    }
    
    // If it is a letter check for shift/caps
    if((keyCode>=16 && keyCode<=25) || (keyCode>=30 && keyCode<=38) || (keyCode>=44 && keyCode<=50)){
        
        int cap = (shift || caps) && !(shift && caps);
        return cap ? keyboard_map[keyCode]-'a'+'A' : keyboard_map[keyCode];
    
    }else{

        return shift ? shifted_keyboard_map[keyCode] : keyboard_map[keyCode];

    }

}