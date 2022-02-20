{
    for ( i = 1 ; i <= length($0) ; i++ ) {
        switch ( substr($0,i,1) ) {
            case "+" : { printf("0x91U,"); break;}
            case "-" : { printf("0x89U,"); break;}
            case " " : { printf("0x5D,"); break;}
            case "," : { printf("0x85U,"); break;}
            default  : { printf("'%s'+0x1D,",substr($0,i,1)); break;}
        }
    }
    printf("\n") ;
}
